#include "stdafx.h"
#include "Camera.h"



falcon::Camera::Camera():
	m_viewMatrix(Mat4()),
	m_projectionMatrix(Mat4()),
	m_ortho(false),
	m_frustum(Vec4()),
	m_fov(static_cast<float>(DEG2RAD(60.0f))),
	m_nearPlane(0.01f),
	m_farPlane(1000.0f),
	m_aspectRatio(16.0f/9.0f),
	m_lookAt(Vec3(0,0,-1)),
	m_worldUp(Vec3(0,1,0)),
	m_position(Vec3(0,0,0)),
	m_rotation(Mat3()),
	m_scale(1.0f),
	m_isActive(false),
	m_speed(5.0f),
	m_runMultiplier(3.0f)
{
	UpdateProjectionMatrix();
}

falcon::Camera::~Camera()
{
	
}

void falcon::Camera::SetFov(const float fov)
{	
	m_fov = fov;
	m_ortho = false;
	UpdateProjectionMatrix();
}

void falcon::Camera::SetOrtho(float left, float right, float top, float bottom)
{
	m_ortho = true;
	m_frustum.x = left;
	m_frustum.y = right;
	m_frustum.z = top;
	m_frustum.w = bottom;

	UpdateProjectionMatrix();
}

void falcon::Camera::SetNearPlane(const float nearPlane)
{
	m_nearPlane = nearPlane;
	UpdateProjectionMatrix();
}

void falcon::Camera::SetFarPlane(const float farPlane)
{
	m_farPlane = farPlane;
	UpdateProjectionMatrix();
}

void falcon::Camera::SetAspectRatio(const float aspectRatio)
{
	m_aspectRatio = aspectRatio;
	UpdateProjectionMatrix();
}

void falcon::Camera::UpdateProjectionMatrix()
{
	if(m_ortho)
	{
		float rl = (m_frustum.y - m_frustum.x);
		float tb = (m_frustum.z - m_frustum.w);
		float fn = (m_farPlane - m_nearPlane);

		m_projectionMatrix.identity();

		m_projectionMatrix.at(0,0) = 2.0f / rl;
		m_projectionMatrix.at(1,1) = 2.0f / tb;
		m_projectionMatrix.at(2,2) = 1.0f / fn;
		m_projectionMatrix.at(2,3) = m_nearPlane / -fn;
	}else{

		const float yScale = 1.0f / tan(m_fov/2.0f);
		const float xScale = yScale / m_aspectRatio;

		m_projectionMatrix.identity();
		m_projectionMatrix.at(0,0) = xScale;
		m_projectionMatrix.at(1,1) = yScale;
		m_projectionMatrix.at(2,2) = (m_farPlane+m_nearPlane) / (m_nearPlane- m_farPlane);
		m_projectionMatrix.at(2,3) = -1.0f;
		m_projectionMatrix.at(3,2) = (2*m_nearPlane * m_farPlane) / (m_nearPlane- m_farPlane);
		m_projectionMatrix.at(3,3) = 0.0f;
	}
}

void falcon::Camera::UpdateViewMatrix()
{
	Vec3 rightvector = Vec3(m_rotation.at(0,0), m_rotation.at(1,0), m_rotation.at(2,0));
	Vec3 upvector = Vec3(m_rotation.at(0,1), m_rotation.at(1,1), m_rotation.at(2,1));
	Vec3 viewDir = Vec3(m_rotation.at(0,2), m_rotation.at(1,2), m_rotation.at(2,2));

	m_viewMatrix.identity();
	m_viewMatrix.at(0,0) = rightvector.x;
	m_viewMatrix.at(1,0) = rightvector.y;
	m_viewMatrix.at(2,0) = rightvector.z;

	m_viewMatrix.at(0,1) = upvector.x;
	m_viewMatrix.at(1,1) = upvector.y;
	m_viewMatrix.at(2,1) = upvector.z;

	m_viewMatrix.at(0,2) = viewDir.x;
	m_viewMatrix.at(1,2) = viewDir.y;
	m_viewMatrix.at(2,2) = viewDir.z;

	m_viewMatrix.at(3,0) = -rightvector.dotProduct(m_position);
	m_viewMatrix.at(3,1) = -upvector.dotProduct(m_position);
	m_viewMatrix.at(3,2) = -viewDir.dotProduct(m_position);

	m_lookAt = -viewDir;
}

void falcon::Camera::SetPosition(const Vec3& position)
{
	m_position = position;
	UpdateViewMatrix();
}

void falcon::Camera::SetRotation(const Mat3& rotation)
{
	m_rotation = rotation;
	UpdateViewMatrix();
}

void falcon::Camera::SetScale(const float& scale)
{
	m_scale = scale;
	UpdateViewMatrix();
}

void falcon::Camera::SetTransform(const Vec3& translation, const Mat3& rotation, const float& scale)
{
	m_position = translation;
	m_rotation = rotation;
	m_scale = scale;
	UpdateViewMatrix();
}
void falcon::Camera::Place(const Vec3& location, const Vec3& lookatPosition)
{
	SetPosition(location);	
	LookAt(lookatPosition);	
}

void falcon::Camera::LookAt(const Vec3& target)
{

	Vec3 viewDir = target - m_position;
	viewDir.normalize();

	Vec3 rightvector = m_worldUp.crossProduct(viewDir);
	rightvector.normalize();

	Vec3 upvector = viewDir.crossProduct(rightvector);
	upvector.normalize();

	m_rotation.at(0,0) = rightvector.x;
	m_rotation.at(1,0) = rightvector.y;
	m_rotation.at(2,0) = rightvector.z;

	m_rotation.at(0,1) = upvector.x;
	m_rotation.at(1,1) = upvector.y;
	m_rotation.at(2,1) = upvector.z;

	m_rotation.at(0,2) = -viewDir.x;
	m_rotation.at(1,2) = -viewDir.y;
	m_rotation.at(2,2) = -viewDir.z;

	UpdateViewMatrix();
}

