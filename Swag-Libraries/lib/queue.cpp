#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <memory>

template<typename T>
class Queue_array {
public:
    Queue_array(int maxsize = 10) : maxsize_(maxsize),
                                    size_(0), front_(0), rear_(0)
    {
        pa_ = new T[maxsize_];
    }
    virtual ~Queue_array() {
        delete[] pa_;
    }

public:
    void push( const T& x) {
        if(isFull())
            return ;

        size_++;
        rear_ %= maxsize_;
        pa_[rear_] = x;

        rear_++;
    }
    void pop() {
        size_ --;
        front_ ++;
        front_ %= 10;
    }
    const T getFront() {
        return pa_[front_];
    }
    const int getSize() const {
        return size_;
    }
    bool isEmpty() const {
        return size_ == 0;
    }
    bool isFull() const {
        return size_ == maxsize_;
    }

private:
    int front_, rear_;
    T* pa_;
    int size_;
    int maxsize_;
};


template<typename T>
class Queue_list {
public:
    typedef struct list {
        T data;
        list *next;
        list(T x) : data(x), next(nullptr) {}
    } ListNode;

    Queue_list(int maxsize = 10) : size_(0), maxsize_(maxsize) {
        front_ = rear_ = new ListNode(0);
    }

    virtual ~Queue_list() {
        while( front_ != rear_) {
            ListNode* t = front_->next;
            delete front_;
            front_ = t;
        }
        delete rear_;
    };
public:
    void push( const T& x) {
        size_++;
        rear_->data = x;
        rear_->next = new ListNode(0);
        rear_ = rear_->next;
    }

    void pop() {
        size_--;
        ListNode *t = front_;
        front_ = front_->next;
        delete t;
    }

    const T getFront() {
        return front_->data;
    }

    const int getSize() const {
        return size_;
    }

    bool isEmpty() const {
        return front == rear;
    }

private:
    ListNode *front_, *rear_;
    int size_;
    int maxsize_;
};


int main() {
    {
        Queue_list<int> q;
        for(auto i = 0; i<10; i++)
            q.push(i);
        q.pop();
        assert(9 == q.getSize());
        assert(1 == q.getFront());
        q.push(10);
        q.pop();
        assert(2 == q.getFront());
    }

    {
        Queue_array<int> q;
        for(auto i = 0; i<10; i++)
            q.push(i);
        q.pop();
        assert(9 == q.getSize());
        assert(1 == q.getFront());
        q.push(10);
        q.pop();
        assert(2 == q.getFront());
    }


    std::cout << "All test cases pass";
    return 0;
}