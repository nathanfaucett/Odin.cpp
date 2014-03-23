#ifndef _ODIN_GAME_OBJECT_CPP_
#define _ODIN_GAME_OBJECT_CPP_

namespace Odin {

	inline GameObject::GameObject(void) : Object() {

	}

	inline GameObject::GameObject(std::string Name) : Object(Name) {

	}

	inline GameObject::~GameObject(void) {
		p_Clear();
	}

	inline void GameObject::p_Clear(void) {
		p_scene = NULL;
	}

	inline void GameObject::Destroy(void) {
		if (p_scene != NULL) {
			p_scene->RemoveGameObject(this);
		}

		p_Clear();
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
		m_components.erase(&typeid(*component));

		if (p_scene != NULL) {
			p_scene->m_RemoveComponent(component);
		}

		return *this;
	}

	template <typename Type>inline Type* GameObject::GetComponent(void) {

		if (m_components.count(&typeid(Type)) != 0) {
			return static_cast<Type*>(m_components[&typeid(Type)]);
		}

		return NULL;
	}
}

#endif