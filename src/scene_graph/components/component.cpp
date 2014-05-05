#ifndef ODIN_COMPONENT_CPP
#define ODIN_COMPONENT_CPP

namespace Odin {

	inline Component::Component(void) : Object() {}

	inline Component::Component(std::string name) : Object(name) {}

	inline Component::Component(const Component& other) : Object() {
		Copy(other);
	}

	inline Component::Component(const Component&& other) : Object() {
		Move(std::move(other));
	}

	inline Component::~Component(void) {
		p_Clear();
	}
	
	inline Component* Component::Clone(void) {
		return new Component(*this);
	}

	inline Component& Component::Copy(const Component& other) {
		Object::Copy(static_cast<Object>(other));
		
		p_updateOrder = other.p_updateOrder;
		p_order = other.p_order;
		
		return *this;
	}
	
	inline Component& Component::Move(const Component&& other) {
		Object::Move(std::move(static_cast<Object>(other)));
		
		p_updateOrder = std::move(other.p_updateOrder);
		p_order = std::move(other.p_order);
		
		return *this;
	}

	inline void Component::p_Init(void) {

	}

	inline void Component::p_Start(void) {

	}

	inline void Component::p_Clear(void) {
		p_gameObject = NULL;
	}

	inline void Component::p_Sort(void) {
		p_order = 0.0f;
	}

	inline void Component::Update(void) {

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
	
	inline Component& Component::operator =(const Component& other) {
		return Copy(other);
	}
	
	inline Component& Component::operator =(const Component&& other) {
		return Move(std::move(other));
	}
}

#endif