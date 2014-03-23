#ifndef _ODIN_OBJECT_H_
#define _ODIN_OBJECT_H_

namespace Odin {

	class Object {

		private:
			int32 m_id;

		protected:

		public:
			std::string name;

			inline Object(void);
			inline Object(std::string Name);
			inline ~Object(void);

			inline int32 GetID(void);
	};
}

#endif