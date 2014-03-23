#ifndef _ODIN_SCENE_H_
#define _ODIN_SCENE_H_

namespace Odin {

	class Scene : public Object {

		private:
			friend class Component;
			friend class GameObject;

			Array<GameObject*> m_gameObjects;
			Array<Array<Component*>*> m_componentsTypes;
			std::unordered_map<const std::type_info*, Array<Component*>*> m_components;
			uint32 m_count;

			inline void m_AddComponent(Component* component);
			inline void m_RemoveComponent(Component* component);

			inline static float32 m_SortComponents(Array<Component*>* a, Array<Component*>* b);

		protected:

			inline void p_Clear(void);

			inline void p_Init(void);
			inline void p_Start(void);
			inline void p_Update(void);

		public:
			inline Scene(void);
			inline Scene(std::string Name);
			inline ~Scene(void);

			inline Scene& AddGameObject(GameObject* gameObject);
			inline Scene& RemoveGameObject(GameObject* gameObject);

			inline uint32 Count(void);
			inline void SortType(Component* component);

			inline void Update(void);
	};
}

#endif