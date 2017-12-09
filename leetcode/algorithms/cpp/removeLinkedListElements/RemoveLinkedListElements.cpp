// 删除链表结点，弄个新的头结点可以简化一点。这是惯用的技巧了。
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        // ListNode* mhead = new ListNode(0);
        // ListNode* p = mhead;
        // p->next = head;
        ListNode mhead(-1);// 这样就保证0内存泄露了。
        ListNode *p = &mhead;
        p->next = head;
        while(p->next){
            if(p->next->val == val){
                ListNode* tdel = p->next;
                p->next =p->next->next;
                delete tdel;
            }
            else{
                p = p->next;
            }
        }
        return mhead->next;
    }
};

// Source : https://leetcode.com/problems/remove-linked-list-elements/
// Author : Hao Chen
// Date   : 2015-06-09

/********************************************************************************** 
 * 
 * Remove all elements from a linked list of integers that have value val.
 * 
 * Example
 * Given: 1 --> 2 --> 6 --> 3 --> 4 --> 5 --> 6,  val = 6
 * Return: 1 --> 2 --> 3 --> 4 --> 5
 * 
 * Credits:Special thanks to @mithmatt for adding this problem and creating all test cases.
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
    ListNode* removeElements(ListNode* head, int val) {
        static ListNode dummy(-1);
        dummy.next = head;
        ListNode *p = &dummy;
        
        while( p->next) {
            if (p->next->val == val) {
                p->next = p->next->next;
            }else{
                p = p->next;
            }
        }
        
        return dummy.next;
    }
};


