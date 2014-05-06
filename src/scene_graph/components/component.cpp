#ifndef ODIN_COMPONENT_CPP
#define ODIN_COMPONENT_CPP

namespace Odin {
	
	inline Component::Component(void) : Object() {
		p_gameObject = NULL;
	}
	
	inline Component::~Component(void) {}
	
	inline Component* Component::Clone(void) {
		return this;
	}

	inline Component& Component::Copy(const Component& other) {
		return *this;
	}

	inline void Component::p_Init(void) {

	}

	inline void Component::p_Start(void) {

	}

	inline void Component::p_Sort(void) {
		p_order = 0.0f;
	}

	inline void Component::Update(void) {

	}

	inline void Component::Clear(void) {
		if (p_gameObject != NULL) {
			p_gameObject->RemoveComponent(this);
		}
	}

	inline GameObject* Component::GetGameObject(void) {
		return p_gameObject;
	}

	inline Scene* Component::GetScene(void) {
		if (p_gameObject != NULL) {
			return p_gameObject->p_scene;
		}

		return NULL;
	}
}

#endif