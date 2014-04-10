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
		name = "Object_"+ Util.ToString(m_instanceID);
	}
	
	inline Object::Object(std::string Name) {
		m_instanceID = __OBJECT_UNIQUE_ID__.next();
		name = Name;
	}

	inline Object::Object(const Object& other) {
		m_instanceID = __OBJECT_UNIQUE_ID__.next();
		Copy(other);
	}
	
	inline Object::Object(const Object&& other) {
		m_instanceID = __OBJECT_UNIQUE_ID__.next();
		Move(std::move(other));
	}

	inline Object::~Object(void) {
		
	}

	inline int32 Object::GetInstanceID(void) {
		return m_instanceID;
	}

	inline Object& Object::Copy(const Object& other) {
		name = other.name;
		return *this;
	}

	inline Object& Object::Move(const Object&& other) {
		name = std::move(other.name);
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