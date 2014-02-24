#ifndef ODIN_OBJECT_CPP
#define ODIN_OBJECT_CPP

namespace Odin {

	inline Object::Object(void) {
		m_id = ObjectID.GenerateID();
	}

	inline Object::Object(const Object& other) {
		m_id = ObjectID.GenerateID();
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

		name = other.name;

		return *this;
	}

	inline unsigned int Object::GetID(void) {

		return m_id;
	}

	inline std::string Object::ToString(void) {

		return name;
	}
}

#endif