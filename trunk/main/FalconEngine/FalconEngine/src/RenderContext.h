#ifndef FALCONENGINE_RENDERCONTEXT_H
#define FALCONENGINE_RENDERCONTEXT_H

#include "FalconMath.h"

namespace falcon
{

	class RenderContext
	{
	public:
		RenderContext();
		~RenderContext();

		//RenderProperties
		const Mat4& GetViewMatrix() const {return m_viewMatrix;}
		const Mat4& GetProjectionMatrix() const {return m_projectionMatrix;}
		const Mat4& GetViewProjectionMatrix() const {return m_viewProjectionMatrix;}
		const Vec4& GetCameraPos() const {return m_cameraPos;}
		const Mat4& GetWorldMatrix() const {return m_worldMatrix;}
		void SetViewProjectionMatrix(const Mat4& view, const Mat4& projection);
		void SetCameraPos(const Vec3& pos) {m_cameraPos = Vec4(pos.x, pos.y, pos.z, 1);}
		void SetWorldMatrix(const Mat4& world) {m_worldMatrix = world;}
		//LightProperties
		//const Vec3& GetAmbientColor() const {return m_ambientColor;}
		//const Vec3& GetLightDirection() const {return m_lightDirection;}
		const Vec3& GetDiffuseColor() const {return m_diffuseColor;}
		//const Vec3& GetSpecularColor() const {return m_specularColor;}

	private:
		Mat4 m_viewMatrix;
		Mat4 m_projectionMatrix;
		Mat4 m_viewProjectionMatrix;
		Mat4 m_worldMatrix;
		Vec4 m_cameraPos;

		//Vec3 m_ambientColor;
		//Vec3 m_lightDirection;
		Vec3 m_diffuseColor;
		//Vec3 m_specularColor;
	};
}

#endif /*FALCONENGINE_RENDERCONTEXT_H*/