#ifndef FALCONENGINE_SKYBOX_H
#define FALCONENGINE_SKYBOX_H

#include "InputState.h"
#include "RenderContext.h"
#include "FalconLuaBind.h"

namespace falcon
{
	class Shader;
	class ShaderData;
	class ResourceManager;
	class VertexBuffer;
	class IndexBuffer;

	class SkyBox
	{
	public:
		SkyBox(std::string texturePath);
		virtual ~SkyBox();

		virtual void Init(ResourceManager* resourceManager);		
		void Draw(RenderContext& renderContext);

		void SetLocation(const Vec3& location);

		static luabind::scope Register();
	protected:
		void BuildCube();
		void AddQuad(const unsigned int a, const unsigned int b, const unsigned int c, const unsigned int d);

		std::string m_texturePath;
		GLuint m_textureID;

		VertexBuffer* m_vBuffer;
		IndexBuffer* m_iBuffer;

		Shader* m_shader;
		ShaderData* m_shaderData;

		Vec3 m_location;
	private:
		SkyBox(const SkyBox& t);
		SkyBox& operator=(const SkyBox& t);
	};
}

#endif //FALCONENGINE_SKYBOX_H
