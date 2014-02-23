#ifndef ODIN_COMPONENT_CPP
#define ODIN_COMPONENT_CPP

namespace Odin {

	inline Component::Component(void) : Object() {
		m_gameObject = NULL;
	}

	inline Component::~Component(void) {
		Deconstructor();
	}

	inline void Component::Deconstructor(void) {
		m_gameObject = NULL;
	}

	inline void Component::Update(void) {

	}

	inline void Component::Destroy(void) {

		if (m_gameObject != NULL) {
			m_gameObject->RemoveComponent(this);
		}
	}

	inline GameObject* Component::GetGameObject(void) {

		return m_gameObject;
	}
}

#endif