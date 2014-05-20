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
	
	inline void Scene::m_Sort(void) {
		
		for (auto it = m_components.begin(); it != m_components.end(); ++it) {
			const std::type_info* type = it->first;
			Array<Component*>* components = it->second;
			
			if (m_componentsNeedsSort[type] == true) {
				(*components)[0]->p_Sort();
				m_componentsNeedsSort[type] = false;
			}
		}
	}
	
	template <typename Type> inline void Scene::SortType(void) {
		const std::type_info* type = &typeid(Type);
		Array<Component*>* components = m_components[type];
		
		if (components != NULL) {
			Component* component = (*components)[0];
			
			if (component != NULL) {
				component->p_Sort();
				m_componentsNeedsSort[type] = false;
			}
		}
	}
	
	inline Scene* Scene::Clone(void) {
		return &((new Scene())->Copy(*this));
	}
	
	inline Scene& Scene::Copy(const Scene& other) {
		Clear();
		
		for (uint32 i = 0, length = other.m_gameObjectCount; i < length; i++) {
			AddGameObject(new GameObject(*(other.m_gameObjects[i])));
		}
		
		return *this;
	}

	inline void Scene::p_Init(void) {
		m_Sort();
		
		for (auto it = m_components.begin(); it != m_components.end(); ++it) {
			Array<Component*>* components = it->second;
			for (uint32 i = 0, il = components->Length(); i < il; i++) (*components)[i]->p_Init();
		}
	}

	inline void Scene::p_Start(void) {
		m_Sort();
		
		for (auto it = m_components.begin(); it != m_components.end(); ++it) {
			Array<Component*>* components = it->second;
			for (uint32 i = 0, il = components->Length(); i < il; i++) (*components)[i]->p_Start();
		}
	}

	inline Scene& Scene::AddGameObject(GameObject* gameObject) {
		if (gameObject == NULL) {
			return *this;
		}

		int32 index = m_gameObjects.IndexOf(gameObject);

		if (index == -1) {
			gameObject->m_scene = this;
			m_gameObjects.Push(gameObject);

			m_gameObjectCount++;

			for (auto it = gameObject->m_components.begin(); it != gameObject->m_components.end(); ++it) {
				Component* component = it->second;
				
				m_AddComponent(component);
				if (m_game != NULL) {
					component->p_Init();
				}
			}
			
			if (m_game != NULL) {
				for (auto it = gameObject->m_components.begin(); it != gameObject->m_components.end(); ++it) {
					it->second->p_Start();
				}
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
		Array<Component*>* components = m_components[type];
		m_componentsNeedsSort[type] = true;

		if (components == NULL) {
			components = new Array<Component*>;
			m_components[type] = components;
		}

		components->Push(component);
	}

	inline Scene& Scene::RemoveGameObject(GameObject* gameObject) {
		if (gameObject == NULL) {
			return *this;
		}
		int32 index = m_gameObjects.IndexOf(gameObject);

		if (index != -1) {
			gameObject->m_scene = NULL;
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
		Array<Component*>* components = m_components[type];

		if (components == NULL) return;
		
		int32 index = components->IndexOf(component);
		if (index != -1)  {
			components->Splice(index, 1);
		}
		
		if (components->Length() == 0) {
			m_components[type] = NULL;
			delete components;
		}
	}

	inline uint32 Scene::GetGameObjectCount(void) {
		return m_gameObjectCount;
	}

	inline int32 Scene::IndexOf(GameObject* gameObject) {
		return (gameObject == NULL) ? -1 : m_gameObjects.IndexOf(gameObject);
	}

	inline void Scene::Update(void) {
		m_Sort();
		
		for (auto it = m_components.begin(); it != m_components.end(); ++it) {
			Array<Component*>* components = it->second;
			for (uint32 i = 0, il = components->Length(); i < il; i++) (*components)[i]->Update();
		}
	}

	inline void Scene::Clear(void) {
		uint32 i = m_gameObjects.Length();
		
		while (i--) {
			RemoveGameObject(m_gameObjects[i]);
		}
	}
	
	template <typename Type> inline Array<Type*>* Scene::GetComponents(void) {
		const std::type_info* type = &typeid(Type);
		if (m_components.count(type) != 0) {
			return reinterpret_cast<Array<Type*>*>(m_components[type]);
		}

		return NULL;
	}
}

#endif