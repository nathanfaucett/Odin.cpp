#ifndef _ODIN_SCENE_H
#define _ODIN_SCENE_H

namespace Odin {

	class Scene : public Object {
		private:
			friend class GameObject;

			Array<GameObject*> m_gameObjects;
			uint32 m_gameObjectCount;

			inline void m_AddGameObject (GameObject* gameObject);
			inline void m_RemoveGameObject (GameObject* gameObject);

		protected:

		public:
			inline explicit Scene(void);
			inline ~Scene(void);

			inline virtual void Deconstructor(void);

			inline void Update(void);

			inline GameObject* operator [](int32 i);

			inline void AddGameObject(GameObject* gameObject);
			inline void RemoveGameObject(GameObject* gameObject);

			inline uint32 GameObjectCount(void) const;

			inline int32 IndexOf(GameObject* gameObject);
	};
}
#endif