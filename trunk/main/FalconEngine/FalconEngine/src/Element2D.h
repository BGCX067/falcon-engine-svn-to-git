#ifndef FALCONENGINE_ELEMENT2D_H
#define FALCONENGINE_ELEMENT2D_H

#include "FalconMath.h"
#include <vector>
#include "FalconLuaBind.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace falcon
{
	class RenderContext;
	class ShaderData;
	class Mesh;
	class ICallable;

	class Element2D
	{
	public:
		Element2D(float x, float y, float width, float height);
		virtual ~Element2D();

		void Init();
		void Draw();

		void Translate(float xDiff, float yDiff);

		// These methods have to be implemented by the user in inherited classes
		virtual void AddCallListener(ICallable* /*ptr*/){} /*= 0*/;
		virtual bool OnLMBClick(float /*x*/, float /*y*/){return false;} /*= 0*/;
		virtual void OnLMBReleased(){};

		// Getters & Setters
		const Vec2 GetCenter() const {return Vec2(m_pos.x+m_width/2, m_pos.y+m_height/2);}
		const float GetWidth() const {return m_width;}
		const float GetHeight() const {return m_height;}

		void SetWidth(const float width);
		void SetHeight(const float height);

		const Vec2 GetPos() const {return m_pos;}
		void SetPos(const Vec2 pos);

		ShaderData* GetShaderData() const {return m_shaderData;}
		void SetShaderData(ShaderData* data) {m_shaderData = data;}

		Shader* GetShader() const {return m_shader;}
		void SetShader(Shader* shader) {m_shader = shader;}

		static luabind::scope Register()
		{
			return
				luabind::class_<Element2D, Element2D*>("Element2D")
				.def(luabind::constructor<float, float, float, float>())
				.def("Init", &Element2D::Init)
 				.property("shader", &Element2D::GetShader, &Element2D::SetShader)
 				.property("shaderData", &Element2D::GetShaderData, &Element2D::SetShaderData);
		}
		
	protected:
		Vec2 m_pos;
		Shader* m_shader;
		ShaderData* m_shaderData;
		Mesh* m_mesh;
		float m_width, m_height;
	};
}

#endif //FALCONENGINE_ELEMENT2D_H