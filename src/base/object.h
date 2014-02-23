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

			inline explicit Object(void);
			inline Object(const Object& other);
			inline ~Object(void);

			inline virtual void Deconstructor(void);

			inline virtual Object* Clone(void);
			inline Object& Copy(const Object& other);

			inline unsigned int GetID(void);

			inline void SetName(std::string name);
			inline std::string ToString(void);
	};
}

#endif