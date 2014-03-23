#ifndef _ODIN_COMPONENT_CPP_
#define _ODIN_COMPONENT_CPP_

namespace Odin {

	inline Component::Component(void) : Object() {
		
	}

	inline Component::~Component(void) {
		p_Clear();
	}

	inline void Component::p_Clear(void) {
		p_gameObject = NULL;
	}

	inline void Component::p_Init(void) {

	}

	inline void Component::p_Start(void) {

	}

	inline void Component::p_Update(void) {

	}

	inline void Component::p_Sort(void) {
		p_order = 0.0f;
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