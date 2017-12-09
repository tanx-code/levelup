class Solution {
public:
    // 判断二叉树是否平衡
    // 思路：用dfs把子树的高度信息返回
    bool isBalanced(TreeNode* root) {
        if(!root)
            return true;
        int md = treeDepth(root->left)-treeDepth(root->right);
        if(md>1||md<-1)
            return false;
        return isBalanced(root->left)&&isBalanced(root->right);
    }
    int treeDepth(TreeNode* t) //默认根节点的深度为1
    {
        if(!t)
            return 0;
        int left = 1,right = 1;
        left += treeDepth(t->left);
        right += treeDepth(t->right);
        return left>right?left:right;
    }
};

// Source : https://oj.leetcode.com/problems/balanced-binary-tree/
// Author : Hao Chen
// Date   : 2014-06-28

/********************************************************************************** 
* 
* Given a binary tree, determine if it is height-balanced.
* 
* For this problem, a height-balanced binary tree is defined as a binary tree in which 
* the depth of the two subtrees of every node never differ by more than 1.
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
    bool isBalanced(TreeNode *root) {
        int height=0;
        return isBalancedUtil(root, height);
    }

    bool isBalancedUtil(TreeNode* root, int& height){
       if(root==NULL){
          height=0;
          return true;
       }
       int lh=0, rh=0;
       bool isLeft = isBalancedUtil(root->left, lh);
       bool isRight = isBalancedUtil(root->right, rh);
       height = (lh > rh ? lh : rh) + 1;
       return (abs(lh-rh)<=1 && isLeft && isRight);
    }

};

//Notes: 
// I think the above solution should be more efficent than the below, 
//  but for leetcode, the below solution needs 60ms, the above needs 88ms
class Solution {
public:
    bool isBalanced(TreeNode *root) {
        if (root==NULL) return true;
        
        int left = treeDepth(root->left); 
        int right = treeDepth(root->right);
        
        if (left-right>1 || left-right < -1) {
            return false;
        }
        return isBalanced(root->left) && isBalanced(root->right);
    }
    
    int treeDepth(TreeNode *root) {
        if (root==NULL){
            return 0;
        }

        int left=1, right=1;
        
        left += treeDepth(root->left);
        right += treeDepth(root->right);
        
        return left>right?left:right;
    }

};
