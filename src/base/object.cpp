#ifndef _ODIN_OBJECT_CPP_
#define _ODIN_OBJECT_CPP_

namespace Odin {

	struct __OBJECT_UNIQUE_ID__ {

		private:
			int32 m_id;

		public:
			__OBJECT_UNIQUE_ID__(void) {
				m_id = 0;
			}
			~__OBJECT_UNIQUE_ID__(void) {}

			inline int32 next(void) {
				return m_id++;
			}
	};
	__OBJECT_UNIQUE_ID__ __OBJECT_UNIQUE_ID__;


	inline Object::Object(void) {
		m_id = __OBJECT_UNIQUE_ID__.next();
		name = "Object_" + util.ToString(m_id);
	}

	inline Object::Object(std::string Name) {
		m_id = __OBJECT_UNIQUE_ID__.next();
		name = Name;
	}

	inline Object::~Object(void) {

	}

	inline int32 Object::GetID(void) {
		return m_id;
	}
}

#endif