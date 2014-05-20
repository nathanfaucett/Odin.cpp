#ifndef ODIN_COMPONENT_CPP
#define ODIN_COMPONENT_CPP

namespace Odin {
	
	inline Component::Component(void) : Object() {
		p_gameObject = NULL;
	}
	
	inline Component::~Component(void) {
		
	}

	inline Component* Component::Clone(void) {
		return &((new Component())->Copy(*this));
	}
	
	inline Component& Component::Copy(const Component& other) {
		return *this;
	}

	inline void Component::p_Init(void) {
		
	}

	inline void Component::p_Start(void) {
		
	}
	
	inline void Component::p_Sort(void) {
		
	}

	inline void Component::Update(void) {

	}

	inline void Component::Clear(void) {
		if (p_gameObject != NULL) {
			p_gameObject->RemoveComponent(this);
		}
	}
	
	inline float32 Component::Sort(Component* a, Component* b) {
		return static_cast<float32>(a->GetInstanceID()) - static_cast<float32>(b->GetInstanceID());
	}

	
	inline GameObject* Component::GetGameObject(void) {
		return p_gameObject;
	}
	inline Scene* Component::GetScene(void) {
		if (p_gameObject != NULL) {
			return p_gameObject->m_scene;
		}
		
		return NULL;
	}
	template <typename Type>inline Type* Component::GetComponent(void) {
		const std::type_info* type = &typeid(Type);
		
		if (p_gameObject->m_components.count(type) != 0) {
			return static_cast<Type*>(p_gameObject->m_components[type]);
		}

		return NULL;
	}
}

#endif