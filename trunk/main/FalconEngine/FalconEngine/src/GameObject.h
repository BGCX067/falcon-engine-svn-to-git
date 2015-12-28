#ifndef FALCONENGINE_GAMEOBJECT_H
#define FALCONENGINE_GAMEOBJECT_H

#include "FalconMath.h"
#include "RenderContext.h"
#include "InputState.h"
#include "FalconLuaBind.h"
#include "ResourceManager.h"
#include "FalconBulletBind.h"
#include "PhysicsObject.h"
#include "MotionState.h"

namespace falcon
{
	class Mesh;
	class Shader;
	class ShaderData;
	class ResourceManager;

	class GameObject: public MotionState
	{
	public:
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& t);
		
		virtual const std::string GetName(){return m_name;};
		virtual void SetName(std::string name){m_name = name;};

		virtual const Vec3& GetTranslate(){return m_translate;};
		virtual const Mat3& GetRotate(){return m_rotate;};
		virtual float GetScale(){return m_scale;};

		virtual void SetTranslate(const Vec3& translate){m_translate = translate;};
		virtual void SetRotate(const Mat3& rotate){m_rotate = rotate;};
		virtual void SetScale(float scale){m_scale = scale;};

		virtual void Rotate(const Vec3& axis, const float degrees);

		virtual void Init(ResourceManager* resourceManager) {resourceManager;}/*0*/;
		virtual void Update(InputState* inputState) {inputState;}/*=0*/;

		virtual Mesh* GetMesh() const;
		virtual void SetMesh(Mesh* mesh);

		virtual ShaderData* GetShaderData() const {return m_shaderData;};
		virtual void SetShaderData(ShaderData* data);

		virtual PhysicsObject* GetPhysicsObject() const {return m_physicsObject;};
		virtual void SetPhysicsObject(PhysicsObject* physicsObject){m_physicsObject = physicsObject;};

		virtual Shader* GetShader() const {return m_shader;};
		virtual void SetShader(Shader* shader);

		//not virtual (shouldn't be called by hand)
		void Draw(RenderContext& renderContext);

		virtual void getWorldTransform (btTransform &worldTrans) const;
		virtual void setWorldTransform (const btTransform &worldTrans);

		//testfunc
		virtual void AddForce(Vec3& force)
		{
			m_physicsObject->GetRigidBody()->applyForce(btVector3(force.x, force.y, force.z), btVector3(m_translate.x+1, m_translate.y, m_translate.z));
		
		}
	protected:
		bool IsVisible(const Mat4& wvpMatrix);

		Vec3 m_translate;
		Mat3 m_rotate;
		float m_scale;

		std::string m_name;
		Mesh* m_mesh;
		Shader* m_shader;
		ShaderData* m_shaderData;
		PhysicsObject* m_physicsObject;

	private:
		GameObject& operator=(const GameObject& t);
	};

	struct GameObjectWrapper: GameObject
	{
		GameObjectWrapper():GameObject(){};
		virtual ~GameObjectWrapper(){};

		static luabind::scope Register();

		virtual void AddForce(Vec3& force) { call<void>("AddForce", force); }
		static void default_AddForce( GameObject* ptr, Vec3& force) { return ptr->GameObject::AddForce(force); }

		virtual void Rotate( const Vec3& axis, const float degrees ) { call<void>("Rotate", axis, degrees); }
		static void default_Rotate( GameObject* ptr, const Vec3& axis, const float degrees) { return ptr->GameObject::Rotate(axis, degrees); }

		virtual const Vec3& GetTranslate() { return call<const Vec3&>("GetTranslate"); }
		static const Vec3& default_GetTranslate(GameObject* ptr) { return ptr->GameObject::GetTranslate(); }

		virtual void SetTranslate(const Vec3& translate) { call<void>("SetTranslate", translate); }
		static void default_SetTranslate(GameObject* ptr, const Vec3& translate) { return ptr->GameObject::SetTranslate(translate); }

		virtual void Init(ResourceManager* resourceManager) { call<void>("Init", resourceManager) ;}
		static void default_Init(GameObject* ptr, ResourceManager* resourceManager) { return ptr->GameObject::Init(resourceManager); }

		virtual void Update(InputState* inputState) { call<void>("Update", inputState); }
		static void default_Update(GameObject* ptr, InputState* inputState) { return ptr->GameObject::Update(inputState); }
	};
}

#endif //FALCONENGINE_GAMEOBJECT_H
