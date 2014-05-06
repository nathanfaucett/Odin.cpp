#ifndef ODIN_GAME_OBJECT_H
#define ODIN_GAME_OBJECT_H

namespace Odin {

	class GameObject : public Object {

		private:
			friend class Scene;
			friend class Component;

			std::unordered_map<const std::type_info*, Component*> m_components;

		protected:
			Scene* p_scene;

		public:
			inline GameObject(void);
			inline GameObject(const GameObject&) = default;
			inline GameObject(GameObject&&) = default;
			inline ~GameObject(void);
			
			inline GameObject* Clone(void);
			inline GameObject& Copy(const GameObject& other);

			inline void Destroy(void);
			inline Scene* GetScene(void);

			inline GameObject& AddComponent(Component* component);
			inline GameObject& RemoveComponent(Component* component);
			
			inline void Clear(void);
			
			template <typename Type>inline Type* GetComponent(void);
			
			inline GameObject& operator=(const GameObject&)& = default;
			inline GameObject& operator=(GameObject&&)& = default;
	};
}

#endif