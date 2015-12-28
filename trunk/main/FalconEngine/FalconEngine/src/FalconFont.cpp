#include "FalconFont.h"
#include "FontShader.h"
#include "Camera.h"
#include "LogManager.h"
#include "Element2D.h"
#include "Element2DManager.h"
#include <boost\foreach.hpp>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Mesh.h"
#include "ResourceManager.h"

falcon::FalconFont::FalconFont(const std::string& fontName, float screenWidth, float screenHeight, int fontSize/* =16 */)
	:m_fontName(fontName)
	,m_screenHeight(screenHeight)
	,m_screenWidth(screenWidth)
	,m_fontSize(fontSize)
{
	m_Shader = new FontShader("./data/shaders/font.vert", "./data/shaders/font.frag");
	m_ShaderData = new ShaderData();
	m_Shader->SetShaderData(m_ShaderData);
}

falcon::FalconFont::~FalconFont()
{
	delete m_Shader;
	delete m_ShaderData;
	glDeleteTextures(128, m_textureID);
}

bool falcon::FalconFont::Init(ResourceManager* rm)
{
	m_ResourceManager = rm;

	// Create an instance of a freetype library
	FT_Library library;

	if (FT_Init_FreeType(&library))
	{
		LOG(LOG_Error,"Couldn't initialize freetype library!");
		return false;
	}

	// This contains all the info of the loaded font
	// A face describes a given typeface and style
	FT_Face fontInfo;

	// Load the font information
	if(FT_New_Face(library, m_fontName.c_str(), 0, &fontInfo))
	{
		LOG(LOG_Error,"Could not load specified font!");
		return false;
	}

	// Set the character size of the font
	// FreeType uses heights which are 1/64 of the size in pixels
	// The font height is thus 64*m_fontSize
	// 96x96 == dpi
	FT_Set_Char_Size(fontInfo, 0, (int)m_fontSize*64, 96, 96);

	// Generate 128 textures (one for each character)
	glGenTextures(128, m_textureID);

	for (int ch = 0; ch < fontInfo->num_glyphs; ++ch)
	{
		if (!generateCharacterTexture((unsigned char)ch, fontInfo))
		{
			std::stringstream buffer;
			buffer << "Could not generate the texture for character: " << ch << "\n";
			LOG(LOG_Error, buffer.str());
		}
	}

	// Releases the fontInfo and the library as we don't need them anymore
	FT_Done_Face(fontInfo);
	FT_Done_FreeType(library);

// 	// Init the texturecoordinates with default values, will be changed later on
	float texCoords[] = {
		0.0f, 1.0f,
		1.0f, 1.0f, 
		1.0f, 0.0f,
		0.0f, 0.0f
	};

	glGenBuffers(1, &m_texCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_texCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 8, &texCoords[0], GL_DYNAMIC_DRAW);
	
	return true;
}

bool falcon::FalconFont::generateCharacterTexture( unsigned char ch, FT_Face fontInfo )
{
	int glyph_index = FT_Get_Char_Index(fontInfo, ch);
	if(FT_Load_Glyph(fontInfo, glyph_index, FT_LOAD_DEFAULT))
	{
		return false;
	}

	if(FT_Render_Glyph(fontInfo->glyph, FT_RENDER_MODE_NORMAL))
	{
		return false;
	}

	FT_Bitmap myBitmap = fontInfo->glyph->bitmap;

	if (myBitmap.rows != 0 && myBitmap.width != 0)
	{
		int width = myBitmap.width;
		int rows = myBitmap.rows;
		int imageSize = width*rows*4;
	
		std::vector<unsigned char> imageData(imageSize);
		for (int i = 0; i < imageSize/4; ++i)
		{
			unsigned char color = 0;
			if (myBitmap.buffer) 
			{
				color = myBitmap.buffer[i];
			} 
	
			imageData[i*4] = color;
			imageData[(i*4)+1] = color;
			imageData[(i*4)+2] = color;
			imageData[(i*4)+3] = color;		
		}
	
		glBindTexture(GL_TEXTURE_2D, m_textureID[ch]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, &imageData[0]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	
		m_letters.insert(std::pair<unsigned char, TextureID>(ch, m_textureID[ch]));
	}

	m_glyphDimensions[ch] = std::make_pair( fontInfo->glyph->bitmap.width, fontInfo->glyph->bitmap.rows);
	m_glyphAdvances[ch] = fontInfo->glyph->advance.x/64;
	m_glyphPositions[ch] = std::make_pair(fontInfo->glyph->bitmap_left, fontInfo->glyph->bitmap_top);

	return true;
}

void falcon::FalconFont::printString(const std::string& str, float x, float y)
{
	Element2D Element(x,y,(float)m_fontSize,(float)m_fontSize);
	Element.Init();
	Element.SetShader(m_ResourceManager->GetShader("Font"));
	Element.SetShaderData(new ShaderData());

	float xPos = x, 
		  yPos = y;

	for (size_t i = 0; i < strlen(str.c_str()); ++i)
	{
		Element.SetWidth(m_glyphDimensions[str.at(i)].first);
		Element.SetHeight(m_glyphDimensions[str.at(i)].second);
		Element.SetPos(Vec2(xPos + m_glyphPositions[str.at(i)].first, yPos + m_glyphPositions[str.at(i)].second));
		Element.GetShaderData()->SetTexture(GetLetter(str.at(i)));
		Element.Draw();

		xPos += m_glyphAdvances[str.at(i)];
	}
}

