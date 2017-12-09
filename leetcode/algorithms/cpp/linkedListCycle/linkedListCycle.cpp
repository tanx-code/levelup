// Source : https://oj.leetcode.com/problems/linked-list-cycle/
// Author : Hao Chen
// Date   : 2014-07-03

/********************************************************************************** 
* 
* Given a linked list, determine if it has a cycle in it.
* 
* Follow up:
* Can you solve it without using extra space?
* 
*               
**********************************************************************************/

/*
 * if there is a cycle in the list, then we can use two pointers travers the list.
 *
 * one pointer traverse one step each time, another one traverse two steps each time.
 *
 * so, those two pointers meet together, that means there must be a cycle inside the list.
 */

// 我没做出来，看了答案之后真是学到了！@其实快行指针的思想我见过，但是以前没理解，而且这题有创新。
// 相当于用一个指针去追另外一个指针，而且关键在于两个指针的步长的差为1，如果成环的话，是一定能在某个结点相遇的！
// 就是利用了这一点！才这么放心的让他们在环里面跑！
bool hasCycle(ListNode *head) {
    if (head==NULL || head->next==NULL) return false;
    ListNode* fast=head;
    ListNode* slow=head;
    do{
        slow = slow->next;
        fast = fast->next->next;
    }while(fast != NULL && fast->next != NULL && fast != slow);
    return fast == slow? true : false;
} 
