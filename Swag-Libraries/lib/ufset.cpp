#include <iostream>
#include <vector>
#include <cassert>
#define MAXSIZE 10

template<typename T>
class DisjointSet {
public:
    DisjointSet(int maxsize) : container_(maxsize, SetType()) , size_(0) {

    }
    virtual ~DisjointSet() {

    }

public:
    typedef struct st {
        st() : data_(T()), parent_(-1) {
        }
        T data_;
        int parent_;
    } SetType;

    // insert a element as a unique set.
    void insert( const T& data) {
        if(size_ != container_.size()) {
            container_[size_++].data_ = data;
        }
    }
    int find(const T& x) {
        auto i = 0;
        // traversal the container to get the index of x
        for( ; i< container_.size() && container_[i].data_ != x ; i++)  ;

        // if didn't find return -1
        if( i == container_.size()) return -1;

        // get x 's root
        auto ti = i; // for path compression
        while( container_[i].parent_ > 0) {
            i = container_[i].parent_;
        }

        // path compression
        while( container_[ti].parent_ > 0) {
            int before = ti;
            ti = container_[ti].parent_;
            container_[before].parent_ = i;
        }

        // find it, return index of root
        return i;
    }
    int setUnion( const T& a, const T& b) {
        auto root1 = find(a);
        auto root2 = find(b);

        int ht1 = container_[root1].parent_, ht2 = container_[root2].parent_;
        int newHight = ht1 + ht2;

        if(ht1 > ht2) {
            container_[root2].parent_ = root1;
            return root1;
        }
        else {
            container_[root1].parent_ = root2;
            return root2;
        }

        return -1;
    }

private:
    std::vector<SetType> container_;
    int size_;

};


int main() {
    {
        DisjointSet<int> s(100);
        for(auto i=0; i<11; i++)
            s.insert(i);
        assert( s.find(0) != s.find(1));

        s.setUnion(1, 2);
        s.setUnion(2, 4);
        s.setUnion(3, 5);
        s.setUnion(4, 7);
        s.setUnion(5, 8);
        s.setUnion(6, 9);
        s.setUnion(6, 10);

        //the correct result should be {1,2,4,7} {5,3,8} {9,6,10}
        assert( s.find(2) == s.find(7));
        assert( s.find(5) == s.find(8));
        assert( s.find(6) == s.find(9));
        
        std::cout<< "All test pass" <<std::endl;
    }
    return 0;
}
