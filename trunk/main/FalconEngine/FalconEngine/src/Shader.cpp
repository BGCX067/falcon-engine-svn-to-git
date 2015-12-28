#include "stdafx.h"
#include "Shader.h"

#include <iostream>
#include <fstream>

#define BUFFER_OFFSET(bytes) ((GLubyte*)NULL + (bytes))
GLuint falcon::Shader::s_activeProgram = 0;

//////////////////////////////////////////////////////////////////////////
///						LUA REGISTRATION							   ///
//////////////////////////////////////////////////////////////////////////
// luabind::scope falcon::Shader::Register()
// {
// 	return 
// 		luabind::class_<Shader, Shader*>("Shader")
// 		.def(luabind::constructor<std::string, std::string>());
// }

//////////////////////////////////////////////////////////////////////////
///						LUA REGISTRATION							   ///
//////////////////////////////////////////////////////////////////////////
// luabind::scope falcon::ShaderData::Register()
// {
// 	return 
// 		luabind::class_<ShaderData, ShaderData*>("ShaderData")
// 		.def(luabind::constructor<>())
// 		.property("texture", &ShaderData::GetTexture, &ShaderData::SetTexture)
// 		.property("color", &ShaderData::GetDiffuseColor, &ShaderData::SetDiffuseColor);
// }


falcon::Shader::Shader(std::string vert, std::string frag)
	:m_VertexShader(vert),
	m_FragmentShader(frag),
	m_VertexShaderID(0),
	m_FragmentShaderID(0),
	m_ProgramID(0),
	m_inPosition(-1),
	m_inNormal(-1),
	m_inTC(-1),
	m_shaderData(0)
{
}

falcon::Shader::~Shader()
{

	//clean all shader variables
	std::map<std::string, ShaderVariable*>::iterator iter = m_VariableMap.begin();
	std::map<std::string, ShaderVariable*>::iterator itEnd = m_VariableMap.end();

	for(iter; iter != itEnd; ++iter)
	{
		delete (*iter).second;
	}
	m_VariableMap.clear();

	//detachshaders
	glDetachShader(m_ProgramID, m_VertexShaderID);
	glDetachShader(m_ProgramID, m_FragmentShaderID);

	//delete shaders
	glDeleteShader(m_VertexShaderID);
	glDeleteShader(m_FragmentShaderID);

	//and eventually delete the program
	glDeleteProgram(m_ProgramID);
}

bool falcon::Shader::Init()
{
	//create our shaders
	m_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//Read the source for both
	std::string vertexSource = ReadFile(m_VertexShader);
	GLint vlength = vertexSource.length();
	const char* vertexCharSource = vertexSource.c_str();
	glShaderSource(m_VertexShaderID, 1 , &vertexCharSource, &vlength);
	
	std::string fragmentSource = ReadFile(m_FragmentShader);
	GLint flength = fragmentSource.length();
	const char* fragmentCharSource = fragmentSource.c_str();
	glShaderSource(m_FragmentShaderID, 1 , &fragmentCharSource, &flength);

	//compile them both
	glCompileShader(m_VertexShaderID);
	GLint vresult;
	glGetShaderiv(m_VertexShaderID, GL_COMPILE_STATUS,&vresult); 

	glCompileShader(m_FragmentShaderID);
	GLint fresult;
	glGetShaderiv(m_FragmentShaderID, GL_COMPILE_STATUS,&fresult); 

	//if both compiles are OK
	if ( vresult == GL_TRUE && fresult == GL_TRUE )
	{
		//create our program and attach both shaders
		m_ProgramID = glCreateProgram();
		glAttachShader(m_ProgramID,m_VertexShaderID);
		glAttachShader(m_ProgramID,m_FragmentShaderID);

		//use a custom out variable for our frag-data
		glBindFragDataLocation(m_ProgramID, 0, "outColor");

		//link the program
		glLinkProgram(m_ProgramID);

		GLint presult;
		glGetProgramiv(m_ProgramID,GL_LINK_STATUS, &presult);
		//if the linking was unsuccessful show a message
		if (presult == GL_FALSE )
		{
			LOG(LOG_Error, "Shader Linking Was Unsuccesful!");
			return false;
		}
	}else{
		//if compiling fails show what failed
		char logBuffer[1024*4];
		int length;
		glGetShaderInfoLog(m_VertexShaderID, 1024*4, &length, logBuffer);
		LOG(LOG_Error, logBuffer);
		return false;
	}

	//Get the attribute Locations
	m_inPosition =  glGetAttribLocation(m_ProgramID, "inPosition");
	m_inNormal =  glGetAttribLocation(m_ProgramID, "inNormal");
	m_inTC =  glGetAttribLocation(m_ProgramID, "inTexCoord");

	//activate the shader
	Activate();

	//create Shadervariables
	CreateVariables();
	return true;
}

void falcon::Shader::Activate()
{
	if(m_ProgramID != 0 && s_activeProgram != m_ProgramID)
	{
		//activate our shader
		glUseProgram(m_ProgramID);
		if(m_inPosition > -1) glEnableVertexAttribArray(m_inPosition);
		if(m_inNormal > -1) glEnableVertexAttribArray(m_inNormal);
		if(m_inTC > -1) glEnableVertexAttribArray(m_inTC);
		s_activeProgram = m_ProgramID;
	}
}

void falcon::Shader::Deactivate()
{
	//disable our shader
	if(m_inPosition > -1) glDisableVertexAttribArray(m_inPosition);
	if(m_inNormal > -1) glDisableVertexAttribArray(m_inNormal);
	if(m_inTC > -1) glDisableVertexAttribArray(m_inTC);
	glUseProgram(0);
	s_activeProgram = 0;
}
void falcon::Shader::SetAttributes()
{
	//set the attribute variables for our shader
	if(m_inPosition > -1) glVertexAttribPointer(m_inPosition, 3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));
	if(m_inNormal > -1) glVertexAttribPointer(m_inNormal, 3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));
	if(m_inTC > -1) glVertexAttribPointer(m_inTC, 2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));
}

falcon::ShaderVariable& falcon::Shader::GetShaderVariable(std::string name)
{
	//return the asked shader variable
	return *m_VariableMap[name];
}

void falcon::Shader::AddShaderVariable(std::string name)
{
	GLint locID = glGetUniformLocation(m_ProgramID,name.c_str());
	m_VariableMap[name] = new ShaderVariable(locID);
}

std::string falcon::Shader::ReadFile(std::string filename)
{
	//straightforward, read the file
	std::ifstream file;
	file.open(filename.c_str());
	std::string result = "";
	std::string line;
	if ( file.is_open())
	{
		while ( file.good() )
		{
			getline (file,line);
			result += line + "\n";
		}
		file.close();
	}
	return result;

}