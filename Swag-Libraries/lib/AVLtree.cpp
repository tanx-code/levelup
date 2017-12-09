#include<iostream>
#include<deque>
#include<memory>
#include<cassert>


template<typename T>
class AVLTree
{
public:
	AVLTree() : size_(0)
	{
		root_ = newNode(T()); // initial an empty node as root
	}
	virtual ~AVLTree()
	{

	}

	struct TreeNode;
	typedef TreeNode* NodePtr;
	typedef void(*callback)(const T& data);

	struct TreeNode
	{
		NodePtr left;
		NodePtr right;
		unsigned char height; // can save space when meet large amount of nodes
		T val;
		TreeNode(const T& x) : val(x) , height(1) {}
	};


public:

	void traverse(callback func)
	{
		traverse(func, root_);
	}
	void traverse(callback func, NodePtr root) const
	{
		if (root == nullptr)
			return;
		traverse(func, root->left);
		func(root->val);
		traverse(func, root->right);
	}

	NodePtr insert(const T& x)
	{
		return root_ = insert(x, root_);
	}
	NodePtr insert(const T& x, NodePtr& root)
	{
		if (size_ == 0)
		{
			size_++;
			root->val = x;
			return root;
		}
		if (root == nullptr)
		{
			size_++;
			root = newNode(x);
			return root;
		}
		if (x < root->val)
		{
			root->left = insert(x, root->left);
			return balance(root);
		}
		else if (x >= root->val)
		{
			root->right = insert(x, root->right);
			return balance(root);
		}

	}

	NodePtr remove(const T& x)
	{
		return root_ = remove(x, root_);
	}
	NodePtr remove(const T& x, NodePtr& root)
	{
		if (root == nullptr)
			return nullptr;
		if (x < root->val)
			root->left = remove(x, root->left);
		else if (x > root->val)
			root->right = remove(x, root->right);
		else // x == root->val
		{
			NodePtr l = root->left;
			NodePtr r = root->right;

			if( !l && !r)	return nullptr;
			if(!l && r) return r;
			if(l && !r) return l;

			NodePtr min = findMin(r);
			root->val = min->val;
			root->right = removeMin(root->right);
		}

		return balance(root);
	}

	NodePtr find(const T& x)
	{
		return find(x, root_);
	}
	NodePtr find(const T& x, NodePtr& root) const
	{
		if (root == nullptr)
			return nullptr;
		if ( x == root->val)
			return root;
		if ( x < root->val)
			return find(x, root->left);
		if ( x > root->val)
			return find(x, root->right);
	}

	NodePtr findMin()
	{
		return findMin(root_);
	}
	// just find the most left node
	NodePtr findMin(NodePtr& root) const
	{
		if (root == nullptr || root->left == nullptr)
		{
			return root;
		}
		return findMin(root->left);
	}

	NodePtr findMax()
	{
		return findMax(root_);
	}
	NodePtr findMax(NodePtr& root) const
	{
		if (root == nullptr || root->right == nullptr)
		{
			return root;
		}
		return findMax(root->right);
	}

	size_t getSize() const
	{
		return size_;
	}

	NodePtr getRoot()
	{
		return root_;
	}

	bool isEmpty() const
	{
		return size_ == 0;
	}

private:
	// helper functions
	unsigned char getHeight(NodePtr &p) {
		return p?p->height : 0;
	}
	int getFactor(NodePtr &p) {
		return getHeight(p->right) - getHeight(p->left);
	}
	void fixHeight(NodePtr &p) {
		unsigned char hl = getHeight(p->left);
		unsigned char hr = getHeight(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}
	NodePtr rotateLeft(NodePtr &p) {
		NodePtr q = p->right;
		p->right = q->left;
		q->left = p;
		fixHeight(p);
		fixHeight(q);
		return q;
	}
	// symmetric copy of the left one
	NodePtr rotateRight(NodePtr &p) {
		NodePtr q = p->left;
		p->left = q->right;
		q->right = p;
		fixHeight(p);
		fixHeight(q);
		return q;
	}
	NodePtr balance(NodePtr &p) {
		fixHeight(p);
		if( getFactor(p) == 2) {
			if( getFactor(p->right) < 0)
				p->right = rotateRight(p->right);
			return rotateLeft(p);
		}
		if( getFactor(p) == -2) {
			if( getFactor(p->left) > 0)
				p->left = rotateLeft(p->left);
			return rotateRight(p);
		}
		// if no balance need, return itself
		return p;
	}
	NodePtr removeMin(NodePtr &p) {
		if(!p->left)
		{	
			deleteNode(p);
			return p->right;
		}
		p->left = removeMin(p->left);
		return balance(p);
	}

	NodePtr newNode(const T& x)
	{
		NodePtr node(new TreeNode(x));
		node->left = nullptr;
		node->right = nullptr;
		node->height = 1;
		nodeList_.push_back(std::shared_ptr<TreeNode>(node));
		return node;
	}
	void deleteNode(NodePtr& node)
	{
		for (auto it = nodeList_.begin(); it != nodeList_.end(); it++)
		{
			if ((*it)->val == node->val)
			{
				nodeList_.erase(it);
				size_--;
				node = nullptr;
				return;
			}
		}
	}
	NodePtr root_;
	size_t size_;
	std::deque<std::shared_ptr<TreeNode>> nodeList_;

};



void printNode(const int& x)
{
	std::cout << x << " ";
}


int main()
{
	{
		AVLTree<int> t;
		t.insert(8);t.insert(3);t.insert(10);t.insert(1);
		t.remove(1);t.remove(3);
		t.insert(6);t.insert(14);t.insert(4);t.insert(7);t.insert(13);

        assert( t.find(13)->val == 13);
        assert( t.findMax()->val == 14);
        assert( t.findMin()->val == 4);

		t.traverse(printNode);
	}

	{
		AVLTree<int> t;
		t.insert(8);t.insert(3);t.insert(10);t.insert(1);
		t.insert(6);t.insert(14);t.insert(4);t.insert(7);t.insert(13);

		t.traverse(printNode);
	}

	return 0;
}