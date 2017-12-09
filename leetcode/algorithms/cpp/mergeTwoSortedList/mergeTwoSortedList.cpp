class Solution {
public:
    // 把我自己的写法放到下面去了，复习的时候优先看这个解法。
    // 再写一遍！关键点有两个
    // p1不动，插p2。
    // 要一直keep好p1的前驱指针，这个技巧很有用。！
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(!l1)
            return l2;
        if(!l2)
            return l1;
        ListNode *h = new ListNode(0);
        h->next = l1;
        ListNode *pre = h;
        ListNode *p1 = l1,*p2 = l2;
        while(p1&&p2)
        {
            if(p1->val < p2->val)
            {
                pre = p1;
                p1 = p1->next;
            }
            else
            {
                pre->next = p2;
                p2 = p2->next;
                pre = pre->next;
                pre->next = p1;
            }
        }

        if(p2)
            pre->next = p2;
        return h->next;
        
    }
    // md，本来是也是打算把第二个链直接做插入，插到第一个中去，但是没想到给他弄一个头结点，最后搞得很麻烦就换这个白痴方法了。。
    // 太坑了，感觉自己好菜。
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(!l1)
            return l2;
        if(!l2)
            return l1;
        ListNode* p1 = l1,*p2 = l2;
        ListNode* h,*ph;
        h = new ListNode(0);
        ph = h;
        while(p1&&p2)
        {
            if((p1->val)==(p2->val))
            {
                ph->val = p1->val;
                ph->next = new ListNode(0);
                ph = ph->next;

                ph->val = p1->val;
                ph->next = new ListNode(0);

                p1=p1->next;
                p2=p2->next;

                if(!p1&&!p2)
                {
                    ph->next =NULL;
                    break;
                }
                ph = ph->next;

                continue;
            }
            if((p1->val)<(p2->val))
            {
                ph->val = p1->val;
                ph->next = new ListNode(0);
                p1=p1->next;
                ph = ph->next;
                continue;
            }
            if((p1->val)>(p2->val))
            {
                ph->val = p2->val;
                ph->next = new ListNode(0);
                p2=p2->next;
                ph = ph->next;
                continue;
            }
        }
        if(!p1&&p2)
        {
            ph->val = p2->val;
            ph->next = p2->next;
            return h;
        }
        if(p1&&!p2)
        {
            ph->val = p1->val;
            ph->next = p1->next;
            return h;
        }

        return h;
        
    }
    

};
// Source : https://oj.leetcode.com/problems/merge-two-sorted-lists/
// Author : Hao Chen
// Date   : 2014-07-06

/********************************************************************************** 
* 
* Merge two sorted linked lists and return it as a new list. The new list should be 
* made by splicing together the nodes of the first two lists.
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
    Solution(){
        srand(time(NULL));
    }
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        switch (random()%3){
            case 0:
                return mergeTwoLists01(l1, l2);
            case 1:
                return mergeTwoLists02(l1, l2);
            default:
                return mergeTwoLists03(l1, l2);
        }
    }
    
    /* merge the 2nd list into 1st list*/
    ListNode *mergeTwoLists01(ListNode* head1, ListNode* head2){
        ListNode *p1 = head1,  *p2=head2;
        static ListNode dummy(0);
    
        dummy.next = p1;
        ListNode *prev = &dummy;
    
        while(p1 && p2){
            if(p1->val < p2->val){
                prev = p1;
                p1 = p1->next;
            }else{
                prev->next = p2;
                p2 = p2->next;
                prev = prev->next;
                prev->next = p1;
            }
        }
        if (p2){
            prev->next = p2;
        }
    
        return dummy.next;
    }


    /* merge two lists to the new list */
    ListNode *mergeTwoLists02(ListNode *l1, ListNode *l2) {
        ListNode *l=NULL, *p=NULL;
        
        while (l1!=NULL && l2!=NULL ){
            ListNode *n=NULL;
            if (l1->val < l2-> val){
                n = l1;
                l1=l1->next;
            }else{
                n = l2;
                l2=l2->next;
            }
            if (l==NULL){
                l = p = n;
            }else{
                p->next = n;
                p = p->next;
            }
        }
        
        ListNode* rest = l1 ? l1 :l2;
        
        l = mergeTheRest(rest, l, p);
       
        
        return l;
    }

    ListNode* mergeTheRest(ListNode* l, ListNode*head, ListNode* tail){
        if (l){
            if (head && tail ){
                tail->next = l;
            }else{
                head = l;
            }
        }
        return head;
    }

    /*  
     * You can see the 2nd slution's code is quite complicated, 
     * because it need to check the (head==NULL) situation.
     * We can use the "pointer to pointer" to make the code more clean
     * however, this would be bad for performance.
     */
    ListNode *mergeTwoLists03(ListNode *l1, ListNode *l2) {
        ListNode *head = NULL;
        ListNode **pTail = &head;
        while (l1 != NULL && l2 != NULL) {
            if (l1->val < l2->val) {
                *pTail = l1;
                l1 = l1->next;
            } else {
                *pTail = l2;
                l2 = l2->next;
            }
            pTail = &(*pTail)->next;
        }
        *pTail = (l1 != NULL ? l1 : l2);
        return head;
    }

};
