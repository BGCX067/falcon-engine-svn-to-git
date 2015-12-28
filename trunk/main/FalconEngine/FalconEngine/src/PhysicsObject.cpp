#include "stdafx.h"
#include "PhysicsObject.h"
#include "GameObject.h"



falcon::PhysicsObject::PhysicsObject(float mass):
	m_rigidBody(nullptr),
	m_motionState(nullptr),
	m_shape(nullptr),
	m_mass(mass)
{
}

falcon::PhysicsObject::~PhysicsObject()
{
	delete m_shape;
	delete m_rigidBody;
}