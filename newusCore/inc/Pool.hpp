
#ifndef POOL_HPP
#define POOL_HPP

#include <stack>
#include <vector>

#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

template <typename T>
class Pool {
public:
	Pool() 
		: index(0), container(), trash() {
		container.push(std::vector< T >());
		container.top().resize(8);
	}
	
	Pool(const Pool& orig)
		: index(orig.index), container(orig.container), trash(orig.trash)
	{}

	boost::shared_ptr< T > getObj() {
		boost::lock_guard<boost::mutex> guard(mut);
		boost::shared_ptr< T > ptr;
		if (trash.size()) {
			ptr = boost::shared_ptr<T>(trash.top(), boost::bind(&Pool::redeemObj, this, _1));
			trash.pop();
		} else {
			realloc();
			ptr = boost::shared_ptr<T>(&container.top()[index], boost::bind(&Pool::redeemObj, this, _1));
			index++;
		}
		return ptr;
	}

	void redeemObj(T* value) {
		boost::lock_guard<boost::mutex> guard(mut);
		trash.push(value);
	}

protected:
	void realloc() {
		if (index >= container.top().size()) {
			unsigned newSize = container.top().size() * 2;
			container.push(std::vector< T >());
			container.top().resize(newSize);
			index = 0;
		}
	}

private:
	unsigned int index;
	std::stack< std::vector< T > > container;
	std::stack< T* > trash;
	boost::mutex mut;
};


#endif /* POOL_HPP */