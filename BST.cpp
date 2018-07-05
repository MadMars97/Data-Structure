#include <iostream>
#include <string>
#include <stack>
#include <list>

using namespace std;

//binary search tree
//tree node
template <class datatype>
class TreeNode
{
public:
	TreeNode *left;
	TreeNode *right;
	datatype data_;
public:
	TreeNode(datatype x = 0, TreeNode *left = NULL, TreeNode *right = NULL)
	{
		data_ = x; this->left = left; this->right = right;
	}
	TreeNode<datatype> *getleft() { return left; }
	TreeNode<datatype> *getright() { return right; }
	datatype getdata() { return data_; }
	void setdata(datatype x) { data_ = x; }
	//void setleft(TreeNode *ptr) { left = ptr; }
	//or
	void setleft(datatype v) { left = new TreeNode<datatype>(v); }
	//void setright(TreeNode *ptr) { right = ptr; }
	//or
	void setright(datatype v) { right = new TreeNode<datatype>(v); }
	bool isleaf() { return (left == NULL && right == NULL); }
	TreeNode<datatype> *InOrderSuccessor()
	{
		TreeNode * leftmostrightsubtree = right;
		while (leftmostrightsubtree->left != NULL)
		{
			leftmostrightsubtree = leftmostrightsubtree->left;
		}
		return leftmostrightsubtree;
	}
	TreeNode<datatype> *InOrderPredecessor()
	{
		TreeNode * rightmostleftsubtree = left;
		while (rightmostleftsubtree->right != NULL)
		{
			rightmostleftsubtree = rightmostleftsubtree->right;
		}
		return rightmostleftsubtree;
	}
	//friend class BST;
};

// binary search tree
template <class datatype>
class BST :TreeNode<datatype>
{
private:
	TreeNode<datatype>* root;
public:
	//BST() { root = NULL; }
	BST(TreeNode<datatype> *rootoo = NULL)
	{
		this->root = rootoo;
	}
	// *search(datatype x);
	bool insert(datatype x)
	{
		if (root == NULL)
		{
			root = new TreeNode<datatype>(x);
			return true;
		}
		TreeNode<datatype> *temp = root;
		while (temp != NULL)
		{
			int t = temp->getdata();
			if (t == x) { return false; }
			else if (x < t)
			{
				if (temp->getleft() == NULL)
				{
					temp->setleft(x);
					return true;
				}
				else
					temp = temp->getleft();
			}
			else
			{
				if (temp->getright() == NULL)
				{
					temp->setright(x);
					return true;
				}
				else
					temp = temp->getright();
			}
		}
	}
	bool isSubTree(TreeNode *x) { return x != root&&!isleaf(); }
	void remove(datatype x) { remove(root, x); }
	void remove(TreeNode<datatype> * root_node, datatype x)
	{
		TreeNode<datatype> * TargetNode = root_node;
		TreeNode<datatype> * parent = NULL;
		bool leftchild = false;

		// make targetnode points to the wanted node to be deleted and get it's parent
		while (TargetNode != NULL)
		{
			int t = TargetNode->getdata();
			if (x == t)  break;
			else if (x < t)
			{
				parent = TargetNode;
				leftchild = true;
				TargetNode = TargetNode->getleft();
			}
			else
			{
				parent = TargetNode;
				leftchild = false;
				TargetNode = TargetNode->getright();
			}
		}

		if (TargetNode->isleaf())
		{
			if (parent == NULL)
			{
				TreeNode<datatype> * temp = root_node;
				root_node = NULL;
				delete temp;
			}
			else if (leftchild)
			{
				delete parent->getleft(); parent->left = NULL;
			}
			else
			{
				delete parent->getright(); parent->right = NULL;
			}
		}
		else if (TargetNode->getleft() == NULL&&TargetNode->getright() != NULL)
		{
			if (parent == NULL&&!isSubTree(TargetNode))
				root_node = TargetNode->getright();
			else if (leftchild)
				parent->left = TargetNode->getright();
			else
				parent->right = TargetNode->getright();
			delete TargetNode;
		}
		else if (TargetNode->getright() == NULL&&TargetNode->getleft() != NULL)
		{
			if (parent == NULL &&!isSubTree(TargetNode))
				root_node = TargetNode->getleft();
			else if (leftchild)
				parent->left = TargetNode->getleft();
			else
				parent->right = TargetNode->getleft();
			delete TargetNode;
		}
		else
		{
			TreeNode<datatype> * leftmostrightsubtree = TargetNode->InOrderSuccessor_left();
			TargetNode->data_ = leftmostrightsubtree->getdata();
			remove(TargetNode->getright(), TargetNode->getdata());
		}

	}
	bool isEmpty() { return root == NULL; }
	TreeNode<datatype> * getRoot() { return root; }
	TreeNode<datatype> * search(datatype x)
	{
		if (isEmpty()) { return NULL; }
		TreeNode *temp = root;
		while (temp != NULL)
		{
			datatype d = temp->getdata();
			if (d == x)return temp;
			else if (x < a)p = temp->getleft();
			else p = temp->getright();
		}
		return NULL;
	}
	void inOrderTraversal(TreeNode<datatype> * root)
	{
		if (root == NULL) return;
		inOrderTraversal(root->getleft());
		cout << root->getdata() << " ";
		inOrderTraversal(root->getright());
	}
	void preOrderTraversal(TreeNode<datatype> * root)
	{
		if (root == NULL) return;
		cout << root->getdata() << " ";
		preOrderTraversal(root->getleft());
		preOrderTraversal(root->getright());
	}
	void postOrderTraversal(TreeNode<datatype> * root)
	{
		if (root == NULL) return;
		postOrderTraversal(root->getleft());
		postOrderTraversal(root->getright());
		cout << root->getdata() << " ";
	}
	/*int count()
	{
	TreeNode * node = root;
	if (node->isleaf())
	return 1;
	else
	return node->getleft()->count() + node->getright()->count() + 1;
	}
	int count_right(TreeNode *t)
	{
	TreeNode * target = t->right;
	if (target->isleaf())
	return 1;
	else
	return target->getleft()->count() + target->getright()->count() + 1;
	}*/
};

class XML_treeNode
{
private:
	string tagName;
	string tagValue;
	list<XML_treeNode*> children;
public:
	XML_treeNode(string name_, string value_) :tagName(name_), tagValue(value_) {}
	void insert(XML_treeNode* node)
	{
		children.push_back(node);
	}
	string Name()
	{
		return tagName;
	}
	string Value()
	{
		return tagValue;
	}
	list<XML_treeNode*> Children()
	{
		return children;
	}
};
void convert_XML_to_text(XML_treeNode* root, int level)
{
	for (size_t i = 0; i < level; i++)
		cout << "\t";
	cout << "<" << root->Name() << ">" << root->Value();
	if (root->Children().size()>0)
		cout << endl;
	for (auto itr = root->Children().begin(); itr != root->Children().end(); itr++)
		convert_XML_to_text(*itr, level + 1);
	if (root->Children().size()>0)
		for (size_t i = 0; i < level; i++)
		{
			cout << "\t";
		}
	cout << "</" << root->Name() << ">" << endl;
}

#pragma region evaluate postfix exp
int isOperand(char ch)
{
	return (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'z');
}
int isDigit(char ch)
{
	return (ch >= '0'&&ch <= '9');
}
int prec(char ch)
{
	switch (ch)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
		/*case '(':
		return 0;
		case ')':
		return -1;*/
	}
	return -1;
}
int evaluatePostfix(string exp)
{
	stack <char> operand_stack;
	for (size_t i = 0; i < exp.size(); ++i)
	{
		if (isDigit(exp[i]))
			operand_stack.push(exp[i] - '0');
		else
		{
			int val1 = operand_stack.top();
			operand_stack.pop();
			int val2 = operand_stack.top();
			operand_stack.pop();
			switch (exp[i])
			{
			case '*': operand_stack.push(val2*val1); break;
			case '+': operand_stack.push(val2 + val1); break;
			case '-': operand_stack.push(val2 - val1); break;
				//case '^': operand_stack.push(pow(val2,val1)); break;
			case '/': operand_stack.push(val2 / val1); break;
			default:
				break;
			}
		}
	}
	return(operand_stack.top());
}
#pragma endregion

void initialize(BST<int> &test)
{
	int arr[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
	test.insert(7);
	test.insert(3);
	test.insert(5);
	test.insert(1);
	test.insert(0);
	test.insert(2);
	test.insert(4);
	test.insert(6);
	test.insert(11);
	test.insert(9);
	test.insert(8);
	test.insert(10);
	test.insert(13);
	test.insert(12);
	test.insert(14);
}
void main()
{
	BST<int> bst;
	initialize(bst);
	for (int i = 0; i < 15; i++)
	{
		bst.inOrderTraversal(bst.getRoot());
		cout << endl;
		cout << "removing" << bst.getRoot()->getdata() << endl;
		bst.remove(bst.getRoot()->getdata());
	}
	system("pause");
}
