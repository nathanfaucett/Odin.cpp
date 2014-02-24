#ifndef ODIN_ARRAY_H
#define ODIN_ARRAY_H

namespace Odin {

	template <class Type> class Array {

		private:
			Type* m_array;
			unsigned int m_length;

			inline void m_QuickSort(std::function<float(const Type a, const Type b)> sortFunction, const int from, const int to);
			inline int m_Partition(std::function<float(const Type a, const Type b)> sortFunction, int i, int j);

		protected:


		public:

			inline explicit Array(void);
			inline Array(const Array<Type>& other);
			inline Array(const Array<Type>&& other);
			inline ~Array(void);

			inline Type operator [] (unsigned int index) const;
			inline Type& operator [] (unsigned int index);

			inline Type Splice(const unsigned int index, const unsigned int count);
			inline Type Splice(const unsigned int index, const unsigned int count, const Type item);

			inline Type Push(const Type item);
			inline Type Unshift(const Type item);

			inline void Clear(void);

			inline int IndexOf(const Type& item);
			inline unsigned int Length(void);

			inline void Sort(std::function<int(const Type a, const Type b)> sortFunction);

			inline Array<Type>& operator =(const Array<Type>& other);
			inline Array<Type>& operator =(const Array<Type> && other);
	};
}
#endif