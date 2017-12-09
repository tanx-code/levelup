// 啊啊啊啊，又被chenhao的做法完虐了，上次用implement queue using stack 我就没设计好，效率太低
// 这次设计好了，结果思路不够简洁。。。
// 按照chenhao的做法，就是把队列头pop出来放到队列尾去！
class Stack {
public:
    // Push element x onto stack.
    void push(int x) {
        q1.push(x);
    }

    // Removes the element on top of the stack.
    void pop() {
        while(!q1.empty())
        {
            q2.push(q1.front());
            q1.pop();
        }
        while(!q2.empty())
        {
            
            if(q2.size()==1)
                break;
            q1.push(q2.front());
            q2.pop();
        }
        q2.pop();
    }

    // Get the top element.
    int top() {
        int result = 0;
        while(!q1.empty())
        {
            q2.push(q1.front());
            q1.pop();
        }
        while(!q2.empty())
        {
            if(q2.size()==1)
                result = q2.front();
            q1.push(q2.front());
            q2.pop();
        }
        return result;
    }

    // Return whether the stack is empty.
    bool empty() {
        return q1.empty();
    }
private:
    queue<int> q1,q2;
};


// Source : https://leetcode.com/problems/implement-stack-using-queues/
// Author : Hao Chen
// Date   : 2015-06-13

/********************************************************************************** 
 * 
 * Implement the following operations of a stack using queues.
 * 
 * push(x) -- Push element x onto stack.
 * 
 * pop() -- Removes the element on top of the stack.
 * 
 * top() -- Get the top element.
 * 
 * empty() -- Return whether the stack is empty.
 * 
 * Notes:
 * 
 * You must use only standard operations of a queue -- which means only push to back, 
 * peek/pop from front, size, and is empty operations are valid.
 *
 * Depending on your language, queue may not be supported natively. You may simulate 
 * a queue by using a list or deque (double-ended queue), as long as you use only 
 * standard operations of a queue.
 *
 * You may assume that all operations are valid (for example, no pop or top operations 
 * will be called on an empty stack).
 * 
 * Update (2015-06-11):
 * The class name of the Java function had been updated to MyStack instead of Stack.
 * 
 * Credits:Special thanks to @jianchao.li.fighter for adding this problem and all test cases.
 *               
 **********************************************************************************/


class Stack {
    public:
        // Push element x onto stack.
        void push(int x) {
            nums.push(x);
        }
        // Removes the element on top of the stack.
        void pop() {
            if (!empty()) {
                int len = nums.size()-1;
                //Don't treat the "-->" is a new operator. ;-)
                while ( len-->0) {
                    nums.push(nums.front());
                    nums.pop();
                }
                nums.pop();
            }
        }
        // Get the top element.
        int top() {
            return nums.back();
        }
        // Return whether the stack is empty.
        bool empty() {
            return nums.empty();
        }

    private:
        queue<int> nums;
};
