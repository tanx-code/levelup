class Solution {
public:

    int minDepth(TreeNode* root) {
        queue<TreeNode*> q;
        if(!root)
                return 0;
        int depth = 1;
        q.push(root);
        TreeNode* last = root; //当从队列出来的是上一层的最后一个结点，意味着现在队列里的是下一层的所有结点。
        while(!q.empty())
        {
            TreeNode* t = q.front();
            q.pop();
            
            if(!t->left&&!t->right)
                return depth;
            if(t->left)
                q.push(t->left);
            if(t->right)
                q.push(t->right);
            if(t==last)
            {
                depth++;
                last = q.back();
            }
        }
        return depth;
    }
    
    // 递归的方法。分治的思想，min(左子树的最小深度,右子树的最小深度)
    // 注意：一定是到*叶子*结点的最小深度。
    // 其实递归还容易错，还不如用层序遍历的方法呢，而且最后效率也不如层序遍历。
    int minDepth(TreeNode* root) {
        if(!root)
            return 0;
        if(!root->left&&!root->right)
            return 1;
        if(root->left&&!root->right)
            return 1+minDepth(root->right);
        if(!root->left&&root->right)
            return 1+minDepth(root->left);
        return min(1+minDepth(root->left),1+minDepth(root->right));
    }
};

// Source : https://oj.leetcode.com/problems/minimum-depth-of-binary-tree/
// Author : Hao Chen
// Date   : 2014-06-22

/********************************************************************************** 
* 
* Given a binary tree, find its minimum depth.
* 
* The minimum depth is the number of nodes along the shortest path from the root node 
* down to the nearest leaf node.
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
    int minDepth(TreeNode *root) {
        if (root==NULL){
            return 0;
        }
        if (root->left==NULL && root->right==NULL){
            return 1;
        }
        int left=INT_MAX;
        if (root->left){
            left = minDepth(root->left) + 1 ;
        }
        int right=INT_MAX;
        if (root->right){
            right = minDepth(root->right) + 1;
        }
        
        return left<right ? left : right;
        
    }
};
