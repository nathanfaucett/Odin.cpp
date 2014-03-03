#ifndef _ODIN_GAME_OBJECT_H
#define _ODIN_GAME_OBJECT_H

namespace Odin {

	class Scene;

	class GameObject : public Object {

		private:
			friend class Scene;

			Array<GameObject*> m_children;

			Scene* m_scene;

			Camera* m_camera;

			GameObject* m_parent;
			GameObject* m_root;
			uint32 m_depth;
			uint32 m_childCount;

			inline void m_RemoveParent(void);
			inline void m_UpdateDepth(uint32 depth);

			inline void m_AddComponent(const std::string type);
			inline void m_RemoveComponent(const std::string type);

		protected:

		public:
			Vec3 position, scale;
			Quat rotation;

			Mat4 matrix, matrixWorld;

			inline explicit GameObject(void);
			inline GameObject(const GameObject& other);
			inline ~GameObject(void);

			inline virtual void Deconstructor(void);

			inline virtual GameObject* Clone(void);
			inline virtual GameObject& Copy(const GameObject& other);

			inline void Update(void);

			inline void Destroy(void);

			inline GameObject* operator [] (int32 i);

			inline void AddComponent(const Component* component);
			inline void RemoveComponent(const Component* component);

			inline GameObject* GetParent(void) const;
			inline uint32 GetDepth(void) const;

			inline void SetParent(GameObject* parent);
			inline void AddChild(GameObject* child);
			inline void RemoveChild(GameObject* child);

			inline void DetachChildren(void);
			inline int32 IndexOf(GameObject* child);
	};
}

#endif