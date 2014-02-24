#ifndef ODIN_ARRAY_CPP
#define ODIN_ARRAY_CPP

namespace Odin {

	template <class Type> inline void Array<Type>::m_QuickSort(std::function<float(const Type a, const Type b)> sortFunction, const int from, const int to) {

		if (from < to) {
			int j = m_Partition(sortFunction, from, to);
			m_QuickSort(sortFunction, from, j - 1);
			m_QuickSort(sortFunction, j + 1, to);
		}
	}

	template <class Type> inline int Array<Type>::m_Partition(std::function<float(const Type a, const Type b)> sortFunction, int i, int j) {
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

	template <class Type> inline Array<Type>::Array(void) {
		m_length = 0;
		m_array = new Type[m_length];
	}

	template <class Type> inline Array<Type>::Array(const Array<Type>& other) {
		unsigned int length = other.m_length,
		             i = 0;

		Type* array = new Type[length];

		for (; i < length; i++) {
			array[i] = other.m_array[i];
		}

		m_array = array;
		m_length = length;
	}

	template <class Type> inline Array<Type>::Array(const Array<Type>&& other) {
		unsigned int length = other.m_length,
		             i = 0;

		Type* array = new Type[length];

		for (; i < length; i++) {
			array[i] = std::move(other.m_array[i]);
		}

		m_array = array;
		m_length = length;
	}

	template <class Type> inline Array<Type>::~Array(void) {
		delete []m_array;
	}

	template <class Type> inline Type Array<Type>::operator [] (unsigned int index) const {

		return m_array[(index >= m_length ? (m_length - 1) : index)];
	}

	template <class Type> inline Type& Array<Type>::operator [] (unsigned int index) {

		if (index >= m_length) {
			Type* array = new Type[index];

			for (unsigned int i = 0; i < m_length; i++) {
				array[i] = m_array[i];
			}

			delete []m_array;
			m_array = array;
			m_length = index;
			index -= 1;
		}

		return m_array[index];
	}

	template <class Type> inline Type Array<Type>::Splice(const unsigned int index, const unsigned int count) {
		unsigned int length = m_length,
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

	template <class Type> inline Type Array<Type>::Splice(const unsigned int index, const unsigned int count, const Type item) {
		unsigned int length = m_length,
		             ncount = count - 1,
		             i = 0, j = 0;

		m_length = length - ncount;
		Type* array = new Type[m_length];

		for (; i < length; i++) {
			if (i >= index && i < (index + ncount)) {
				continue;
			}

			array[j++] = m_array[i];
		}

		m_array[index] = item;
		delete []m_array;
		m_array = array;
	}

	template <class Type> inline Type Array<Type>::Push(const Type item) {
		unsigned int length = m_length,
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

	template <class Type> inline Type Array<Type>::Unshift(const Type item) {
		unsigned int i = 1, j = 0;

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

	template <class Type> inline void Array<Type>::Clear(void) {
		delete []m_array;
		m_length = 0;
		m_array = new Type[m_length];
	}

	template <class Type> inline int Array<Type>::IndexOf(const Type& item) {

		for (unsigned int i = m_length; i-- > 0;) {
			if (m_array[i] == item) {
				return i;
			}
		}

		return -1;
	}

	template <class Type> inline unsigned int Array<Type>::Length(void) {

		return m_length;
	}

	template <class Type> inline void Array<Type>::Sort(std::function<int(const Type a, const Type b)> sortFunction) {

		m_QuickSort(sortFunction, 0, m_length - 1);
	}

	template <class Type> inline Array<Type>& Array<Type>::operator =(const Array<Type>& other) {
		unsigned int length = other.m_length,
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

	template <class Type> inline Array<Type>& Array<Type>::operator =(const Array<Type> && other) {
		unsigned int length = other.m_length,
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