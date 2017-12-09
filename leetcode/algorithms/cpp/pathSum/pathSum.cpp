// 我觉得我的算法还算简洁吧。
// 总结：把结点的和依次通过参数的方式传下去，碰到没有孩子结点的情况就把和记录下来。

class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        countTraverse(root,0);
        return m_set.count(sum)==1;
    }
    
private:
    void countTraverse(TreeNode* root, int val)
    {
        if(!root)
            return;
        if(!root->left&&!root->right)
        {
            m_set.insert(val+root->val);
        }
        countTraverse(root->left,val+root->val);
        countTraverse(root->right,val+root->val);
    }
    set<int> m_set;
};

// Source : https://oj.leetcode.com/problems/path-sum/
// Author : Hao Chen
// Date   : 2014-06-22

/********************************************************************************** 
* 
* Given a binary tree and a sum, determine if the tree has a root-to-leaf path 
* such that adding up all the values along the path equals the given sum.
* 
* For example:
* Given the below binary tree and sum = 22,
* 
*               5
*              / \
*             4   8
*            /   / \
*           11  13  4
*          /  \      \
*         7    2      1
* 
* return true, as there exist a root-to-leaf path 5->4->11->2 which sum is 22.
*               
**********************************************************************************/

#include <time.h>

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
    bool hasPathSum(TreeNode *root, int sum) {
        if (random()%2){
            return hasPathSum1(root, sum);    
        }
        return hasPathSum2(root, sum);
    }
    
    bool hasPathSum1(TreeNode *root, int sum) {
        if (root==NULL) return false;
        vector<TreeNode*> v;
        v.push_back(root);
        while(v.size()>0){
            TreeNode* node = v.back();
            v.pop_back();
            if (node->left==NULL && node->right==NULL){
                if (node->val == sum){
                    return true;
                }
            }
            if (node->left){
                node->left->val += node->val;
                v.push_back(node->left);
            }
            if (node->right){
                node->right->val += node->val;
                v.push_back(node->right);
            }
        }
        return false;
        
    }
    
    bool hasPathSum2(TreeNode *root, int sum) {
        
        if (root==NULL) return false;
        
        if (root->left==NULL && root->right==NULL ){
            return (root->val==sum);
        }
        
        if (root->left){
            root->left->val += root->val;
            if (hasPathSum2(root->left, sum)){
                return true;
            }
        }
        
        if (root->right){
            root->right->val += root->val;
            if (hasPathSum2(root->right, sum)){
                return true;
            }
        }
        
        return false;
    }

};
