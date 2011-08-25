
#ifndef SINGLETON_HPP
#define SINGLETON_HPP

#include <boost/function.hpp>

template < typename T >
class Singleton {
public:
	static T& getInstance() {
		static T instance;

		return instance;
	}
};

#endif /* SINGLETON_HPP */