#include<iostream>
#include<deque>
#include<memory>
#include<cassert>


template<typename T>
class BinarySearchTree
{
public:
	BinarySearchTree() : size_(0)
	{
		root_ = newNode(T()); // initial an empty node as root
	}
	virtual ~BinarySearchTree()
	{

	}

	struct TreeNode;
	typedef TreeNode* NodePtr;
	typedef void(*callback)(const T& data);

	struct TreeNode
	{
		NodePtr left;
		NodePtr right;
		T val;
		TreeNode(const T& x) : val(x)
		{
		}
	};


public:
	// default argument in member function is not belong to class, it's belong to caller, 
	// and should be visible to the caller. So i have to overload those function...
	// http://stackoverflow.com/questions/9286533/how-to-use-an-member-variable-as-a-default-argument-in-c


	NodePtr insert(const T& x)
	{
		return insert(x, root_);
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
			return insert(x, root->left);
		else if (x >= root->val)
			return insert(x, root->right);
	}

	void remove(const T& x)
	{
		remove(x, root_);
	}
	void remove(const T& x, NodePtr& root)
	{
		if (root == nullptr)
			return;
		if (x < root->val)
			remove(x, root->left);
		else if (x > root->val)
			remove(x, root->right);
		else // x == root->val
		{
			NodePtr l = root->left;
			NodePtr r = root->right;

			if( !l && !r)	{deleteNode(root);return;}
			if(!l && r) 	{deleteNode(root);root = r;return;}
			if(l && !r) 	{deleteNode(root);root = l;return;}

			NodePtr min = findMin(r);
			root->val = min->val;
			remove(min->val, min);
		}
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

private:
	NodePtr newNode(const T& x)
	{
		NodePtr node(new TreeNode(x));
		node->left = nullptr;
		node->right = nullptr;
		nodeList_.push_back(std::shared_ptr<TreeNode>(node));
		return node;
	}
	void deleteNode(NodePtr& node)
	{
		// for (auto it = nodeList_.begin(); it != nodeList_.end(); it++)
		// {
		// 	if ((*it)->val == node->val)
		// 	{
		// 		nodeList_.erase(it);
		// 		size_--;
		// 		node = nullptr;
		// 		return;
		// 	}
		// }
        node = nullptr;
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
		BinarySearchTree<int> t;
		t.insert(8);t.insert(3);t.insert(10);t.insert(1);
		t.remove(1);t.remove(3);
		t.insert(6);t.insert(14);t.insert(4);t.insert(7);t.insert(13);

        assert( t.find(13)->val == 13);
        assert( t.findMax()->val == 14);
        assert( t.findMin()->val == 4);

		t.traverse(printNode);
	}

	{
		BinarySearchTree<int> t;
		t.insert(8);t.insert(3);t.insert(10);t.insert(1);
		t.insert(6);t.insert(14);t.insert(4);t.insert(7);t.insert(13);

		t.traverse(printNode);
	}

	return 0;
}



