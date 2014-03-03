#ifndef _ODIN_SCENE_CPP
#define _ODIN_SCENE_CPP

namespace Odin {

	inline void Scene::m_AddGameObject (GameObject* gameObject) {

		m_gameObjects.Push(gameObject);
		gameObject->m_scene = this;

		for (uint32 i = gameObject->m_children.Length(); i-- > 0;) {
			GameObject* child = gameObject->m_children[i];

			if (child->m_scene != this) {
				AddGameObject(child);
			}
		}

		m_gameObjectCount++;
	}

	inline void Scene::m_RemoveGameObject (GameObject* gameObject) {
		uint32 i, j;

		for (i = m_gameObjects.Length(); i-- > 0;) {

			if (m_gameObjects[i] == gameObject) {
				m_gameObjects.Splice(i, 1);
				gameObject->m_scene = NULL;

				for (j = gameObject->m_children.Length(); j-- > 0;) {
					GameObject* child = gameObject->m_children[j];

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
		m_gameObjects.Clear();
	}

	inline void Scene::Update (void) {
		for (uint32 i = m_gameObjects.Length(); i-- > 0;) {
			m_gameObjects[i]->Update();
		}
	}

	inline GameObject* Scene::operator [] (int32 i) {
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

	inline uint32 Scene::GameObjectCount (void) const {

		return m_gameObjectCount;
	}

	inline int32 Scene::IndexOf (GameObject* gameObject) {

		if (gameObject != NULL) {

			return m_gameObjects.IndexOf(gameObject);
		}

		return -1;
	}
}
#endif
