#ifndef FALCONENGINE_PHYSICSBOX_H
#define FALCONENGINE_PHYSICSBOX_H

#include "PhysicsObject.h"
#include "FalconMath.h"

namespace falcon
{
	class GameObject;

	class PhysicsBox : public PhysicsObject
	{
	public:
		PhysicsBox(float mass, Vec3& halfExtends);
		virtual ~PhysicsBox();

		virtual void Init(GameObject* go);

		static luabind::scope Register();

	private:
		Vec3 m_halfExtends;

		PhysicsBox(const PhysicsBox& t);
		PhysicsBox& operator=(const PhysicsBox& t);
	};
}
#endif // FALCONENGINE_PHYSICSBOX_H