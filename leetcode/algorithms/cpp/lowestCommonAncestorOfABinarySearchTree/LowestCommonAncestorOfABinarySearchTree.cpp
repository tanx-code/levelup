class Solution {
public:
    // 这是一种最直白的做法。。。我其实想到了，如果两个结点在根结点两边，那公共结点一定是根节点。
    // 最低的意思是深度最深的
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root)
            return root;
        vector<TreeNode*> vp,vq;
        vp = Search(root,p);
        vq = Search(root,q);
        auto i=vp.begin(),j = vq.begin();
        for(;i!=vp.end()&&j!=vq.end();i++,j++)
        {
            if(((*i)->val)!=((*j)->val))
                return *(i-1);
        }
        if(i==vp.end())
            return p;
        if(j==vq.end())
            return q;
        return p;
            
    }
    vector<TreeNode*> Search(TreeNode* root,TreeNode* p)
    {
        vector<TreeNode*> rs;
        while(root)
        {
            rs.push_back(root);
            if(root->val==p->val)
            {
                break;
            }

            if(root->val>p->val)
            {    
                root = root->left;
            }
            else
            {
                root = root->right;
            }
        }
        return rs;
    }
    
    // 看了chenhao的做法，再写一下
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        while(root){
            if(p->val < root->val && q->val < root->val)
            {
                root = root->left;
                continue;
            }
            if(p->val > root->val && q->val > root->val)
            {
                root = root->right;
                continue;
            }
            return root;
        }
        return NULL;
    }
};

// Source : https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
// Author : Hao Chen
// Date   : 2015-07-17

/********************************************************************************** 
 * 
 * Given a binary search tree (BST), find the lowest common ancestor (LCA) of two given 
 * nodes in the BST.
 * 
 * According to the definition of LCA on Wikipedia: “The lowest common ancestor is 
 * defined between two nodes v and w as the lowest node in T that has both v and w as 
 * descendants (where we allow a node to be a descendant of itself).”
 * 
 *         _______6______
 *        /              \
 *     ___2__          ___8__
 *    /      \        /      \
 *    0      _4       7       9
 *          /  \
 *          3   5
 * 
 * For example, the lowest common ancestor (LCA) of nodes 2 and 8 is 6. Another example 
 * is LCA of nodes 2 and 4 is 2, since a node can be a descendant of itself according 
 * to the LCA definition.
 *               
 *               
 **********************************************************************************/


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
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

        while(root) {
            if (p->val > root->val && q->val > root->val) {
                root = root->right;
                continue;
            }
            if (p->val < root->val && q->val < root->val) {
                root = root->left;
                continue;
            }
            return root;
            
        }
        return NULL;
    }
};
