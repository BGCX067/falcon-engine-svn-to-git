#ifndef FALCONENGINE_CAMERA_H
#define FALCONENGINE_CAMERA_H

#include "FalconMath.h"
#include "InputState.h"

namespace falcon
{
	#define CAMERA_MOUSE_SCALE 10

	class Camera
	{
	public:
		Camera();
		 virtual ~Camera();

		virtual void Update(const InputState* inputState) = 0;

		virtual void Place(const Vec3& location, const Vec3& lookAt);
		virtual void LookAt(const Vec3& lookAt);

		virtual void SetOrtho(float left, float right, float top, float bottom);
		virtual void UnSetOrtho(){UpdateProjectionMatrix();}

		virtual const Mat4& GetViewMatrix() const {return m_viewMatrix;}
		virtual const Mat4& GetProjectionMatrix() const {return m_projectionMatrix;}

		//void SetViewMatrix(Vec3 position, Vec3 lookDirection);
		//void SetProjectionMatrix(const Mat4& matrix);				

		virtual const Vec3 GetWorldUp(){return m_worldUp;}

		virtual void SetPosition(const Vec3& position);
		virtual void SetRotation(const Mat3& rotation);
		virtual void SetScale(const float& scale);
		virtual void SetTransform(const Vec3& translation, const Mat3& rotation, const float& scale);

		virtual void SetFov(const float fov);
		virtual void SetNearPlane(const float nearPlane);
		virtual void SetFarPlane(const float nearPlane);
		virtual void SetAspectRatio(const float aspectRatio);

		virtual const Vec3 GetPosition() const {return m_position;}
		virtual float GetFov() const {return m_fov;}
		virtual float GetNearPlane() const {return m_nearPlane;}
		virtual float GetFarPlane() const {return m_farPlane;}
		virtual float GetAspectRatio() const {return m_aspectRatio;}

		//when cam is active it registers user input
		virtual void Activate(){m_isActive = true;}
		//when cam is disabled it ignores user input
		virtual void Deactivate(){m_isActive = false;}

	protected:
		virtual void UpdateProjectionMatrix();
		virtual void UpdateViewMatrix();
		//test variables
		GLfloat m_projMatrixGL[16];
		GLfloat m_modelViewMatrixGL[16];

		Mat4 m_viewMatrix;
		Mat4 m_projectionMatrix;

		bool m_ortho;

		Vec4 m_frustum;

		float m_fov;
		float m_nearPlane;
		float m_farPlane;		
		float m_aspectRatio;

		Vec3 m_lookAt;
		Vec3 m_worldUp;

		Vec3 m_position;
		Mat3 m_rotation;
		float m_scale;
		
		bool m_isActive;
		float m_speed;
		float m_runMultiplier;
	private:
		Camera(const Camera& scene);
		Camera& operator=(const Camera& scene);
	};
}

#endif //FALCONENGINE_CAMERA_H