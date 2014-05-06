#ifndef ODIN_GAME_OBJECT_CPP
#define ODIN_GAME_OBJECT_CPP

namespace Odin {

	inline GameObject::GameObject(void) : Object() {
		p_scene = NULL;
	}

	inline GameObject::~GameObject(void) {
		
		for (auto it = m_components.begin(); it != m_components.end(); ++it) {
			RemoveComponent(it->second);
			delete it->second;
		}
		
		if (p_scene != NULL) {
			p_scene->RemoveGameObject(this);
		}
	}
	
	inline GameObject* GameObject::Clone(void) {
		return &((new GameObject())->Copy(*this));
	}
	
	inline GameObject& GameObject::Copy(const GameObject& other) {
		
		for (auto it = other.m_components.begin(); it != other.m_components.end(); ++it) {
			AddComponent(it->second->Clone());
		}
		
		return *this;
	}

	inline void GameObject::Destroy(void) {
		if (p_scene != NULL) {
			p_scene->RemoveGameObject(this);
		}

		Clear();
	}

	inline Scene* GameObject::GetScene(void) {
		return p_scene;
	}

	inline GameObject& GameObject::AddComponent(Component* component) {
		if (component == NULL) {
			return *this;
		}
		
		component->p_gameObject = this;
		m_components[&typeid(*component)] = component;

		if (p_scene != NULL) {
			p_scene->m_AddComponent(component);
		}

		return *this;
	}

	inline GameObject& GameObject::RemoveComponent(Component* component) {
		if (component == NULL) {
			return *this;
		}
		
		component->p_gameObject = NULL;
		m_components[&typeid(*component)] = NULL;

		if (p_scene != NULL) {
			p_scene->m_RemoveComponent(component);
		}

		return *this;
	}

	inline void GameObject::Clear(void) {

		for (auto it = m_components.begin(); it != m_components.end(); ++it) {
			RemoveComponent(it->second);
		}
		
		if (p_scene != NULL) {
			p_scene->RemoveGameObject(this);
		}
	}

	template <typename Type>inline Type* GameObject::GetComponent(void) {

		if (m_components.count(&typeid(Type)) != 0) {
			return static_cast<Type*>(m_components[&typeid(Type)]);
		}

		return NULL;
	}
}

#endif