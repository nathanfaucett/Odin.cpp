#ifndef ODIN_OBJECT_H
#define ODIN_OBJECT_H

namespace Odin {
	unsigned int ODIN_OBJECT_ID = 0;

	class Object {

		private:
			unsigned int m_id;
			std::string m_name;

		protected:


		public:

			Object();

			~Object();

			inline void virtual Deconstructor();

			inline unsigned int GetID();

			inline std::string ToString();
	};
}

#endif