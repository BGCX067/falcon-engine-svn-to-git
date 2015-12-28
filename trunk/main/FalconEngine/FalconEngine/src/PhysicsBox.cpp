#include "stdafx.h"
#include "PhysicsBox.h"
#include "GameObject.h"

//////////////////////////////////////////////////////////////////////////
///						LUA REGISTRATION							   ///
//////////////////////////////////////////////////////////////////////////
luabind::scope falcon::PhysicsBox::Register()
{
	return
		luabind::class_<PhysicsObject, PhysicsBox>("PhysicsBox")
		.def(luabind::constructor<float, Vec3&>())
		.def("Init", &PhysicsBox::Init);
}

falcon::PhysicsBox::PhysicsBox(float mass, Vec3& halfExtends):
	PhysicsObject(mass),
	m_halfExtends(halfExtends)
{
}

falcon::PhysicsBox::~PhysicsBox()
{
	//delete m_motionState;
}

void falcon::PhysicsBox::Init(GameObject* go)
{
	m_motionState = dynamic_cast<btMotionState*>(go);
	m_shape = new btBoxShape(btVector3(m_halfExtends.x,m_halfExtends.y,m_halfExtends.z));
	m_rigidBody = new btRigidBody(m_mass,m_motionState, m_shape);
}