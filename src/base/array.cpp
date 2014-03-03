#ifndef _ODIN_ARRAY_CPP
#define _ODIN_ARRAY_CPP

namespace Odin {

	template <typename Type> inline void Array<Type>::m_QuickSort(std::function<float32(const Type a, const Type b)> sortFunction, int32 from, int32 to) {

		if (from < to) {
			int32 j = m_Partition(sortFunction, from, to);
			m_QuickSort(sortFunction, from, j - 1);
			m_QuickSort(sortFunction, j + 1, to);
		}
	}

	template <typename Type> inline int32 Array<Type>::m_Partition(std::function<float32(const Type a, const Type b)> sortFunction, int32 i, int32 j) {
		Type pivot = m_array[j];
		Type tmp;

		while (i < j) {
			while (sortFunction(m_array[i], pivot) < 0.0f) {
				i++;
			}

			while (sortFunction(m_array[j], pivot) > 0.0f) {
				j--;
			}

			if (sortFunction(m_array[i], m_array[j]) == 0.0f) {
				i++;

			} else if (i < j) {
				tmp = m_array[i];
				m_array[i] = m_array[j];
				m_array[j] = tmp;
			}
		}

		return j;
	}

	template <typename Type> inline Array<Type>::Array(void) {
		m_length = 0;
		m_array = new Type[m_length];
	}

	template <typename Type> inline Array<Type>::Array(const Array<Type>& other) {
		uint32 length = other.m_length,
		       i = 0;

		Type* array = new Type[length];

		for (; i < length; i++) {
			array[i] = other.m_array[i];
		}

		m_array = array;
		m_length = length;
	}

	template <typename Type> inline Array<Type>::Array(const Array<Type>&& other) {
		uint32 length = other.m_length,
		       i = 0;

		Type* array = new Type[length];

		for (; i < length; i++) {
			array[i] = std::move(other.m_array[i]);
		}

		m_array = array;
		m_length = length;
	}

	template <typename Type> inline Array<Type>::~Array(void) {
		delete []m_array;
	}

	template <typename Type> inline Type Array<Type>::operator [] (uint32 index) const {

		return m_array[(index >= m_length ? (m_length - 1) : index < 0 ? 0 : index)];
	}

	template <typename Type> inline Type& Array<Type>::operator [] (uint32 index) {

		return m_array[(index >= m_length ? (m_length - 1) : index < 0 ? 0 : index)];
	}

	template <typename Type> inline Type Array<Type>::Splice(uint32 index, int32 count) {
		uint32 length = m_length,
		       i = 0, j = 0;

		m_length = length - count;
		Type* array = new Type[m_length];

		for (; i < length; i++) {
			if (i >= index && i < (index + count)) {
				continue;
			}

			array[j++] = m_array[i];
		}

		delete []m_array;
		m_array = array;
	}

	template <typename Type> inline Type Array<Type>::Splice(uint32 index, int32 count, const Type item) {
		count -= 1;
		uint32 length = m_length,
		       i = 0, j = 0;

		m_length = length - count;
		Type* array = new Type[m_length];

		for (; i < length; i++) {
			if (i >= index && i < (index + count)) {
				continue;
			}

			array[j++] = m_array[i];
		}

		array[index] = item;
		delete []m_array;
		m_array = array;
	}

	template <typename Type> inline Type Array<Type>::Push(const Type item) {
		uint32 length = m_length,
		       i = 0;

		m_length++;
		Type* array = new Type[m_length];

		for (; i < length; i++) {
			array[i] = m_array[i];
		}

		delete []m_array;
		array[m_length - 1] = item;
		m_array = array;

		return item;
	}

	template <typename Type> inline Type Array<Type>::Unshift(const Type item) {
		uint32 i = 1, j = 0;

		m_length++;
		Type* array = new Type[m_length];

		for (; i < m_length; i++) {
			array[i] = m_array[j++];
		}

		delete []m_array;
		array[0] = item;
		m_array = array;

		return item;
	}

	template <typename Type> inline void Array<Type>::Clear(void) {
		delete []m_array;
		m_length = 0;
		m_array = new Type[m_length];
	}

	template <typename Type> inline int32 Array<Type>::IndexOf(const Type& item) {

		for (uint32 i = m_length; i-- > 0;) {
			if (m_array[i] == item) {
				return i;
			}
		}

		return -1;
	}

	template <typename Type> inline uint32 Array<Type>::Length(void) {

		return m_length;
	}

	template <typename Type> inline void Array<Type>::Sort(std::function<int32(const Type a, const Type b)> sortFunction) {

		m_QuickSort(sortFunction, 0, m_length - 1);
	}

	template <typename Type> inline Array<Type>& Array<Type>::operator =(const Array<Type>& other) {
		uint32 length = other.m_length,
		       i = 0;

		Type* array = new Type[length];

		for (; i < length; i++) {
			array[i] = other.m_array[i];
		}

		delete []m_array;
		m_array = array;
		m_length = length;

		return *this;
	}

	template <typename Type> inline Array<Type>& Array<Type>::operator =(const Array<Type> && other) {
		uint32 length = other.m_length,
		       i = 0;

		Type* array = new Type[length];

		for (; i < length; i++) {
			array[i] = std::move(other.m_array[i]);
		}

		delete []m_array;
		m_array = array;
		m_length = length;

		return *this;
	}
}
#endif