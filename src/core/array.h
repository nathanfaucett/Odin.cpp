#ifndef ODIN_ARRAY_H
#define ODIN_ARRAY_H

namespace Odin {

	template <typename Type> class Array {

		private:
			Type* m_array;
			uint32 m_length;

			inline void m_QuickSort(std::function<float32(const Type& a, const Type& b)> sortFunction, int32 from, int32 to);
			inline int32 m_Partition(std::function<float32(const Type& a, const Type& b)> sortFunction, int32 i, int32 j);

		public:

			inline explicit Array(void);
			inline Array(const Array<Type>& other);
			inline Array(const Array<Type>&& other);
			inline ~Array(void);

			inline Type operator [] (int32 index) const;
			inline Type& operator [] (int32 index);

			inline void Splice(uint32 index, int32 count);
			inline void Splice(uint32 index, int32 count, const Type item);

			inline void Push(const Type item);
			inline void Unshift(const Type item);

			inline Type Pop(void);
			inline Type Shift(void);

			inline void Clear(void);

			inline int32 IndexOf(const Type& item);
			inline uint32 Length(void);
			inline Type& GetRawArray(void);

			inline void Sort(std::function<float32(const Type& a, const Type& b)> sortFunction);
			inline void ForEach(std::function<bool(const Type& item, int32 index)> sortFunction);

			inline Array<Type>& operator =(const Array<Type>& other);
			inline Array<Type>& operator =(const Array<Type> && other);
	};
}
#endif