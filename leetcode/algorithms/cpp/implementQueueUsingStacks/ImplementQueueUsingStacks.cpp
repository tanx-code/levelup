// 跟chenhao的比起来，我这写的真是太丑了
// 有问题的代码：
// 1，每个操作都new了一个stack，可以将缓存stack也设置成员变量的
// 2，每次stack之间数据交换可以写成一个内部函数
// 出问题的根本原因：
// 没有思考出来究竟要怎么实现这个问题，就马上动手写了
// 这个问题的本质就是把一个stack倒在另一个stack里面，然后执行完相应的操作再倒回来，这样就能支持pop和peek功能了。
class Queue {
public:
    stack<int> *s;
    Queue(){
        s = new stack<int>;
    }
    // Push element x to the back of queue.
    void push(int x) {
        s->push(x);
    }

    // Removes the element from in front of queue.
    void pop(void) {
        stack<int> *s_tmp = new stack<int>;
        while(!s->empty())
        {
            s_tmp->push(s->top());
            s->pop();
        }
        s_tmp->pop();
        while(!s_tmp->empty())
        {
            s->push(s_tmp->top());
            s_tmp->pop();
        }
    }

    // Get the front element.
    int peek(void) {
        stack<int> *s_tmp = new stack<int>;
        while(!s->empty())
        {
            s_tmp->push(s->top());
            s->pop();
        }
        int result = s_tmp->top();
        while(!s_tmp->empty())
        {
            s->push(s_tmp->top());
            s_tmp->pop();
        }
        return result;
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return s->empty();
    }
};

// Source : https://leetcode.com/problems/implement-queue-using-stacks/
// Author : Hao Chen
// Date   : 2015-07-16

/********************************************************************************** 
 * 
 * Implement the following operations of a queue using stacks.
 * 
 * push(x) -- Push element x to the back of queue.
 * 
 * pop() -- Removes the element from in front of queue.
 * 
 * peek() -- Get the front element.
 * 
 * empty() -- Return whether the queue is empty.
 * 
 * Notes:
 * 
 * You must use only standard operations of a stack -- which means only push to top, 
 * peek/pop from top, size, and is empty operations are valid.

 * Depending on your language, stack may not be supported natively. You may simulate a 
 * stack by using a list or deque (double-ended queue), as long as you use only 
 * standard operations of a stack.

 * You may assume that all operations are valid (for example, no pop or peek operations 
 * will be called on an empty queue).
 *               
 **********************************************************************************/

class Queue {
public:
    // Push element x to the back of queue.
    void push(int x) {
        s1.push(x);
    }

    // Removes the element from in front of queue.
    void pop(void) {
        transfer(s1, s2);
        s2.pop();
        transfer(s2, s1);
    }

    // Get the front element.
    int peek(void) {
        transfer(s1, s2);
        int ret = s2.top();
        transfer(s2, s1);
        return ret;
    }

    // Return whether the queue is empty.
    bool empty(void) {
        return s1.empty();
    }
private:
    stack<int> s1, s2;
    void transfer(stack<int>& s1, stack<int>& s2) {
        while(!s1.empty()){
            s2.push(s1.top());
            s1.pop();
        }
    }
};

