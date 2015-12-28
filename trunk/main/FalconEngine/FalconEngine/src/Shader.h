#ifndef FALCONENGINE_SHADER_H
#define FALCONENGINE_SHADER_H

#include <map>
#include "ShaderVariable.h"
#include "typedefs.h"
#include "FalconLuaBind.h"

namespace falcon
{
	class ShaderVariable;

	class ShaderData
	{
	public:
		ShaderData():
			m_worldMatrix(Mat4()),
			m_worldViewProjectionMatrix(Mat4()),
			m_texID(0)
			{}
		virtual ~ShaderData(){}
		
		virtual void SetWorldMatrix(Mat4& wm){m_worldMatrix = wm;}
		virtual Mat4 GetWorldMatrix() const {return m_worldMatrix;}

		virtual void SetWorldViewProjectionMatrix(Mat4& wvpm){m_worldViewProjectionMatrix = wvpm;}
		virtual Mat4 GetWorldViewProjectionMatrix() const {return m_worldViewProjectionMatrix;}

		virtual void SetTexture(TextureID id){m_texID = id;}
 		virtual TextureID GetTexture() const {return m_texID;}

		virtual void SetCubeTexture(TextureID id){m_cubeTexID = id;}
 		virtual TextureID GetCubeTexture() const {return m_cubeTexID;}

		virtual void SetDiffuseColor(Vec3& c){m_color = c;}
		virtual Vec3 GetDiffuseColor() const {return m_color;}

		static luabind::scope Register()
		{
			return 
				luabind::class_<ShaderData, ShaderData*>("ShaderData")
				.def(luabind::constructor<>())
				.property("texture", &ShaderData::GetTexture, &ShaderData::SetTexture)
				.property("color", &ShaderData::GetDiffuseColor, &ShaderData::SetDiffuseColor);
		}

	private:
		Mat4 m_worldMatrix;
		Mat4 m_worldViewProjectionMatrix;
		TextureID m_texID;
		TextureID m_cubeTexID;
		Vec3 m_color;
	};

	class Shader
	{
	public:
		Shader(std::string vert, std::string frag);
		virtual ~Shader(void);

		bool Init();
		void Activate();
		void Deactivate();

		void SetAttributes();

		ShaderVariable& GetShaderVariable(std::string name);
		void AddShaderVariable(std::string name);

		GLint GetProgramID() const {return m_ProgramID;}

		virtual void SetShaderData(ShaderData* data){m_shaderData = data;}
		virtual ShaderData* GetShaderData() const {return m_shaderData;}

		//cannot be pure virutal because of LUA
		virtual void SetShaderVariables(){};

		static luabind::scope Register()
		{
			return 
				luabind::class_<Shader, Shader*>("Shader")
				.def(luabind::constructor<std::string, std::string>());
		};
		
	protected:
		//cannot be pure virutal because of LUA
		virtual void CreateVariables(){};
		ShaderData* m_shaderData;

	private:
		std::string ReadFile(std::string fileName);

		//filenames for the shaders
		std::string m_VertexShader;
		std::string m_FragmentShader;

		//IDs for the shaders and program
		GLuint m_VertexShaderID;
		GLuint m_FragmentShaderID;
		GLuint m_ProgramID;

		//attributelocations of the program
		GLint m_inPosition;
		GLint m_inNormal;
		GLint m_inTC;

		static GLuint s_activeProgram;

		//map that holds the shaderUniformvariables
		std::map<std::string,ShaderVariable*> m_VariableMap;
		//disabled copy constructor and assignment operator
		Shader(const Shader& shader);
		Shader& operator=(const Shader& shader);
	};

}

#endif //FALCONENGINE_SHADER_H
