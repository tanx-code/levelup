#include<iostream>
#include<deque>
#include<memory>
#include<cassert>

// 难产代码 


template<typename T>
class RBTree
{
public:
	RBTree() : size_(0)
	{
		root_ = newNode(T()); // initial an empty node as root
		deleteNode_ = nullptr;
	}
	virtual ~RBTree()
	{

	}

	struct TreeNode;
	typedef TreeNode* NodePtr;
	typedef void(*callback)(const T& data);
	typedef bool RBColor;


	struct TreeNode
	{
		NodePtr left;
		NodePtr right;
		NodePtr parent;
		RBColor color;

		unsigned char height; // can save space when meet large amount of nodes
		T val;
		TreeNode(const T& x) : val(x), height(1)
		{
		}
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
		NodePtr z = insert(x, root_);
		NodePtr y;

		if (z->parent == nullptr) return root_;

		// 如果儿子和父亲都是红色的，就通过这个while循环，不断朝着树根变色，旋转。
		// 如果parent是黑的，那么可以直接插入，则不进入while循环
		while (z->parent->color == rbRed)
		{
			// 在左边的时候
			if (z->parent == z->parent->parent->left)
			{
				// y为z的叔叔节点
				y = z->parent->parent->right;

				// 父亲和叔叔节点都是红色
				if (y->color == rbRed)
				{
					// 父亲，叔叔节点颜色设置为黑
					z->parent->color = rbBlack;
					y->color = rbBlack;

					// 爷爷节点设置为红色
					z->parent->parent->color = rbRed;
					// z等于爷爷节点
					z = z->parent->parent;
				}
				// 父亲节点是红色，叔叔节点是黑色
				else
				{
					// 这里进行了旋转，所以要更新节点的链接关系。
					if (z == z->parent->left)
					{
						NodePtr f = z->parent->parent;
						z = rotateLeft(z->parent);
						f->left = z;
						z = z->left;
					}
					NodePtr f = z->parent->parent->parent;
					z->parent->color = rbBlack;
					z->parent->parent->color = rbRed;
					z = rotateRight(z->parent->parent);
					if (f)
					{
						f->left = z;
						z->parent = f;
					}
				}
			}
			// 在右边的时候
			else
			{

				y = z->parent->parent->left;

				if (y && y->color == rbRed)
				{
					z->parent->color = rbBlack;
					y->color = rbBlack;
					z->parent->parent->color = rbRed;
					z = z->parent->parent;
				}
				else
				{
					// 这里进行了旋转，所以要更新节点的链接关系。
					if (z == z->parent->left)
					{
						NodePtr f = z->parent->parent;
						z = rotateRight(z->parent);
						f->right = z;
						z->parent = f;
						z = z->right;
					}
					NodePtr f = z->parent->parent->parent;
					z->parent->color = rbBlack;
					z->parent->parent->color = rbRed;
					z = rotateLeft(z->parent->parent);
					if (f)
					{
						f->right = z;
						z->parent = f;
					}
				}
			}
			// 到了树根节点则退出
			if (z->parent == nullptr) break;
		}
		
		if(!z->parent) root_ = z;
		root_->color = rbBlack;
		return root_;
	}

	// 返回的是插入节点
	NodePtr insert(const T& x, NodePtr& root)
	{
		if (size_ == 0)
		{
			size_++;
			root->val = x;
			root->color = rbBlack; // root node's color is black
			return root;
		}

		if (x < root->val)
		{
			if (root->left == nullptr)
			{
				size_++;
				root->left = newNode(x);
				root->left->parent = root;
				return root->left;
			}
			return insert(x, root->left);
		}
		else if (x >= root->val)
		{
			if (root->right == nullptr)
			{
				size_++;
				root->right = newNode(x);
				root->right->parent = root;
				return root->right;
			}
			return insert(x, root->right);
		}
	}




	void remove(const T& x)
	{

		remove(x,root_);
		if (!deleteNode_) return;

		if (deleteNode_->color == rbBlack)
		{
			root_ = rb_erase_rebalance(deleteNode_, deleteNode_->parent, root_);
		}
	}
	NodePtr  rb_erase_rebalance(NodePtr node, NodePtr parent, NodePtr root)
	{
		NodePtr other, o_left, o_right;   //x的兄弟*other，兄弟左孩子*o_left,*o_right  

		while ((!node || node->color == rbBlack) && node != root)
		{
			if (parent->left == node)
			{
				other = parent->right;
				if (other->color == rbRed)   //情况1：x的兄弟w是红色的  
				{
					other->color = rbBlack;
					parent->color = rbRed;   //上俩行，改变颜色，w->黑、p[x]->红。  
					
					{
						NodePtr x = rotateLeft(parent);
						NodePtr tp = parent->parent;
						bool r;
						if (tp) r = (tp->left == parent);
						if (!tp) root_ = x;
						else
						{
							r ? tp->left = x : tp->right = x;
							x->parent = tp;
						}
					}
					  //再对p[x]做一次左旋  
					other = parent->right;  //x的新兄弟new w 是旋转之前w的某个孩子。其实就是左旋后的效果
				}
				if ((!other->left || other->left->color == rbBlack) &&
					(!other->right || other->right->color == rbBlack))
					//情况2：x的兄弟w是黑色，且w的俩个孩子也都是黑色的

				{                         //由于w和w的俩个孩子都是黑色的，则在x和w上得去掉一黑色，  
					other->color = rbRed;   //于是，兄弟w变为红色。  
					node = parent;    //p[x]为新结点x  
					parent = node->parent;  //x<-p[x]  
				}
				else                       //情况3：x的兄弟w是黑色的，  
				{                          //且，w的左孩子是红色，右孩子为黑色。  
					if (!other->right || other->right->color == rbBlack)
					{
						if ((o_left = other->left))   //w和其左孩子left[w]，颜色交换。  
						{
							o_left->color = rbBlack;    //w的左孩子变为由黑->红色  
						}
						other->color = rbRed;           //w由黑->红  
						 //再对w进行右旋，从而红黑性质恢复。
						{
							NodePtr x = rotateRight(other);
							NodePtr tp = other->parent;
							bool r;
							if (tp) r = (tp->left == other);
							if (!tp) root_ = x;
							else
							{
								r ? tp->left = x : tp->right = x;
								x->parent = tp;
							}
						}
						other = parent->right;        //变化后的，父结点的右孩子，作为新的兄弟结点w。
					}
					//情况4：x的兄弟w是黑色的  
					other->color = parent->color;  //把兄弟节点染成当前节点父节点的颜色。  
					parent->color = rbBlack;  //把当前节点父节点染成黑色  
					if (other->right)      //且w的右孩子是红  
					{
						other->right->color = rbBlack;  //兄弟节点w右孩子染成黑色  
					}

					{
						NodePtr x = rotateLeft(parent);
						NodePtr tp = parent->parent;
						bool r;
						if (tp) r = (tp->left == parent);
						if (!tp) root_ = x;
						else
						{
							r ? tp->left = x : tp->right = x;
							x->parent = tp;
						}
					}
					node = root;   //并把x置为根。  
					break;
				}
			}
			//下述情况与上述情况，原理一致。分析略。  
			else
			{
				other = parent->left;
				if (other->color == rbRed)
				{
					other->color = rbBlack;
					parent->color = rbRed;
					{
						NodePtr x = rotateRight(parent);
						NodePtr tp = parent->parent;
						bool r;
						if (tp) r = (tp->left == parent);
						if (!tp) root_ = x;
						else
						{
							r ? tp->left = x : tp->right = x;
							x->parent = tp;
						}
					}

					other = parent->left;
				}
				if ((!other->left || other->left->color == rbBlack) &&
					(!other->right || other->right->color == rbBlack))
				{
					other->color = rbRed;
					node = parent;
					parent = node->parent;
				}
				else
				{
					if (!other->left || other->left->color == rbBlack)
					{
						if ((o_right = other->right))
						{
							o_right->color = rbBlack;
						}
						other->color = rbRed;

						{
							NodePtr x = rotateLeft(other);
							NodePtr tp = other->parent;
							bool r;
							if (tp) r = (tp->left == other);
							if (!tp) root_ = x;
							else
							{
								r ? tp->left = x : tp->right = x;
								x->parent = tp;
							}
						}
						other = parent->left;
					}
					other->color = parent->color;
					parent->color = rbBlack;
					if (other->left)
					{
						other->left->color = rbBlack;
					}
					{
						NodePtr x = rotateRight(parent);
						NodePtr tp = parent->parent;
						bool r;
						if (tp) r = (tp->left == parent);
						if (!tp) root_ = x;
						else
						{
							r ? tp->left = x : tp->right = x;
							x->parent = tp;
						}
					}
					node = root;
					break;
				}
			}
		}

		if (node)
		{
			node->color = rbBlack;  //最后将node[上述步骤置为了根结点]，改为黑色。  
		}
		return root;  //返回root  
	}
	NodePtr remove(const T& x, NodePtr& root)
	{
		if (root == nullptr)
			return nullptr;
		if (x < root->val)
		{
			root->left = remove(x, root->left);
			if (root->left)
				root->left->parent = root;
		}
		else if (x > root->val)
		{
			root->right = remove(x, root->right);
			if (root->right)
				root->right->parent = root;
		}
		else // x == root->val
		{
			NodePtr l = root->left;
			NodePtr r = root->right;

			if (!l && !r)
			{
				setColor(root->color);
				setDeleteNode(root->parent);
				return nullptr;
			}
			if (!l && r)
			{
				setColor(root->color);
				setDeleteNode(r);
				deleteNode(root);
				return r;
			}
			if (l && !r)
			{
				setColor(root->color);
				setDeleteNode(l);
				deleteNode(root);
				return l;
			}
			NodePtr min = findMin(r);
			root->val = min->val;
			root->right = removeMin(root->right);
			if(root->right)
				root->right->parent = root;
		}

		return root;
	}


	NodePtr find(const T& x)
	{
		return find(x, root_);
	}
	NodePtr find(const T& x, NodePtr& root) const
	{
		if (root == nullptr)
			return nullptr;
		if (x == root->val)
			return root;
		if (x < root->val)
			return find(x, root->left);
		if (x > root->val)
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
	unsigned char getHeight(NodePtr &p)
	{
		return p ? p->height : 0;
	}
	int getFactor(NodePtr &p)
	{
		return getHeight(p->right) - getHeight(p->left);
	}
	void fixHeight(NodePtr &p)
	{
		unsigned char hl = getHeight(p->left);
		unsigned char hr = getHeight(p->right);
		p->height = (hl > hr ? hl : hr) + 1;
	}
	NodePtr rotateLeft(NodePtr &p)
	{
		NodePtr q = p->right;
		p->right = q->left;
		q->left = p;
		p->parent = q;// 旋转之后记得要改变parent
		return q;
	}
	// symmetric copy of the left one
	NodePtr rotateRight(NodePtr &p)
	{
		NodePtr q = p->left;
		p->left = q->right;
		q->right = p;
		p->parent = q;// 旋转之后记得要改变parent
		return q;
	}
	NodePtr getSibling()
	{
		NodePtr ln = n->parent->left;
		NodePtr rn = n->parent->right;
		return n == ln ? rn : ln;
	}




	NodePtr removeMin(NodePtr &p)
	{
		if (!p->left)
		{
			if (!p->right)
			{
				setColor(p->color);
				setDeleteNode(p->parent);
			}
			else
			{
				setColor(p->color);
				setDeleteNode(p->right);
			}
			deleteNode(p);
			return p->right;
		}
		p->left = removeMin(p->left);
		p->left->parent = p;
		return p;
	}
	void setColor(RBColor x)
	{
		removeColor_ = x;
	}
	NodePtr newNode(const T& x)
	{
		NodePtr node(new TreeNode(x));
		node->left = nullptr;
		node->right = nullptr;
		node->parent = nullptr;
		node->height = 1;
		node->color = rbRed;
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
	void setDeleteNode(NodePtr x)
	{
		deleteNode_ = x;
	}

	static const RBColor rbRed = false;
	static const RBColor rbBlack = true;
	NodePtr root_;
	size_t size_;
	RBColor removeColor_;
	NodePtr deleteNode_;
	std::deque<std::shared_ptr<TreeNode>> nodeList_;

};



void printNode(const int& x)
{
	std::cout << x << " ";
}


int main()
{
	{
		RBTree<int> t;
		t.insert(8);t.insert(3);t.insert(10);t.insert(1);
		t.remove(1);t.remove(3);
		t.insert(6);t.insert(14);t.insert(4);t.insert(7);t.insert(13);

		assert(t.find(13)->val == 13);
		assert(t.findMax()->val == 14);
		assert(t.findMin()->val == 4);

		t.traverse(printNode);
	}

	{
		RBTree<int> t;
		t.insert(8);t.insert(3);t.insert(10);t.insert(1);
		t.insert(6);t.insert(14);t.insert(4);t.insert(7);t.insert(13);

		t.traverse(printNode);
	}

	return 0;
}