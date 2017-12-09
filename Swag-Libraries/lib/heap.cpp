#include <iostream>
#include <vector>
#include <cassert>

using namespace std;



template<typename T>
class PriorityQueue {
public:

    // construct and destruct
    PriorityQueue() : container_(21, 0) {
        size_ = 0;
        capacity_ = container_.size();
        container_.push_back(INT_MIN);
    }
    PriorityQueue(int size) : container_(size*2+1, 0) {
        size_ = 0;
        capacity_ = container_.size();
        container_.push_back(INT_MIN);
    }
    virtual ~PriorityQueue(){

    }

    // clear all the element but don't release meomory
    void clear() {
        container_.clear();
        size_ = 0;
    }

    // remove all elements and release memory , and the object can't use later
    void destroy() {
        container_.clear();
        size_ = 0;
        capacity_ = 0;
    }

    // O(logN)
    void push(const T &t){
        int i;
        // if is full , double size the capacity
        if(isFull())
            container_.resize( capacity_ = capacity_ * 2, 0);
        // percolate up
        for(i = ++size_; container_[i/2] > t; i/=2) {
            container_[i] = container_[i/2];
        }
        
        container_[i] = t;
    }

    // O(logN)
    void pop() {
        if(isEmpty()) 
            return ;
        
        T lastElement = container_[size_--];
        auto i = 1, child = 1;

        for( ; i * 2 <= size_; i = child) {
            // find smaller child. Because the heap based on complete binary tree, if the
            // node only has left child , the child must be the last element, so we can 
            // simplify the code like this, i think it is clever
            child  = 2 * i;
            if( child != size_ && container_[child] > container_[child+1] )
                child++;
            
            // percolate down one level
            if( lastElement > container_[child] )
                container_[i] = container_[child];
            else {
                break;
            }
        }
        
        container_[i] = lastElement;
    }

    const T& getTop() const{
        if(size_ == 0) 
            throw std::underflow_error("heap is empty"); 
        return container_[1];
    }

    bool isEmpty() const{
        return size_ == 0;
    }

    bool isFull() const{
        return size_ >= capacity_-1;
    }

    const int& getSize() const {
        return size_;
    } 

    const int& getCapacity() const {
        return capacity_;
    }

private:
    vector<T> container_;
    int capacity_;
    int size_;
};


template<typename T>
vector<T> print_queue(PriorityQueue<T> &q){
    vector<T> ret;
    while(!q.isEmpty()) {
        ret.push_back(q.getTop());
        q.pop();
    }
    return ret;
}

template<typename T>
void heap_sort(T &begin, T &end) {
    PriorityQueue<int> p;
    T it = begin;
    while(it!=end) {
        p.push(*it);
        it++;
    }
    it = begin;
    while(it!=end) {
        *it = p.getTop();
        p.pop();
        it++;
    }
}

int main()
{
    // push , pop , top test
    {
        PriorityQueue<int> p;
        assert(p.getSize() == 0);
        assert(p.getCapacity() == 21);

        p.push(3);p.push(2);p.push(7);p.push(11);p.push(23);
        p.pop();p.pop();
        p.push(3);p.push(2);p.push(43);p.push(21);p.push(25);
        p.pop();p.pop();
        vector<int> vcmp = {7, 11, 21, 23, 25, 43};

        assert(p.getSize() == 6);
        assert( vcmp == print_queue<int>(p));
        assert(p.getCapacity() == 21);

    }

    // size , capacity , clear , destroy test
    {
        PriorityQueue<int> p;
        assert(p.getSize() == 0);
        assert(p.getCapacity() == 21);

        for(auto i = 0; i<21; i++){
            p.push(i);
        }
        assert(p.getSize() == 21);
        assert(p.getCapacity() == 42);

        p.clear();
        assert(p.getSize() == 0);
        assert(p.getCapacity() == 42);

        p.destroy();
        assert(p.getSize() == 0);
        assert(p.getCapacity() == 0);
    }

    // heapsort test
    {
        vector<int> v = {1, 16, 12, 2, 25, 5, 6};
        vector<int> cmpv = {1, 2, 5, 6, 12, 16, 25};
        heap_sort(v.begin(), v.end());
        assert(v == cmpv);
        
    }


    cout<< "All TestCases Pass."<<endl;
    return 0;
}