#ifndef ODIN_OBJECT_CPP
#define ODIN_OBJECT_CPP

namespace Odin {

	struct __OBJECT_UNIQUE_ID__ {

		private:
			uint32 m_instanceID;

		public:
			__OBJECT_UNIQUE_ID__(void) {
				m_instanceID = 0;
			}
			~__OBJECT_UNIQUE_ID__(void) {}

			inline uint32 next(void) {
				return m_instanceID++;
			}
	} __OBJECT_UNIQUE_ID__;


	inline Object::Object(void) {
		m_instanceID = __OBJECT_UNIQUE_ID__.next();
	}

	inline Object::~Object(void) {}

	inline uint32 Object::GetInstanceID(void) const {
		return m_instanceID;
	}
}

#endif