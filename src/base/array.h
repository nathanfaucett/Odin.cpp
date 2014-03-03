#ifndef _ODIN_ARRAY_H
#define _ODIN_ARRAY_H

namespace Odin {

	template <typename Type> class Array {

		private:
			Type* m_array;
			uint32 m_length;

			inline void m_QuickSort(std::function<float32(const Type a, const Type b)> sortFunction, int32 from, int32 to);
			inline int32 m_Partition(std::function<float32(const Type a, const Type b)> sortFunction, int32 i, int32 j);

		public:

			inline explicit Array(void);
			inline Array(const Array<Type>& other);
			inline Array(const Array<Type>&& other);
			inline ~Array(void);

			inline Type operator [] (uint32 index) const;
			inline Type& operator [] (uint32 index);

			inline Type Splice(uint32 index, int32 count);
			inline Type Splice(uint32 index, int32 count, const Type item);

			inline Type Push(const Type item);
			inline Type Unshift(const Type item);

			inline void Clear(void);

			inline int32 IndexOf(const Type& item);
			inline uint32 Length(void);

			inline void Sort(std::function<int32(const Type a, const Type b)> sortFunction);

			inline Array<Type>& operator =(const Array<Type>& other);
			inline Array<Type>& operator =(const Array<Type> && other);
	};
}
#endif