/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode *p=nullptr,*h=nullptr;
        while(head)
        {
            // 画图理解的时候，不要想着去移动结点，而是想着去改变指针指向的方向。
            p = head->next; //p记录下一个要操作的结点
            head->next = h; //h为head的前驱
            h = head;
            head = p;
        }
        return h;
    }
    // 递归其实更好理解。。我还看了好久。。
    // 就是把所有的 -> 变成 <- ，然后原先最后一个结点就变成了头结点。是不是很简单粗暴。
    // 由此可以看出递归的一个特性，就是能保存每次迭代的值
    ListNode* reverseList(ListNode* head) {
        if(!head || !head->next)
            return head;
        ListNode *p = reverseList(head->next); 
        head->next->next = head; // 相当于只是把指向的方向变了
        head->next = nullptr;
        return p;
    }
};

// Source : https://leetcode.com/problems/reverse-linked-list/
// Author : Hao Chen
// Date   : 2015-06-09

/********************************************************************************** 
 * 
 * Reverse a singly linked list.
 * 
 * click to show more hints.
 * 
 * Hint:
 * A linked list can be reversed either iteratively or recursively. Could you implement both?
 * 
 *               
 **********************************************************************************/


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList_iteratively(ListNode* head) {
        ListNode *h=NULL, *p=NULL;
        while (head){
            p = head->next;
            head->next = h;
            h = head;
            head = p;
        }
        return h;
    }
    ListNode* reverseList_recursively(ListNode* head) {
        if (head==NULL || head->next==NULL) return head;
        ListNode *h = reverseList_recursively(head->next);
        head->next->next = head;
        head->next = NULL;
        return h;
        
    }
    ListNode* reverseList(ListNode* head) {
        return reverseList_iteratively(head);
        return reverseList_recursively(head);
    }
};
