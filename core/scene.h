#ifndef ODIN_SCENE_H
#define ODIN_SCENE_H

namespace Odin {
	class Scene : public Object {
		private:
			std::vector <GameObject*> m_gameObjects;
			unsigned int m_gameObjectCount;

			void m_AddGameObject (GameObject* gameObject) {

				m_gameObjects.push_back(gameObject);
				gameObject->m_scene = this;

				m_gameObjectCount++;
			}

			void m_RemoveGameObject (GameObject* gameObject) {

				for (unsigned i = m_gameObjects.size(); i-- > 0;) {

					if (m_gameObjects[i] == gameObject) {
						m_gameObjects.erase(m_gameObjects.begin() + i);
						gameObject->m_scene = NULL;
						m_gameObjectCount--;
						break;
					}
				}
			}

		protected:

		public:
			Scene() : Object() {
				m_gameObjectCount = 0;
			}

			~ Scene() {
				Deconstructor();
			}

			virtual void Deconstructor () {
				m_gameObjects.clear();
			}

			void Update () {
				for (unsigned i = m_gameObjects.size(); i-- > 0;) {
					m_gameObjects[i]->Update();
				}
			}

			GameObject* operator [] (int i) {
				return m_gameObjects[i];
			}

			void AddGameObject (GameObject* gameObject) {

				if (gameObject != NULL) {
					if (gameObject->m_scene != NULL) {
						gameObject->m_scene->RemoveGameObject(gameObject);
					}

					m_AddGameObject(gameObject);
				}
			}

			void RemoveGameObject (GameObject* gameObject) {

				if (gameObject != NULL) {
					m_RemoveGameObject(gameObject);
				}
			}

			int IndexOf (GameObject* gameObject) {

				if (gameObject != NULL) {

					for (unsigned i = m_gameObjects.size(); i-- > 0;) {

						if (m_gameObjects[i] == gameObject) {
							return i;
						}
					}
				}

				return -1;
			}
	};
}
#endif
