#ifndef ODIN_OBJECT_CPP
#define ODIN_OBJECT_CPP

namespace Odin {

	struct __OBJECT_UNIQUE_ID__ {

		private:
			int32 m_instanceID;

		public:
			__OBJECT_UNIQUE_ID__(void) {
				m_instanceID = 0;
			}
			~__OBJECT_UNIQUE_ID__(void) {}

			inline int32 next(void) {
				return m_instanceID++;
			}
	} __OBJECT_UNIQUE_ID__;


	inline Object::Object(void) {
		m_instanceID = __OBJECT_UNIQUE_ID__.next();
		p_name = "Object_"+ ToString(m_instanceID);
	}
	
	inline Object::Object(std::string name) {
		m_instanceID = __OBJECT_UNIQUE_ID__.next();
		p_name = name;
	}

	inline Object::Object(const Object& other) {
		m_instanceID = __OBJECT_UNIQUE_ID__.next();
		Copy(other);
	}
	
	inline Object::Object(const Object&& other) {
		m_instanceID = __OBJECT_UNIQUE_ID__.next();
		Move(std::move(other));
	}

	inline Object::~Object(void) {}

	inline int32 Object::GetInstanceID(void) {
		return m_instanceID;
	}

	inline std::string Object::GetName(void) {
		return p_name;
	}
	inline Object& Object::SetName(std::string name) {
		p_name = name;
		return *this;
	}

	inline Object& Object::Copy(const Object& other) {
		p_name = other.p_name;
		return *this;
	}

	inline Object& Object::Move(const Object&& other) {
		p_name = std::move(other.p_name);
		return *this;
	}

	inline Object& Object::operator =(const Object& other) {
		return Copy(other);
	}
	
	inline Object& Object::operator =(const Object&& other) {
		return Move(std::move(other));
	}
}

#endif