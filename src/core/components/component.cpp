#ifndef ODIN_COMPONENT_CPP
#define ODIN_COMPONENT_CPP

namespace Odin {
	
	inline Component::Component(void) : Object() {
		GameObject gameObject;
	}

	inline Component::~Component(void) {
		Deconstructor();
	}

	inline void Component::Deconstructor(void) {
		
	}

	inline void Component::Update(void) {
		
	}

	inline void Component::Destroy(void) {
		
	}
}

#endif