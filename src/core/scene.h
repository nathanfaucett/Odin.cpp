#ifndef ODIN_SCENE_H
#define ODIN_SCENE_H

namespace Odin {
	class Scene : public Object {
		private:
			friend class GameObject;

			std::vector <GameObject*> m_gameObjects;
			unsigned int m_gameObjectCount;

			inline void m_AddGameObject (GameObject* gameObject);
			inline void m_RemoveGameObject (GameObject* gameObject);

		protected:

		public:
			inline explicit Scene(void);
			inline ~Scene(void);

			inline virtual void Deconstructor(void);

			inline void Update(void);

			inline GameObject* operator [](int i);

			inline void AddGameObject(GameObject* gameObject);
			inline void RemoveGameObject(GameObject* gameObject);

			inline unsigned int GameObjectCount(void) const;

			inline int IndexOf(GameObject* gameObject);
	};
}
#endif