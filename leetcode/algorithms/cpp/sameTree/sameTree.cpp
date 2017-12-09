/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    // 这题关键要注意所有的限制条件
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if( (p && !q)||(!p && q) ) // p为空且q不为空，或者，p不为空q为空，就不同了
            return false;
        if( p==NULL && q==NULL)     // p，q同时为空，是相同的。
            return true;
        if( p->val != q->val)       // p,q的值要相等
            return false;
        if( isSameTree(p->left,q->left) && isSameTree(p->right,q->right))   //两颗树的子树要相等
            return true;
        return false; // 不等的话就不同了。
    }
};


// Source : https://oj.leetcode.com/problems/same-tree/
// Author : Hao Chen
// Date   : 2014-06-27

/********************************************************************************** 
* 
* Given two binary trees, write a function to check if they are equal or not.
* 
* Two binary trees are considered equal if they are structurally identical and the nodes have the same value.
* 
*               
**********************************************************************************/

/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    Solution(){
        srand(time(NULL));
    }
    bool isSameTree(TreeNode *p, TreeNode *q) {
        if (random()%2){
            return isSameTree1(p, q);
        }
        return isSameTree2(p, q);
    }
    
    bool isSameTree1(TreeNode *p, TreeNode *q) {
        if(!p && !q) return true;  
        if(!p || !q) return false;  
        return (p->val == q->val) &&  
                isSameTree(p->left, q->left) &&   
                isSameTree(p->right, q->right);
    }
    
    bool isSameTree2(TreeNode *p, TreeNode *q) {
        
        queue<TreeNode*> q1, q2;
        q1.push(p);
        q2.push(q);
        while (q1.size()>0 && q2.size()>0 ){
            TreeNode* p1 = q1.front();
            q1.pop();
            TreeNode* p2 = q2.front();
            q2.pop();
            if (!p1 && !p2) continue;
            if (!p1 || !p2)  return false;

            if ( p1->val != p2->val) {
                return false;
            }

            q1.push(p1->left);
            q2.push(p2->left);

            q1.push(p1->right);
            q2.push(p2->right);

        }
        return true;
    }
};
