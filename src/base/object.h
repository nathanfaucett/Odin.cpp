#ifndef ODIN_OBJECT_H
#define ODIN_OBJECT_H

namespace Odin {

	struct ObjectID {
		private:
			unsigned int m_id;

		public:
			inline explicit ObjectID(void) {
				m_id = 0;
			}
			inline ~ObjectID(void) {}

			inline unsigned int GenerateID(void) {

				return ++m_id;
			}
	};
	ObjectID ObjectID;


	class Object {

		private:
			unsigned int m_id;

		protected:


		public:
			std::string name;

			inline explicit Object(void);
			inline Object(const Object& other);
			inline ~Object(void);

			inline virtual void Deconstructor(void);

			inline virtual Object* Clone(void);
			inline virtual Object& Copy(const Object& other);

			inline unsigned int GetID(void);

			inline std::string ToString(void);
	};
}

#endif