#ifndef ODIN_SCENE_H
#define ODIN_SCENE_H

namespace Odin {
	
	class BaseGame;

	class Scene : public Object {

		private:
			friend class BaseGame;
			friend class Component;
			friend class GameObject;

			Array<GameObject*> m_gameObjects;
			std::unordered_map<const std::type_info*, Array<Component*>*> m_components;

			uint32 m_gameObjectCount;
			BaseGame* m_game;

			inline void m_AddComponent(Component* component);
			inline void m_RemoveComponent(Component* component);

			inline static float32 m_SortComponents(Component* a, Component* b);
			inline static float32 m_SortComponentTypes(Array<Component*>* a, Array<Component*>* b);

		protected:

			inline void p_Init(void);
			inline void p_Start(void);

		public:
			inline Scene(void);
			inline Scene(const Scene&) = default;
			inline Scene(Scene&&) = default;
			inline ~Scene(void);
			
			inline Scene* Clone(void);
			inline Scene& Copy(const Scene& other);

			inline Scene& AddGameObject(GameObject* gameObject);
			inline Scene& RemoveGameObject(GameObject* gameObject);

			inline uint32 GetGameObjectCount(void);
			inline int32 IndexOf(GameObject* gameObject);
			inline void SortType(Component* component);
			template <typename Type> inline Array<Type*>* GetComponents(void);

			inline void Clear(void);
			inline void Update(void);
			
			inline Scene& operator=(const Scene&)& = default;
			inline Scene& operator=(Scene&&)& = default;
	};
}

#endif