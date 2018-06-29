#include <stack>
#include <queue>
#include <list>
#include <vector>
//#include <fstream>
//#include "math.h"
#include <string>
#include <iostream>
using namespace std;

template <class T>
class Node
{
private:
	T value_;
	Node<T> *next_;
	Node<T> *previous_;
public:
	Node<T>(T val)
	{
		value_ = val;
		next_ = NULL;
		previous_ = NULL;
	}
	Node<T>(T val, Node<T> * n)
	{
		value_ = val;
		next_ = n;
	}
	Node<T>(Node<T> *m, T val, Node<T> * n)
	{
		value_ = val;
		next_ = n;
		previous_ = m;
	}
	T getData()
	{
		return value_;
	}
	void setData(T val)
	{
		value_ = val;
	}
	Node<T> *getNext()
	{
		return next_;
	}
	Node<T> *getPrev()
	{
		return previous_;
	}
	void setNext(Node<T> *n)
	{
		next_ = n;
	}
	void setPre(Node<T> *n)
	{
		previous_ = n;
	}
	void printNode()
	{
		if (previous_ == NULL)
			cout << "NULL";
		else
			cout << previous_->getData();
		cout << "<-- " << value_ << " -->";
		if (next_ == NULL)
			cout << "NULL";
		else
			cout << next_->getData();
		cout << endl;
	}
};

template <class T>
class Linked_List
{
private:
	Node<T> *head; //root
	Node<T> *tail;
	int size_;
public:
	Linked_List<T>()
	{
		head = NULL;
		tail = NULL;
		size_ = 0;
	}
	~Linked_List<T>()
	{
		if (head != NULL)
		{
			Node<T>* temp1 = head;
			while (temp1->getNext() != NULL)
			{
				Node<T>* temp2 = temp1->getNext();
				delete temp1;
				temp1 = temp2;
			}
			head = NULL;
			tail = NULL;
			size_ = 0;
		}
	}
	void push_back(T val)
	{
		if (head == NULL)
		{
			head = new Node<T>(val, NULL);
			tail = head;
		}
		else
		{
			Node<T> *ptrpre = head;
			Node<T> * traversing_ptr = head;
			Node<T> *n = new Node<T>(val);
			while (traversing_ptr->getNext() != NULL)
			{
				traversing_ptr = traversing_ptr->getNext();
				traversing_ptr->setPre(ptrpre);
				ptrpre = ptrpre->getNext();
			}
			n->setPre(traversing_ptr);
			traversing_ptr->setNext(n);
			tail = n;
		}
		size_++;
	}
	void push_front(T val)
	{
		Node<T> *temp = new Node<T>(val, head);
		if (head != NULL)
		{
			head->setPre(temp);
			head = temp;
			size_++;
		}
		else
		{
			head = temp;
			tail = temp;
			size_++;
		}
	}
	void insert(int index, T val)
	{
		// index to be inserted in , inserted value
		if (size_ == 0 || index > size_ || index == 0)
			return;
		else if (index == 1)
			push_front(val);
		else if (index == size_)
			push_back(val);
		Node<T> *new_node = new Node<T>(val);
		if (index >= (size_ / 2))
		{
			Node<T>* traversing_ptr = tail;
			for (int k = size_; k > index + 1; k--)
				traversing_ptr = traversing_ptr->getPrev();
			Node<T> *temp = traversing_ptr->getPrev();
			temp->setNext(new_node);
			traversing_ptr->setPre(new_node);
			new_node->setNext(traversing_ptr);
			new_node->setPre(temp);
		}
		else
		{
			Node<T>* traversing_ptr = head;
			for (int k = 1; k < index; k++)
				traversing_ptr = traversing_ptr->getNext();
			Node<T>* temp = traversing_ptr->getNext();
			temp->setPre(new_node);
			traversing_ptr->setNext(new_node);
			new_node->setNext(temp);
			new_node->setPre(traversing_ptr);
		}
		size_++;
	}

	void remove_front()
	{
		if (head != NULL)
		{
			Node<T> * temp = head;
			if (size_ > 1)(head->getNext())->setPre(NULL);
			head = head->getNext();
			if (size_ == 1)tail = tail->getNext();
			delete temp;
			size_--;
		}
	}
	void remove_back()
	{
		if (size_ > 1 && tail != NULL)
		{
			Node<T> * temp = tail;
			(tail->getPrev())->setNext(NULL);
			tail = tail->getPrev();
			delete temp;
			size_--;
		}
		else if (size_ == 1)
		{
			Node<T> * temp = head;
			head = head->getPrev();
			tail = tail->getNext();
			delete temp;
			/*delete head;
			head = NULL; tail = NULL;*/
			size_--;
		}
	}
	void remove_index(int index)
	{
		if (size_ == 0 || index > size_ || index == 0)
			return;
		else if (index == 1)
			remove_front();
		else if (index == size_)
			remove_back();
		//Node<T> *new_node = new Node<T>(val);
		if (index >= (size_ / 2))
		{
			Node<T>* traversing_ptr = tail;
			for (int k = size_; k > index + 1; k--)
				traversing_ptr = traversing_ptr->getPrev();
			Node<T> *temp = traversing_ptr;
			(temp->getNext())->setPre(temp->getPrev());
			(temp->getPrev())->setNext(temp->getNext());
			delete temp;
		}
		else
		{
			Node<T>* traversing_ptr = head;
			for (int k = 1; k < index; k++)
				traversing_ptr = traversing_ptr->getNext();
			Node<T>* temp = traversing_ptr->getNext();
			(temp->getNext())->setPre(temp->getPrev());
			(temp->getPrev())->setNext(temp->getNext());
			delete temp;
		}
		size_--;
	}
	void remove(int val)
	{
		if (head != NULL && head->getData() == val)
			remove_front();
		else if (tail != NULL && tail->getData() == val)
			remove_back();
		else if (head != NULL)
		{
			Node<T> *traversal_ptr = head;
			while (traversal_ptr->getNext() != NULL
				&& (traversal_ptr->getNext())->getData() != val)
			{
				traversal_ptr = traversal_ptr->getNext();
			}
			if (traversal_ptr == NULL || traversal_ptr->getNext() == NULL)
			{
				cout << "Not Found !" << endl;
				return;
			}
			else if (traversal_ptr->getNext()->getData() == val)
			{
				Node<T> *temp = traversal_ptr->getNext();
				(temp->getNext())->setPre(temp->getPrev());
				(temp->getPrev())->setNext(temp->getNext());
				delete temp;
			}
			size_--;
		}
	}

	Node<T> *getHead()
	{
		return head;
	}
	Node<T> *getTail()
	{
		return tail;
	}
	T getFront()
	{
		if (head != NULL)
			return head->getData();
	}
	T getBack()
	{
		if (tail != NULL)
			return tail->getData();
	}

	Node<T> *contains(T val)
	{
		if (head != NULL)
		{
			Node<T>* traversal_ptr == head();
			while (traversal_ptr != NULL && traversal_ptr->getData() != val)
			{
				traversal_ptr = traversal_ptr->getNext();
			}
			if (traversal_ptr == NULL)
				return NULL;
			else
				return traversal_ptr;
		}
		return NULL;
	}

	void printList()
	{
		Node<T> *temp = head;
		if (temp == NULL)cout << "empty!";
		while (temp != NULL)
		{
			cout << temp->getData();
			if (temp->getNext() != NULL)
				cout << "-->";
			temp = temp->getNext();
		}
		cout << endl;
	}
	void print_list_detailed()
	{
		Node<T> *temp = head;
		while (temp != NULL)
		{
			temp->printNode();
			temp = temp->getNext();
		}
	}
	int getSize()
	{
		return size_;
	}

	void free()
	{
		while (head != NULL)
		{
			remove_front();
		}
		head = NULL; tail = NULL; size_ = 0;
	}
	void free_recursively(Node<T>* temp)
	{
		while (temp != NULL)
		{
			free_recursively(temp->getNext());
			delete temp;
			size_--;
		}
		head = NULL; tail = NULL; size_ = 0;
	}
};

template<class T>
class stack_list
{
private:
	Linked_List<T> data_;
public:
	void push(T val)
	{
		data_.push_back(val);
	}
	void pop()
	{
		data_.remove_back();
	}
	T top()
	{
		data_.getBack();
	}
	bool empty()
	{
		return data_.getSize() == 0;
	}
	int size()
	{
		return data_.getSize();
	}
	void free()
	{
		data_.~Linked_List();
	}
};

template <class T>
class queue_list
{
private:
	Linked_List<T> data_;
public:
	void enqueue(T val)
	{
		data_.push_back(val);
	}
	void dequeue()
	{
		data_.remove_front();
	}
	int top()
	{
		return data_.getFront();
	}
	bool empty()
	{
		return data_.getSize() == 0;
	}
	int size()
	{
		return data_.getSize();
	}
	void free()
	{
		data_.~Linked_List();
	}
};

#pragma region sort for list by the root (selection and bubble)
template<class T>
void List_selection_sort(Node<T>* head)
{
	if (head == NULL)return;
	Node<T>* temp1 = head;
	while (temp1 != NULL)
	{
		Node<T>* temp2 = temp1->getNext();
		Node<T>* min = temp1;
		while (temp2 != NULL)
		{
			if (temp2->getData() < min->getData())
				min = temp2;
			temp2 = temp2->getNext();
		}
		int t = temp1->getData();
		temp1->setData(min->getData());
		min->setData(t);

		temp1 = temp1->getNext();
	}
}

template<class T>
void List_bubble_sort(Node<T>* head)
{
	if (head == NULL)return;
	Node<T>* endNode = head;
	bool swapped = false;
	do
	{
		swapped = false;
		Node<T>* temp = head;
		while (temp->getNext() != endNode&&temp->getNext() != NULL)
		{
			if (temp->getData() > (temp->getNext())->getData())
			{
				int t = temp->getData();
				temp->setData((temp->getNext())->getData());
				(temp->getNext())->setData(t);
				swapped = true;
			}
			temp = temp->getNext();
		}
		endNode = temp;
	} while (swapped);
}
#pragma endregion

#pragma region binary search
template<class T>
int Binary_serch(vector<T>&arr, int begin_, int end_, int val)
{
	if (begin_ > end_)
		return -1;
	if (begin_ == end_)
	{
		if (x[begin_] == val) return begin;
		else return -1;
	}
	int mid = begin_ + (end_ - begin_) / 2;
	if (arr[mid] == val)
		return mid;
	else if (arr[mid] > val)
		return Binary_serch(arr, begin_, mid - 1, val);
	else
		return Binary_serch(arr, mid + 1, end_, val);
}
#pragma endregion

//void LargestMultipleOfThree(vector<int> data_)
/*{
	queue_list<int> zero_r, one_r, two_r;
	int total_sum = 0;
	bool possible = true;
	sort(data_.begin(), data_.end());
	for (size_t i = 0; i < data_.size(); i++)
	{
		int number = data_[i];
		if (number % 3 == 0)
		{
			zero_r.enqueue(number);
			total_sum += number;
		}
		else if (number % 3 == 1)
		{
			one_r.enqueue(number);
			total_sum += number;
		}
		else if (number % 3 == 2)
		{
			two_r.enqueue(number);
			total_sum += number;
		}
	}
	if (total_sum % 3 == 1)
	{
		if (one_r.size() >= 1)
			one_r.dequeue();
		else if (two_r.size() >= 2)
		{
			two_r.dequeue();
			two_r.dequeue();
		}
		else
			possible = false;
	}
	else if (total_sum % 3 == 2)
	{
		if (two_r.size() >= 1)
			two_r.dequeue();
		else if (one_r.size() >= 2)
		{
			one_r.dequeue();
			one_r.dequeue();
		}
		else
			possible = false;
	}

	if (possible)
	{
		list<int> temp;
		queue_list<int> x[] = { zero_r,one_r,two_r };
		for (size_t i = 0; i < 3; i++)
		{
			while (!x[i].empty())
			{
				temp.push_back(x[i].top());
				x[i].dequeue();
			}
		}
		vector<int> result(temp.begin(), temp.end());
		sort(result.begin(), result.end());
		int number = 0;
		for (size_t i = 0; i < result.size(); i++)
		{
			if (i != 0)
				number *= 10;
			number += result[result.size() - i - 1];
		}
		cout << number << endl;
		for (size_t i = 0; i < 3; i++)
		{
			x[i].free();
		}
	}
	else
	{
		cout << "Not possible!" << endl;
	}
	zero_r.free(); one_r.free(); two_r.free();
}*/

#pragma region infix to postfix
int isOperand(char ch)
{
	return (ch>='0' && ch<='9') || (ch>='A' && ch<='z');
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
string infixToPostfix(string exp)
{
	stack<char> opstack;
	int i;
	string result;
	for (i = 0; i < exp.size(); i++)
	{
		if (isOperand(exp[i]))
			result.push_back(exp[i]);
		else if (exp[i] == '(')
			opstack.push(exp[i]);
		else if (exp[i] == ')')
		{
			while (!opstack.empty() &&opstack.top()!='(')
			{
				result.push_back(opstack.top());
				opstack.pop();
			}
			opstack.pop();
		}
		else //operator
		{
			while (!opstack.empty() && prec(exp[i]) <= prec(opstack.top()))
			{
				result.push_back(opstack.top());
				opstack.pop();
			}
			opstack.push(exp[i]);
		}
	}

	// pop all operators from stack;
	while (!opstack.empty())
	{
		result.push_back(opstack.top());
		opstack.pop();
	}
	return result;
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
			case '+': operand_stack.push(val2+val1); break;
			case '-': operand_stack.push(val2-val1); break;
			//case '^': operand_stack.push(pow(val2,val1)); break;
			case '/': operand_stack.push(val2/val1); break;
			default:
				break;
			}
		}
	}
	return(operand_stack.top());
}
void test_infixtopostfix()
{
	string exp = "(1+2)*(3+2)/2";
	string exp2= infixToPostfix(exp);
	cout <<exp2 << endl;
	cout << evaluatePostfix(exp2) << endl;
}
#pragma endregion

#pragma region merge sort
template <class T>
void merge(vector<T> arr, int l, int m, int r)
{
	// array , level , medium ,right
	//O(n)
	int i, j, k;//i for left arr , j for right arr ,k for the origin arr
	int n1 = m - l + 1; //length of arr1
	int n2 = r - m;//length of arr2
	vector<T> L(n1), R(n2);
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];//fill arr 1 from the origin array from l -> l+n1
	for (j = 0; j < n2; j++)
		R[j] = arr[r + j];//fill arr 2 from the origin array from l -> r+n2
	i = 0; j = 0; k = l;
	while (i < n1 && j < n2)//compare and edit the origin array in area with sorted 2arrays
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	//copy the remaining elements of left,if there are any
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	//copy the remaining elements of right,if there are any
	while (i < n1)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
template <class T>
void merge_sort(vector<T> arr, int l, int r)
{
	if (l == r)
	{
		return;
	}
	else if (l < r)
	{
		int m = l + (r - l) / 2;
		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}
#pragma endregion 

void test_LinkedList()
{
	Linked_List<int> kamar;
	kamar.push_back(10);
	kamar.push_back(9);
	kamar.push_back(8);
	kamar.push_back(7);
	kamar.push_back(6);
	kamar.push_front(5);
	kamar.push_front(4);
	kamar.push_front(3);
	kamar.push_front(2);
	kamar.push_front(1);
	//kamar.print_list_detailed();
	kamar.printList();
	kamar.insert(3, 15);
	//kamar.print_list_detailed();
	kamar.printList();
	kamar.insert(8, 15);
	//kamar.print_list_detailed();
	kamar.printList();
	kamar.remove_back();
	kamar.printList();
	kamar.remove_front();
	kamar.printList();
	kamar.remove_index(5);
	kamar.printList();
	kamar.remove(10);
	kamar.printList();
	kamar.remove(20);
	kamar.printList();
	kamar.remove(5);
	kamar.printList();
	kamar.remove(2);
	kamar.printList();
	kamar.remove(7);
	kamar.printList();
	kamar.print_list_detailed();
	//kamar.~Linked_List();
	List_bubble_sort(kamar.getHead());
	kamar.printList();
	cout << kamar.getSize();
}

#pragma region merge sort
template <class T>
void merge(vector<T> arr,int l ,int m , int r)
{
	// array , level , medium ,right
	//O(n)
	int i, j, k;//i for left arr , j for right arr ,k for the origin arr
	int n1 = m - l + 1; //length of arr1
	int n2 = r - m;//length of arr2
	vector<T> L(n1), R(n2);
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];//fill arr 1 from the origin array from l -> l+n1
	for (j = 0; j < n2; j++)
		R[j] = arr[r + j];//fill arr 2 from the origin array from l -> r+n2
	i = 0; j = 0; k = l; 
	while (i < n1 && j < n2)//compare and edit the origin array in area with sorted 2arrays
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	//copy the remaining elements of left,if there are any
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}
	//copy the remaining elements of right,if there are any
	while (i < n1)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}
template <class T>
void merge_sort(vector<T> arr, int l, int r)
{
	if (l == r)
	{
		return;
	}
	else if (l < r)
	{
		int m = l + (r - l) / 2;
		merge_sort(arr, l, m);
		merge_sort(arr, m + 1, r);
		merge(arr, l, m, r);
	}
}
#pragma endregion 

int main()
{
	//test_LinkedList();
	//test_Question_i();
	//test_infixtopostfix();
	return 0;
}


