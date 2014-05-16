#ifndef ODIN_GAME_OBJECT_CPP
#define ODIN_GAME_OBJECT_CPP

namespace Odin {

	inline GameObject::GameObject(void) : Object() {
		m_scene = NULL;
	}

	inline GameObject::~GameObject(void) {
		
		for (auto it = m_components.begin(); it != m_components.end(); ++it) {
			RemoveComponent(it->second);
			delete it->second;
		}
		
		if (m_scene != NULL) {
			m_scene->RemoveGameObject(this);
		}
	}
	
	inline GameObject* GameObject::Clone(void) {
		return &((new GameObject())->Copy(*this));
	}
	
	inline GameObject& GameObject::Copy(const GameObject& other) {
		Clear();
		
		for (auto it = other.m_components.begin(); it != other.m_components.end(); ++it) {
			AddComponent(it->second->Clone());
		}
		
		if (other.m_scene) other.m_scene->AddGameObject(this);
		
		return *this;
	}

	inline void GameObject::Destroy(void) {
		if (m_scene != NULL) {
			m_scene->RemoveGameObject(this);
		}

		Clear();
	}

	inline Scene* GameObject::GetScene(void) {
		return m_scene;
	}

	inline GameObject& GameObject::AddComponent(Component* component) {
		if (component == NULL) {
			return *this;
		}
		const std::type_info* type = &typeid(*component);
		
		if (m_components.count(type) != 0) {
			LogError("GameObject::AddComponent(Component* component) GameObject already has Component");
			return *this;
		}
		
		component->p_gameObject = this;
		m_components[type] = component;

		if (m_scene != NULL) {
			m_scene->m_AddComponent(component);
		}

		return *this;
	}
	template <typename Type> inline GameObject& GameObject::AddComponent(void) {
		AddComponent(new Type());
		return *this;
	}

	inline GameObject& GameObject::RemoveComponent(Component* component) {
		if (component == NULL) {
			return *this;
		}
		const std::type_info* type = &typeid(*component);
		
		if (m_components.count(type) == 0) {
			LogError("GameObject::RemoveComponent(Component* component) GameObject does not have Component");
			return *this;
		}
		
		component->p_gameObject = NULL;
		m_components[&typeid(*component)] = NULL;

		if (m_scene != NULL) {
			m_scene->m_RemoveComponent(component);
		}

		return *this;
	}
	template <typename Type> inline GameObject& GameObject::RemoveComponent(void) {
		const std::type_info* type = &typeid(Type);
		Component* component = m_components[type];
		
		if (component == NULL) {
			return *this;
		}
		
		component->p_gameObject = NULL;
		m_components[type] = NULL;

		if (m_scene != NULL) {
			m_scene->m_RemoveComponent(component);
		}

		return *this;
	}

	inline void GameObject::Clear(void) {

		for (auto it = m_components.begin(); it != m_components.end(); ++it) {
			RemoveComponent(it->second);
		}
		
		if (m_scene != NULL) {
			m_scene->RemoveGameObject(this);
		}
	}

	template <typename Type>inline Type* GameObject::GetComponent(void) {
		const std::type_info* type = &typeid(Type);
		
		if (m_components.count(type) != 0) {
			return static_cast<Type*>(m_components[type]);
		}

		return NULL;
	}
}

#endif