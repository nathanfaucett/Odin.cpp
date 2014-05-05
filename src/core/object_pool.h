#ifndef ODIN_OBJECT_POOL_H
#define ODIN_OBJECT_POOL_H

namespace Odin {

	template <typename Type> class ObjectPool {

		private:
			Array<Type*> m_inactive;
			Array<Type*> m_active;

		public:

			inline explicit ObjectPool(void);
			inline ~ObjectPool(void);
			
			inline Type* Create(void);
			inline void Pool(Type* obj);
			inline void PoolAll(void);
			inline void Clear(void);
	};
}
#endif