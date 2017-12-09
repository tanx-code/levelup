#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cassert>




template<typename T>
class set {

public:
    set(){}
    virtual ~set(){}

public:
    // public interface

    void insert( const T& data ) {
        auto it = std::find( container_.begin(), container_.end(), data );
        if( it == container_.end() )
            container_.push_back(data);
    }

    void remove( const T& data ) {
        auto it = std::find( container_.begin(), container_.end(), data );
        if( it != container_.end() )
            container_.erase(it);
    }
    
    bool find( const T& data ) const {
        auto it = std::find( container_.begin(), container_.end(), data );
        return it != container_.end();
    }

    bool isSubset( const set<T> &a ) {
        for(auto i : a.container_) {
            if( std::find(container_.begin(), container_.end(), i) == container_.end())
                return false;
        }
        return true;
    }

    // maybe O(n2)
    bool isEqual( const set<T> &a ) const {
        if( a.container_.size() != container_.size() )
            return false;
        for(auto i : a.container_) {
            if( std::find(container_.begin(), container_.end(), i) == container_.end())
                return false;
        }
        return true;
    }

    bool isEmpty() const {
        return container_.empty();
    }

    // this function only can assume popping a random element in set
    const T getElement(int i) const {
        if(i < container_.size()) {
            auto it = container_.begin();
            while( i-- > 0) {
                it ++;
            }
            return *it;
        }
        return T();
    }

    int getSize() const {
        return container_.size();
    }


public:
    std::list<T> container_;

};

template<typename T>
const set<T> set_union( set<T> &a, set<T> &b ) {
    set<T> result;
    result = a;
    for(auto i : b.container_) {
        result.insert(i);
    }

    return result;
}

// setA - setB
template<typename T>
const set<T> set_difference( set<T> &a, set<T> &b ) {
    set<T> result;
    result = a;
    set<T> interser = set_intersection( a, b );
    for( auto i : interser.container_) {
        auto it = std::find( result.container_.begin(), result.container_.end(), i );
        if( it != result.container_.end())
            result.container_.erase(it);
    }
    return result;
}

template<typename T>
const set<T> set_intersection( set<T> &a, set<T> &b ) {
    set<T> result;
    for( auto i : b.container_) {
        auto it = std::find( a.container_.begin(), a.container_.end(), i );
        if( it != a.container_.end() )
            result.container_.push_back( i );
    }
    return result;
}





bool mycmp(set<int> s, std::vector<int> v) {
    if( s.getSize() != v.size() )
        return false;
    int i = 0;
    while( i != s.getSize() ) {
        auto it = std::find(v.begin(), v.end(), s.getElement(i++));
        if(it == v.end())
            return false;
    }
    return true;
}

int main()
{
    {
        set<int> a;
        for(auto i = 0; i<5; i++)
            a.insert(i);
        set<int> b;
        for(auto i = 0; i<5; i++)
            b.insert(2*i);

        assert(true == a.isEqual(a));
        assert(5 == a.getSize());
        assert(true == a.find(2));
        assert(true == !a.isSubset(b));
        assert(true == mycmp(set_union(a, b), std::vector<int> {0,1,2,3,4,6,8}) );
        assert(true == mycmp(set_difference(a, b), std::vector<int> {1,3}) );
        assert(true == mycmp(set_intersection(a, b), std::vector<int> {0,2,4}) );
    }

    std::cout<< "All testcases pass.";
    return 0;
}