class Solution {
public:
    // 正常做法。
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int  lengA = 0, lengB = 0;
        ListNode *pA = headA, *pB = headB;
        // get the length of A,B list
        while(pA||pB){
            if(pA){
                lengA++;
                pA = pA->next;
            }
            if(pB){
                lengB++;
                pB = pB->next;
            }
        }
        // let A longgest
        if(lengA<lengB){
            swap(headA,headB);
        }
        // let A,B have "same" length
        for(int i=0; i<abs(lengA-lengB); i++){
            headA = headA->next;
        }
        // move two ptr at same pace
        while(headA!=headB){
            headA = headA->next;
            headB = headB->next;
        }
        return headA;
    }
    
    
    // 谁告诉我这种方法哪里错了？？
    // 虽然是O(n) space。。虽然很丑，但是错误原因是什么？
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        set<ListNode*> setA,setB;
        while(headA||headB)
        {
            if(headA)
            {
                setA.push_back(headA);
                headA = headA->next;
            }
            if(headB)
            {
                setB.push_back(headB);
                headB = headB->next;
            }
        }
        set<ListNode*> result;
        set_intersection(setA.begin(), setA.end(),
                          setB.begin(), setB.end(),
                          inserter(result,result.begin()));
        if(result.size()==0)
            return nullptr;
        return result[0];
    }
};

// Source : https://oj.leetcode.com/problems/intersection-of-two-linked-lists/
// Author : Hao Chen
// Date   : 2014-12-01

/********************************************************************************** 
 * 
 * Write a program to find the node at which the intersection of two singly linked lists begins.
 * 
 * For example, the following two linked lists: 
 * 
 *
 *    A:          a1 → a2
 *                       ↘
 *                         c1 → c2 → c3
 *                       ↗            
 *    B:     b1 → b2 → b3
 * 
 * begin to intersect at node c1.
 * 
 * Notes:
 * 
 * If the two linked lists have no intersection at all, return null.
 * The linked lists must retain their original structure after the function returns. 
 * You may assume there are no cycles anywhere in the entire linked structure.
 * Your code should preferably run in O(n) time and use only O(1) memory.
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
        ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {

            //caculate the length of each List
            int lenA = getListLength(headA);
            int lenB = getListLength(headB);

            if (lenA<=0 || lenB<=0 ) return NULL;

            //let List A is the longest List;
            if (lenA < lenB){
                swap(headA, headB);
            }

            //move head of List A, make both of Lists are same length 
            for (int i=0; i<abs(lenA-lenB); i++){
                headA = headA->next;
            }

            //synced travel both of Lists and check their nodes are same or not 
            while (headA != headB){
                headA = headA->next;
                headB = headB->next;
            }

            return headA;
        }
    private:    
        inline int getListLength(ListNode *head){
            int len=0;
            while(head!=NULL){
                head = head->next;
                len++;
            }
            return len;
        }
};
