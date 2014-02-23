#ifndef ODIN_OBJECT_CPP
#define ODIN_OBJECT_CPP

namespace Odin {

	inline Object::Object(void) {
		m_id = ++ODIN_OBJECT_ID;
	}

	inline Object::Object(const Object& other) {
		m_id = ++ODIN_OBJECT_ID;
		Copy(other);
	}

	inline Object::~Object(void) {
		Deconstructor();
	}

	inline void Object::Deconstructor(void) {

	}

	inline Object* Object::Clone(void) {

		return new Object(*this);
	}

	inline Object& Object::Copy(const Object& other) {

		m_name = other.m_name;

		return *this;
	}

	inline unsigned int Object::GetID(void) {

		return m_id;
	}

	inline void Object::SetName(std::string name) {

		m_name = name;
	}

	inline std::string Object::ToString(void) {

		return m_name;
	}
}

#endif