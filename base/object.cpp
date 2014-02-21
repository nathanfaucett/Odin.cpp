#ifndef ODIN_OBJECT_CPP
#define ODIN_OBJECT_CPP

namespace Odin {

	Object::Object() {
		m_id = ++ODIN_OBJECT_ID;
	}

	Object::~Object() {
		Deconstructor();
	}

	inline void Object::Deconstructor() {

	}

	inline unsigned int Object::GetID() {

		return m_id;
	}

	inline std::string Object::ToString() {

		return m_name;
	}
}

#endif