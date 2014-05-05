#ifndef ODIN_OBJECT_H
#define ODIN_OBJECT_H

namespace Odin {
	
	class Object {

		private:
			int32 m_instanceID;

		protected:
			std::string p_name;

		public:
			inline explicit Object(void);
			inline Object(std::string name);
			inline Object(const Object& other);
			inline Object(const Object&& other);
			inline ~Object(void);

			inline Object& Copy(const Object& other);
			inline Object& Move(const Object&& other);

			inline int32 GetInstanceID(void);
			
			inline std::string GetName(void);
			inline Object& SetName(std::string name);

			inline Object& operator =(const Object& other);
			inline Object& operator =(const Object&& other);
	};
}

#endif