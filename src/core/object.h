#ifndef ODIN_OBJECT_H
#define ODIN_OBJECT_H

namespace Odin {
	
	class Object {

		private:
			int32 m_instanceID;

		protected:

		public:
			inline explicit Object(void);
			inline ~Object(void);

			inline int32 GetInstanceID(void);
	};
}

#endif