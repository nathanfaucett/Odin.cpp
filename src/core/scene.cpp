#ifndef _ODIN_SCENE_CPP_
#define _ODIN_SCENE_CPP_

namespace Odin {

	inline Scene::Scene(void) : Object() {

	}

	inline Scene::Scene(std::string Name) : Object(Name) {

	}

	inline Scene::~Scene(void) {
		p_Clear();
	}

	inline void Scene::p_Clear(void) {
		uint32 i = m_count;

		while (i--) {
			RemoveGameObject(m_gameObjects[i]);
		}

		m_components.clear();
		m_componentsTypes.Clear();
	}

	inline void Scene::p_Init(void) {
		uint32 typesLength = m_componentsTypes.Length(),
		       i, j, length;

		Array<Component*>* components;

		for (i = 0; i < typesLength; i++) {
			components = m_componentsTypes[i];
			length = components->Length();

			for (j = 0; j < length; j++) {
				(*components)[j]->p_Init();
			}
		}
	}

	inline void Scene::p_Start(void) {
		uint32 typesLength = m_componentsTypes.Length(),
		       i, j, length;

		Array<Component*>* components;

		for (i = 0; i < typesLength; i++) {
			components = m_componentsTypes[i];
			length = components->Length();

			for (j = 0; j < length; j++) {
				(*components)[j]->p_Start();
			}
		}
	}

	inline void Scene::p_Update(void) {
		uint32 typesLength = m_componentsTypes.Length(),
		       i, j, length;

		Array<Component*>* components;

		for (i = 0; i < typesLength; i++) {
			components = m_componentsTypes[i];
			length = components->Length();

			for (j = 0; j < length; j++) {
				(*components)[j]->p_Update();
			}
		}
	}

	inline Scene& Scene::AddGameObject(GameObject* gameObject) {
		if (gameObject == NULL) {
			return *this;
		}

		int32 index = m_gameObjects.IndexOf(gameObject);

		if (index == -1) {
			gameObject->p_scene = this;
			m_gameObjects.Push(gameObject);

			m_count++;

			for (auto it = gameObject->m_components.begin(); it != gameObject->m_components.end(); ++it) {
				m_AddComponent(it->second);
			}

		} else {

		}

		return *this;
	}

	inline void Scene::m_AddComponent(Component* component) {
		if (component == NULL) {
			return;
		}

		const std::type_info* type = &typeid(*component);
		Array<Component*>* types;
		int32 index;

		if (m_components.count(type) == 0) {
			types = new Array<Component*>;

			m_components[type] = types;
			m_componentsTypes.Push(types);

			m_componentsTypes.Sort(m_SortComponents);

		} else {
			types = m_components[type];
		}

		index = types->IndexOf(component);

		if (index == -1) {
			types->Push(component);
			types->Sort(component->p_Sort);
		}
	}

	inline float32 Scene::m_SortComponents(Array<Component*>* a, Array<Component*>* b) {

		return (*a)[0]->p_order - (*b)[0]->p_order;
	}

	inline void Scene::SortType(Component* component) {

		m_components[&typeid(*component)]->Sort(component->p_Sort);
	}

	inline Scene& Scene::RemoveGameObject(GameObject* gameObject) {
		if (gameObject == NULL) {
			return *this;
		}

		int32 index = m_gameObjects.IndexOf(gameObject);

		if (index != -1) {
			gameObject->p_scene = NULL;
			m_gameObjects.Splice(index, 1);

			m_count--;

			for (auto it = gameObject->m_components.begin(); it != gameObject->m_components.end(); ++it) {
				m_RemoveComponent(it->second);
			}

		} else {

		}

		return *this;
	}

	inline void Scene::m_RemoveComponent(Component* component) {
		if (component == NULL) {
			return;
		}

		const std::type_info* type = &typeid(*component);
		Array<Component*>* types;
		int32 index;

		if (m_components.count(type) != 0) {
			types = m_components[type];

		} else {
			return;
		}

		index = types->IndexOf(component);

		if (index != -1) {
			types->Splice(index, 1);

			if (types->Length() == 0) {
				m_components.erase(type);
				index = m_componentsTypes.IndexOf(types);

				if (index != -1) {
					m_componentsTypes.Splice(index, 1);
				}
			}
		}
	}

	inline uint32 Scene::Count(void) {
		return m_count;
	}

	inline void Scene::Update(void) {
		p_Update();
	}
}

#endif