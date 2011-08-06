

#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>
#include <exception>

template < typename T, std::size_t SIZE >
Array {
public:
	typedef T ArrayType;

	class ArrayException : public std::exception {
		const char* what() const throw() {
			return "Index out of bound";
		}
	};

	Array()
	{}

	Array(const T& value)
	{
		for (unsigned int i = 0; i < SIZE; ++i)
			_data[i] = value;
	}

	~Array() {}

	Array& operator=(const Array& orig) {
		if (this != &orig) {
			for (unsigned int i = 0; i < SIZE; ++i) {
				_data[i] = orig[i];
			}
		}
		return *this;
	}

	T& at(unsigned int index) {
		if (index >= SIZE)
			throw ArrayException();
		return _data[index];
	}

	const T& at(unsigned int index) const {
		if (index >= SIZE)
			throw ArrayException();
		return _data[index];
	}

	T& operator[](unsigned int index) {
		return at(index);
	}

	const T& operator[](unsigned int index) const {
		return at(index);
	}

	std::size_t size() const {
		return SIZE;
	}

private:
	T _data[SIZE];
};

#endif /* ARRAY_H */