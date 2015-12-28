#ifndef FALCONENGINE_PHYSICSOBJECT_H
#define FALCONENGINE_PHYSICSOBJECT_H

#include "FalconBulletBind.h"
#include "FalconLuaBind.h"

namespace falcon
{
	class GameObject;

	class PhysicsObject
	{
	public:
		PhysicsObject(float mass);
		virtual ~PhysicsObject();

		virtual void Init(GameObject* /*go*/){};

		btRigidBody* GetRigidBody() const {return m_rigidBody;};

		float GetMass() const {return m_mass;};

	protected:
		btRigidBody* m_rigidBody;
		btMotionState* m_motionState;
		float m_mass;
		btCollisionShape* m_shape;
	};
}
#endif // FALCONENGINE_PHYSICSOBJECT_H