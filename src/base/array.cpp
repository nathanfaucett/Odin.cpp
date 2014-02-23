#ifndef ODIN_ARRAY_CPP
#define ODIN_ARRAY_CPP

namespace Odin {

	template <class Type> inline Array<Type>::Array(void) {
		m_length = 0;
		m_array = new Type[m_length];
	}

	template <class Type> inline Array<Type>::Array(const unsigned int length) {
		m_length = length;
		m_array = new Type[m_length];
	}

	template <class Type> inline Array<Type>::~Array(void) {
		delete []m_array;
	}

	template <class Type> inline Type Array<Type>::operator [] (const unsigned int i) {

		return m_array[(i >= m_length ? (m_length - 1) : i)];
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

	template <class Type> inline unsigned int Array<Type>::Length(void) {

		return m_length;
	}

	template <class Type> inline void Array<Type>::Sort(std::function<int(const Type a, const Type b)> sortFunction) {

		m_QuickSort(sortFunction, 0, m_length - 1);
	}

	template <class Type> inline void Array<Type>::m_QuickSort(std::function<int(const Type a, const Type b)> sortFunction, const int from, const int to) {

		if (from < to) {
			int j = m_Partition(sortFunction, from, to);
			m_QuickSort(sortFunction, from, j - 1);
			m_QuickSort(sortFunction, j + 1, to);
		}
	}

	template <class Type> inline int Array<Type>::m_Partition(std::function<int(const Type a, const Type b)> sortFunction, int i, int j) {
		Type pivot = m_array[(i + j) >> 1];
		Type tmp;

		while (i < j) {
			while (sortFunction(m_array[i], pivot) < 0) {
				i++;
			}
			while (sortFunction(m_array[j], pivot) > 0) {
				j--;
			}

			if (sortFunction(m_array[i], m_array[j]) == 0) {
				i++;
			} else if (i < j) {
				tmp = m_array[i];
				m_array[i] = m_array[j];
				m_array[j] = tmp;
			}
		}

		return j;
	}
}
#endif