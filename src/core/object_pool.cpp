#ifndef ODIN_OBJECT_POOL_CPP
#define ODIN_OBJECT_POOL_CPP

namespace Odin {

	template <typename Type> inline ObjectPool<Type>::ObjectPool(void) {
		
	}
	template <typename Type> inline ObjectPool<Type>::~ObjectPool(void) {
		Clear();
	}
	
	template <typename Type> inline Type* ObjectPool<Type>::Create(void) {
		return m_inactive.Length() > 0 ? m_inactive.Pop() : new Type();
	}
	
	template <typename Type> inline void ObjectPool<Type>::Pool(Type* obj) {
		int32 index = m_active.IndexOf(obj);
		
		if (index != -1) {
			m_inactive.Push(obj);
			m_active.Splice(index, 1);
		}
	}
	
	template <typename Type> inline void ObjectPool<Type>::PoolAll(void) {
		uint32 i = m_active.Length();
		
		while(i--) m_inactive.Push(m_active[i]);
		m_active.Clear();
	}
	
	template <typename Type> inline void ObjectPool<Type>::Clear(void) {
		m_active.Clear();
		m_inactive.Clear();
	}
}
#endif