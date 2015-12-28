#include "stdafx.h"
#include "GameObject.h"
#include "Mesh.h"
#include "RenderContext.h"
#include "Shader.h"

//////////////////////////////////////////////////////////////////////////
///						LUA REGISTRATION							   ///
//////////////////////////////////////////////////////////////////////////
luabind::scope falcon::GameObjectWrapper::Register()
{
	return
		luabind::class_<GameObject, GameObjectWrapper>("GameObject")
		.def(luabind::constructor<>())
		.def("Update", &GameObject::Update, &GameObjectWrapper::default_Update)
		.def("Init", &GameObject::Init, &GameObjectWrapper::default_Init, luabind::adopt(luabind::result))
		.def("GetTranslate", &GameObject::GetTranslate, &GameObjectWrapper::default_GetTranslate)
		.def("SetTranslate", &GameObject::SetTranslate, &GameObjectWrapper::default_SetTranslate)
		.def("Rotate", &GameObject::Rotate, &GameObjectWrapper::default_Rotate)
		.def("AddForce", &GameObject::AddForce,  &GameObjectWrapper::default_AddForce)

		.property("mesh", &GameObject::GetMesh, &GameObject::SetMesh)
		.property("shader", &GameObject::GetShader, &GameObject::SetShader)
		.property("shaderData", &GameObject::GetShaderData, &GameObject::SetShaderData)
		.property("physicsObject", &GameObject::GetPhysicsObject, &GameObject::SetPhysicsObject);
}

falcon::GameObject::GameObject():m_mesh(0), m_shader(0), m_shaderData(0),m_physicsObject(0)
{
	m_translate = Vec3();
	m_rotate = Mat3();
	m_scale = 1;
}

falcon::GameObject::GameObject( const GameObject& t )
	:m_mesh(t.m_mesh)
	,m_shaderData(t.m_shaderData)
	,m_shader(t.m_shader)
	,m_scale(t.m_scale)
	,m_rotate(t.m_rotate)
	,m_translate(t.m_translate)
{

}

falcon::GameObject::~GameObject()
{
	delete m_shaderData;
	//m_physicsObject is created by LUA and so deleted by LUA
}

void falcon::GameObject::Draw(RenderContext& renderContext)
{
	Mat4 worldMatrix = Mat4();
	worldMatrix.setRotation(m_rotate);
	worldMatrix.setTranslation(m_translate);
	Mat4 worldViewProjectionMatrix = renderContext.GetViewProjectionMatrix() * worldMatrix;

	if(m_shader != 0  && m_mesh != 0 ){
		if(IsVisible(worldViewProjectionMatrix))
		{
			m_shaderData->SetWorldMatrix(worldMatrix);
			m_shaderData->SetWorldViewProjectionMatrix(worldViewProjectionMatrix);
			m_shader->SetShaderData(m_shaderData);
			m_mesh->SetShader(m_shader);
			m_mesh->Draw(/*renderContext*/);
		}
	}
}

falcon::Mesh* falcon::GameObject::GetMesh() const
{
	return m_mesh;
}

void falcon::GameObject::SetMesh( Mesh* mesh )
{
	m_mesh = mesh;
}

void falcon::GameObject::SetShader( Shader* shader )
{
	 m_shader = shader;
}

void falcon::GameObject::SetShaderData( ShaderData* data )
{
	 m_shaderData = data;
}

bool falcon::GameObject::IsVisible(const Mat4& mvpMatrix)
{
	Vec3 pos = mvpMatrix * m_mesh->GetBoundingSphere().center;
	float radius = m_mesh->GetBoundingSphere().radius;

	float leftPlane[4];
	leftPlane[0] = mvpMatrix[3]  + mvpMatrix[0];
	leftPlane[1] = mvpMatrix[7]  + mvpMatrix[4];
	leftPlane[2] = mvpMatrix[11] + mvpMatrix[8];
	leftPlane[3] = mvpMatrix[15] + mvpMatrix[12];
 
	// Normalise the plane
	GLfloat length = sqrtf(leftPlane[0] * leftPlane[0] + leftPlane[1] * leftPlane[1] + leftPlane[2] * leftPlane[2]);
	leftPlane[0] /= length;
	leftPlane[1] /= length;
	leftPlane[2] /= length;
	leftPlane[3] /= length;
 
	// Check the point's location with respect to the left plane of our viewing frustrum
	float distance = leftPlane[0] * pos.x + leftPlane[1] * pos.y + leftPlane[2] * pos.z + leftPlane[3];
	if (distance <= -radius)
	{
		return false; // Bounding sphere is completely outside the left plane
	}
 
	// Check the point's location with respect to the right plane of our viewing frustum
	GLfloat rightPlane[4];
	rightPlane[0] = mvpMatrix[3]  - mvpMatrix[0];
	rightPlane[1] = mvpMatrix[7]  - mvpMatrix[4];
	rightPlane[2] = mvpMatrix[11] - mvpMatrix[8];
	rightPlane[3] = mvpMatrix[15] - mvpMatrix[12];
 
	// Normalise the plane
	length = sqrtf(rightPlane[0] * rightPlane[0] + rightPlane[1] * rightPlane[1] + rightPlane[2] * rightPlane[2]);
	rightPlane[0] /= length;
	rightPlane[1] /= length;
	rightPlane[2] /= length;
	rightPlane[3] /= length;
 
	distance = rightPlane[0] * pos.x + rightPlane[1] * pos.y + rightPlane[2] * pos.z + rightPlane[3];
	if (distance <= -radius)
	{
		return false; // Bounding sphere is completely outside the right plane
	}
 
	// Check the point's location with respect to the bottom plane of our viewing frustum
	float bottomPlane[4];
	bottomPlane[0] = mvpMatrix[3]  + mvpMatrix[1];
	bottomPlane[1] = mvpMatrix[7]  + mvpMatrix[5];
	bottomPlane[2] = mvpMatrix[11] + mvpMatrix[9];
	bottomPlane[3] = mvpMatrix[15] + mvpMatrix[13];
 
	// Normalise the plane
	length = sqrtf(bottomPlane[0] * bottomPlane[0] + bottomPlane[1] * bottomPlane[1] + bottomPlane[2] * bottomPlane[2]);
	bottomPlane[0] /= length;
	bottomPlane[1] /= length;
	bottomPlane[2] /= length;
	bottomPlane[3] /= length;
 
	distance = bottomPlane[0] * pos.x + bottomPlane[1] * pos.y + bottomPlane[2] * pos.z + bottomPlane[3];
	if (distance <= -radius)
	{
		return false; // Bounding sphere is completely outside the bottom plane
	}
 
	// Check the point's location with respect to the top plane of our viewing frustrum
	float topPlane[4];
	topPlane[0] = mvpMatrix[3]  - mvpMatrix[1];
	topPlane[1] = mvpMatrix[7]  - mvpMatrix[5];
	topPlane[2] = mvpMatrix[11] - mvpMatrix[9];
	topPlane[3] = mvpMatrix[15] - mvpMatrix[13];
 
	// Normalise the plane
	length = sqrtf(topPlane[0] * topPlane[0] + topPlane[1] * topPlane[1] + topPlane[2] * topPlane[2]);
	topPlane[0] /= length;
	topPlane[1] /= length;
	topPlane[2] /= length;
	topPlane[3] /= length;
 
	distance = topPlane[0] * pos.x + topPlane[1] * pos.y + topPlane[2] * pos.z + topPlane[3];
	if (distance <= -radius)
	{
		return false; // Bounding sphere is completely outside the top plane
	}
 
	// Check the point's location with respect to the near plane of our viewing frustum
	float nearPlane[4];
	nearPlane[0] = mvpMatrix[3]  + mvpMatrix[2];
	nearPlane[1] = mvpMatrix[7]  + mvpMatrix[6];
	nearPlane[2] = mvpMatrix[11] + mvpMatrix[10];
	nearPlane[3] = mvpMatrix[15] + mvpMatrix[14];
 
	// Normalise the plane
	length = sqrtf(nearPlane[0] * nearPlane[0] + nearPlane[1] * nearPlane[1] + nearPlane[2] * nearPlane[2]);
	nearPlane[0] /= length;
	nearPlane[1] /= length;
	nearPlane[2] /= length;
	nearPlane[3] /= length;
 
	distance = nearPlane[0] * pos.x + nearPlane[1] * pos.y + nearPlane[2] * pos.z + nearPlane[3];
	if (distance <= -radius)
	{
		return false; // Bounding sphere is completely outside the near plane
	}
 
	// Check the point's location with respect to the far plane of our viewing frustum
	GLfloat farPlane[4];
	farPlane[0] = mvpMatrix[3]  - mvpMatrix[2];
	farPlane[1] = mvpMatrix[7]  - mvpMatrix[6];
	farPlane[2] = mvpMatrix[11] - mvpMatrix[10];
	farPlane[3] = mvpMatrix[15] - mvpMatrix[14];
 
	// Normalise the plane
	length = sqrtf(farPlane[0] * farPlane[0] + farPlane[1] * farPlane[1] + farPlane[2] * farPlane[2]);
	farPlane[0] /= length;
	farPlane[1] /= length;
	farPlane[2] /= length;
	farPlane[3] /= length;
 
	distance = farPlane[0] * pos.x + farPlane[1] * pos.y + farPlane[2] * pos.z + farPlane[3];
	if (distance <= -radius)
	{
		return false; // Bounding sphere is completely outside the far plane
	}
 
	// If we got here, then the bounding sphere is within at least all six sides of the view frustum, so it's visible and we should draw it!
	return true;
}

void falcon::GameObject::Rotate( const Vec3& axis, const float degrees )
{
	m_rotate = m_rotate * Quaternion::fromAxisRot(axis, degrees).rotMatrix();
}

//btMotionState
void falcon::GameObject::getWorldTransform (btTransform &worldTrans) const
{
	worldTrans.setOrigin(btVector3(m_translate.x, m_translate.y, m_translate.z));

	falcon::Quaternion fQ = falcon::Quaternion::fromMatrix(m_rotate);
	btQuaternion btQ = btQuaternion(fQ.v.x, fQ.v.y, fQ.v.z, fQ.w);
	worldTrans.setBasis(btMatrix3x3(btQ));
}

void falcon::GameObject::setWorldTransform (const btTransform &worldTrans)
{
	btVector3 btTranslate = worldTrans.getOrigin();
	m_translate.x = btTranslate.x();
	m_translate.y = btTranslate.y();
	m_translate.z = btTranslate.z();

	btQuaternion btRot = worldTrans.getRotation();
	Quaternion qRot(btRot.getW(), btRot.getX(), btRot.getY(), btRot.getZ());
	m_rotate = qRot.rotMatrix();
}
