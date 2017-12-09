class Solution {
public:
    // 填填补补去修改程序的习惯不好，先考虑是不是一开始的设计的问题
    // 一开始的设计需要考虑一些边界情况，后来重新想了下，弄了个头结点的前驱结点，完美AC
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *plast, *pfront, *phead;
        plast = pfront = phead = new ListNode(0);
        plast->next = head;
        while(1)
        {
            while(n>0){
                --n;
                pfront = pfront->next;
            }
            if(!pfront->next)
                break;
            plast = plast->next;
            pfront = pfront->next;
        }
        plast->next = plast->next->next;
        return phead->next;
    }
};


// Source : https://oj.leetcode.com/problems/remove-nth-node-from-end-of-list/
// Author : Hao Chen
// Date   : 2014-06-21

/********************************************************************************** 
* 
* Given a linked list, remove the nth node from the end of list and return its head.
* 
* For example,
* 
*    Given linked list: 1->2->3->4->5, and n = 2.
* 
*    After removing the second node from the end, the linked list becomes 1->2->3->5.
* 
* Note:
* Given n will always be valid.
* Try to do this in one pass.
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
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        if (head==NULL || n<=0){
            return NULL;
        }
        ListNode fakeHead(0);
        fakeHead.next=head;
        head=&fakeHead;
        
        ListNode *p1, *p2;
        p1=p2=head;
        for(int i=0; i<n; i++){
            if (p2==NULL) return NULL;
            p2=p2->next;
        }
        while (p2->next!=NULL){
            p2=p2->next;
            p1=p1->next;
        }
        
        p1->next = p1->next->next;
        return head->next;
    }
};
