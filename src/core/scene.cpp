#ifndef ODIN_SCENE_CPP
#define ODIN_SCENE_CPP

namespace Odin {

	inline void Scene::m_AddGameObject (GameObject* gameObject) {

		m_gameObjects.push_back(gameObject);
		gameObject->m_scene = this;

		for (unsigned i = gameObject->m_children.size(); i-- > 0;) {
			GameObject* child = gameObject->m_children[i];

			if (child->m_scene != this) {
				AddGameObject(child);
			}
		}

		m_gameObjectCount++;
	}

	inline void Scene::m_RemoveGameObject (GameObject* gameObject) {

		for (unsigned i = m_gameObjects.size(); i-- > 0;) {

			if (m_gameObjects[i] == gameObject) {
				m_gameObjects.erase(m_gameObjects.begin() + i);
				gameObject->m_scene = NULL;

				for (unsigned i = gameObject->m_children.size(); i-- > 0;) {
					GameObject* child = gameObject->m_children[i];

					if (child->m_scene == this) {
						RemoveGameObject(child);
					}
				}

				m_gameObjectCount--;
				break;
			}
		}
	}

	inline Scene::Scene(void) : Object() {
		m_gameObjectCount = 0;
	}

	inline Scene::~Scene(void) {
		Deconstructor();
	}

	inline void Scene::Deconstructor (void) {
		m_gameObjects.clear();
	}

	inline void Scene::Update (void) {
		for (unsigned i = m_gameObjects.size(); i-- > 0;) {
			m_gameObjects[i]->Update();
		}
	}

	inline GameObject* Scene::operator [] (int i) {
		return m_gameObjects[i];
	}

	inline void Scene::AddGameObject (GameObject* gameObject) {

		if (gameObject != NULL) {
			if (gameObject->m_scene != NULL) {
				gameObject->m_scene->m_RemoveGameObject(gameObject);
			}

			m_AddGameObject(gameObject);
		}
	}

	inline void Scene::RemoveGameObject (GameObject* gameObject) {

		if (gameObject != NULL && gameObject->m_scene == this) {
			m_RemoveGameObject(gameObject);
		}
	}

	inline unsigned int Scene::GameObjectCount (void) const {

		return m_gameObjectCount;
	}

	inline int Scene::IndexOf (GameObject* gameObject) {

		if (gameObject != NULL) {

			for (unsigned i = m_gameObjects.size(); i-- > 0;) {

				if (m_gameObjects[i] == gameObject) {
					return i;
				}
			}
		}

		return -1;
	}
}
#endif
