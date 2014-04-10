#ifndef ODIN_OBJECT_H
#define ODIN_OBJECT_H

namespace Odin {
	
	class Object {

		private:
			int32 m_instanceID;

		protected:
			
		public:
			std::string name;
			
			inline Object(void);
			inline Object(std::string Name);
			inline Object(const Object& other);
			inline Object(const Object&& other);
			inline ~Object(void);

			inline virtual Object& Copy(const Object& other);
			inline virtual Object& Move(const Object&& other);
			
			inline int32 GetInstanceID(void);
			
			inline Object& operator =(const Object& other);
			inline Object& operator =(const Object&& other);
	};
}

#endif