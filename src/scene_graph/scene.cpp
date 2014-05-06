#ifndef ODIN_SCENE_CPP
#define ODIN_SCENE_CPP

namespace Odin {

	inline Scene::Scene(void) : Object() {
		m_gameObjectCount = 0;
	}
	inline Scene::~Scene(void) {
		uint32 i = m_gameObjects.Length();
		
		while (i--) {
			GameObject* gameObject = m_gameObjects[i];
			RemoveGameObject(gameObject);
			delete gameObject;
		}
	}
	
	inline Scene* Scene::Clone(void) {
		return &((new Scene())->Copy(*this));
	}
	
	inline Scene& Scene::Copy(const Scene& other) {
		m_gameObjectCount = 0;
		
		for (uint32 i = 0, length = other.m_gameObjectCount; i < length; i++) {
			AddGameObject(new GameObject(*(other.m_gameObjects[i])));
		}
		
		return *this;
	}

	inline void Scene::p_Init(void) {
		
		for (auto it = m_components.begin(); it != m_components.end(); ++it) {
			Array<Component*>* components = it->second;

			for (uint32 i = 0, length = components->Length(); i < length; i++) {
				(*components)[i]->p_Init();
			}
		}
	}

	inline void Scene::p_Start(void) {
		
		for (auto it = m_components.begin(); it != m_components.end(); ++it) {
			Array<Component*>* components = it->second;
			
			for (uint32 i = 0, length = components->Length(); i < length; i++) {
				(*components)[i]->p_Start();
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

			m_gameObjectCount++;

			for (auto it = gameObject->m_components.begin(); it != gameObject->m_components.end(); ++it) {
				m_AddComponent(it->second);
			}

		} else {
			LogError("Scene::AddGameObject(GameObject* gameObject) gameObject already member of Scene");
		}

		return *this;
	}

	inline void Scene::m_AddComponent(Component* component) {
		if (component == NULL) {
			return;
		}

		const std::type_info* type = &typeid(*component);
		Array<Component*>* types = m_components[type];
		int32 index;

		if (types == NULL) {
			types = new Array<Component*>;
			m_components[type] = types;
		}

		index = types->IndexOf(component);

		if (index == -1) {
			types->Push(component);

			for (uint32 i = types->Length(); i-- > 0;) {
				(*types)[i]->p_Sort();
			}

			types->Sort(m_SortComponents);
		}
	}

	inline float32 Scene::m_SortComponents(Component* a, Component* b) {

		return a->p_order - b->p_order;
	}

	inline float32 Scene::m_SortComponentTypes(Array<Component*>* a, Array<Component*>* b) {

		return float32((*a)[0]->p_updateOrder) - float32((*b)[0]->p_updateOrder);
	}

	inline void Scene::SortType(Component* component) {
		Array<Component*>* types = m_components[&typeid(*component)];

		for (uint32 i = types->Length(); i-- > 0;) {
			(*types)[i]->p_Sort();
		}

		types->Sort(m_SortComponents);
	}

	inline Scene& Scene::RemoveGameObject(GameObject* gameObject) {
		if (gameObject == NULL) {
			return *this;
		}

		int32 index = m_gameObjects.IndexOf(gameObject);

		if (index != -1) {
			gameObject->p_scene = NULL;
			m_gameObjects.Splice(index, 1);

			m_gameObjectCount--;

			for (auto it = gameObject->m_components.begin(); it != gameObject->m_components.end(); ++it) {
				m_RemoveComponent(it->second);
			}

		} else {
			LogError("Scene::RemoveGameObject(GameObject* gameObject) gameObject not a member of Scene");
		}

		return *this;
	}

	inline void Scene::m_RemoveComponent(Component* component) {
		if (component == NULL) {
			return;
		}

		const std::type_info* type = &typeid(*component);
		Array<Component*>* types;

		if (m_components.count(type) != 0) {
			types = m_components[type];
		} else {
			return;
		}

		int32 index = types->IndexOf(component);

		if (index != -1) {
			types->Splice(index, 1);

			if (types->Length() == 0) {
				m_components.erase(type);
			}
		}
	}

	inline uint32 Scene::GetGameObjectCount(void) {
		return m_gameObjectCount;
	}

	inline int32 Scene::IndexOf(GameObject* gameObject) {
		return (gameObject == NULL) ? -1 : m_gameObjects.IndexOf(gameObject);
	}

	inline void Scene::Update(void) {
		
		for (auto it = m_components.begin(); it != m_components.end(); ++it) {
			Array<Component*>* components = it->second;
			
			for (uint32 i = 0, length = components->Length(); i < length; i++) {
				(*components)[i]->Update();
			}
		}
	}

	inline void Scene::Clear(void) {
		uint32 i = m_gameObjects.Length();
		
		while (i--) {
			RemoveGameObject(m_gameObjects[i]);
		}
	}
	
	template <typename Type> inline Array<Type*>* Scene::GetComponents(void) {
		
		if (m_components.count(&typeid(Type)) != 0) {
			return reinterpret_cast<Array<Type*>*>(m_components[&typeid(Type)]);
		}

		return NULL;
	}
}

#endif