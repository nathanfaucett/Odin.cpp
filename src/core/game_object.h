#ifndef _ODIN_GAME_OBJECT_H_
#define _ODIN_GAME_OBJECT_H_

namespace Odin {

	class GameObject : public Object {

		private:
			friend class Scene;
			friend class Component;

			std::unordered_map<const std::type_info*, Component*> m_components;

		protected:
			Scene* p_scene;

			inline void p_Clear(void);

		public:
			inline GameObject(void);
			inline GameObject(std::string Name);
			inline ~GameObject(void);

			inline void Destroy(void);
			inline Scene* GetScene(void);

			inline GameObject& AddComponent(Component* component);
			inline GameObject& RemoveComponent(Component* component);

			template <typename Type>inline Type* GetComponent(void);
	};
}

#endif