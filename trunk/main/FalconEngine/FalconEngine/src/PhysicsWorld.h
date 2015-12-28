#ifndef FALCONENGINE_PHYSICSWORLD_H
#define FALCONENGINE_PHYSICSWORLD_H

#include "InputState.h"

#include "FalconBulletBind.h"

namespace falcon
{
	class GameObject;

	class PhysicsWorld
	{
	public:
		PhysicsWorld();
		virtual ~PhysicsWorld();

		void Init();
		void Update(const InputState& inputState);
		void DebugDraw();
		void AddObject(GameObject* object);
	private:
		btDefaultCollisionConfiguration* m_collisionConfiguration;
		btCollisionDispatcher* m_dispatcher;
		btBroadphaseInterface* m_overlappingPairCache;
		btSequentialImpulseConstraintSolver* m_solver;
		btDiscreteDynamicsWorld* m_world;
		btIDebugDraw* m_debugRenderer;

		btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

		PhysicsWorld(const PhysicsWorld& t);
		PhysicsWorld& operator=(const PhysicsWorld& t);
	};
}
#endif // FALCONENGINE_PHYSICSWORLD_H