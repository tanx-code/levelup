// O(n) space , O(n)time
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> vec;
        while(head){
            vec.push_back(head->val);
            head = head->next;
        }
        auto i = vec.begin();
        auto j = vec.rbegin();
        for(;i!=vec.end() && j!=vec.rend();i++,j++){
            if(*i!=*j)
                return false;
        }
        return true;
    }
};
// O(1)space ,O(n) tme
class Solution {
public:
ListNode * getMiddle(ListNode *head) {
	ListNode *p1 = head,*p2 = head;
	while (p2 && p2->next) {
		p1 = p1->next;
		p2 = p2->next->next;
	}
	return p1;
}
ListNode * reverseLink(ListNode *head) {
	ListNode *p1 = nullptr;
	ListNode *p2 = head;
	while(p2){
		ListNode *t = p2->next;
		p2->next = p1;
		p1 = p2;
		p2 = t;
	}
	return p1;
}
bool isPalindrome(ListNode *head){
	ListNode *mid = getMiddle(head);
	ListNode *right = reverseLink(mid);
	for(;head && right; head=head->next,right=right->next) {
		if(head->val != right->val)
			return false;
	}
	return true;
}
};
// Source : https://leetcode.com/problems/palindrome-linked-list/
// Author : Hao Chen
// Date   : 2015-07-17

/********************************************************************************** 
 * 
 * Given a singly linked list, determine if it is a palindrome.
 * 
 * Follow up:
 * Could you do it in O(n) time and O(1) space?
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
    ListNode* findMiddle(ListNode* head) {
        ListNode *p1=head, *p2=head;
        while(p2 && p2->next){
            p1 = p1->next;
            p2 = p2->next->next;
        }
        return p1;
    }
    
    ListNode* reverseLink(ListNode* head) {
        ListNode* p=NULL;
        
        while (head) {
            ListNode* q = head->next;
            head->next = p;
            p = head;
            head = q;
        }
        return p;
    }
    
    bool isPalindrome(ListNode* head) {
        ListNode* pMid = findMiddle(head);
        ListNode* pRev = reverseLink(pMid); 
        for(;head!=pMid; head=head->next, pRev=pRev->next) {
            if (head->val != pRev->val) {
                return false;
            }
        }
        return true;
    }
};


