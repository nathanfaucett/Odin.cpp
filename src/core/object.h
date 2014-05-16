#ifndef ODIN_OBJECT_H
#define ODIN_OBJECT_H

namespace Odin {
	
	class Object {

		private:
			uint32 m_instanceID;

		protected:

		public:
			inline explicit Object(void);
			inline ~Object(void);

			inline uint32 GetInstanceID(void) const;
	};
}

#endif