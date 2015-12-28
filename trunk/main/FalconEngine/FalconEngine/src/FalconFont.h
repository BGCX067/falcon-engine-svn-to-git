#ifndef FALCONENGINE_FALCONFONT_H
#define FALCONENGINE_FALCONFONT_H

#include <ft2build.h> 
#include FT_FREETYPE_H
#include <string>
#include "GL/glew.h"
#include <map>
#include <set>
#include "typedefs.h"

namespace falcon
{
	class Camera;
	class FontShader;
	class Element2D;
	class ShaderData;
	class ResourceManager;

	class FalconFont
	{
	public: 
		FalconFont(const std::string& fontName, float screenWidth, float screenHeight,  int fontSize=16);
		~FalconFont();

		bool Init(ResourceManager* rm);
		void printString(const std::string& str, float x, float y);
		TextureID GetLetter(unsigned char letter){return m_letters[letter];}

	private:
		// Make room for the character textures
		TextureID m_textureID[128];

		int m_fontSize;
		float m_screenWidth;
		float m_screenHeight;
		std::string m_fontName;
		std::map<unsigned char, TextureID> m_letters;

		GLuint m_texCoordBuffer;
		GLuint m_vertexBuffer;
		FontShader* m_Shader;
		ShaderData* m_ShaderData;
		bool generateCharacterTexture(unsigned char ch, FT_Face fontInfo);

		std::map<unsigned char, std::pair<int, int> > m_glyphDimensions;
		std::map<unsigned char, std::pair<int, int> > m_glyphPositions;
		std::map<unsigned char, int> m_glyphAdvances;

		ResourceManager* m_ResourceManager;
	};
}

#endif	//FALCONENGINE_FALCONFONT_H