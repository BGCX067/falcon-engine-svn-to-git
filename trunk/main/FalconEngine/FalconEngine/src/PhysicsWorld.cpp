#include "stdafx.h"
#include "PhysicsWorld.h"
#include "PhysicsDebugRenderer.h"
#include "GameObject.h"
#include "PhysicsObject.h"

falcon::PhysicsWorld::PhysicsWorld(): 
	m_collisionConfiguration(0), 
	m_dispatcher(0),
	m_overlappingPairCache(0),
	m_solver(0),
	m_world(0), 
	m_debugRenderer(0)
{
	
}

falcon::PhysicsWorld::~PhysicsWorld()
{
	delete m_world;
	delete m_solver;
	delete m_overlappingPairCache;
	delete m_dispatcher;
	delete m_collisionConfiguration;
	delete m_debugRenderer;
}

void falcon::PhysicsWorld::Init()
{
	///collision configuration contains default setup for memory, collision setup
	m_collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher
	m_dispatcher = new	btCollisionDispatcher(m_collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase
	m_overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver
	m_solver = new btSequentialImpulseConstraintSolver;

	m_world = new btDiscreteDynamicsWorld(m_dispatcher,m_overlappingPairCache,m_solver,m_collisionConfiguration);

	//m_debugRenderer = new PhysicsDebugRenderer();
	//m_debugRenderer->setDebugMode(btIDebugDraw::DBG_FastWireframe);

	m_world->setGravity(btVector3(0,-9.81f,0));
	m_world->setDebugDrawer(m_debugRenderer);
}

void falcon::PhysicsWorld::Update(const InputState& inputState)
{
	m_world->stepSimulation(inputState.GetDeltaTime());
}

void falcon::PhysicsWorld::DebugDraw()
{
	m_world->debugDrawWorld();
}

void falcon::PhysicsWorld::AddObject(GameObject* gObj)
{
	assert(gObj != nullptr);
	if(gObj->GetPhysicsObject() != 0)
	{
		PhysicsObject* phObj = gObj->GetPhysicsObject();

		if(phObj->GetMass() > 0)
		{
			m_world->addRigidBody(gObj->GetPhysicsObject()->GetRigidBody());
		}
		else
		{
			phObj->GetRigidBody()->setCollisionFlags( phObj->GetRigidBody()->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
			phObj->GetRigidBody()->setActivationState(DISABLE_DEACTIVATION);
			m_world->addCollisionObject(phObj->GetRigidBody());
		}
	}
}