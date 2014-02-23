#ifndef ODIN_GAME_OBJECT_H
#define ODIN_GAME_OBJECT_H

namespace Odin {

	struct Scene;

	class GameObject : public Object {

		private:
			friend class Scene;

			std::vector<GameObject*> m_children;

			Scene* m_scene;

			GameObject* m_parent;
			GameObject* m_root;
			unsigned int m_depth;
			unsigned int m_childCount;

			inline void m_RemoveParent(void);
			inline void m_UpdateDepth(unsigned int depth);

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

			inline GameObject* operator [] (int i);

			inline GameObject* GetParent(void) const;
			inline unsigned int GetDepth(void) const;

			inline void SetParent(GameObject* parent);

			inline void AddChild(GameObject* child);
			inline void RemoveChild(GameObject* child);

			inline void DetachChildren(void);
			inline int IndexOf(GameObject* child);
	};
}

#endif