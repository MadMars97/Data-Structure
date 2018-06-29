//#include <stack>
//#include <queue>
//#include <list>
#include <vector>
#include <fstream>
//#include "math.h"
#include <iostream>

using namespace std;
int swaps = 0;

int parent(int x)
{
	return (x + 1) / 2 - 1;// because the tree starts from 0
}
int left_child(int x)
{
	return 2 * x + 1;
}
int right_child(int x)
{
	return 2 * x + 2;
}

template<class T>
void Swap(vector<T> &arr, int index1, int index2)
{
	T tempval = arr[index1];
	arr[index1] = arr[index2];
	arr[index2] = tempval;
	swaps++;
}
template <class T>
void sift_up_MaxHeap(vector<T>&arr, int index)
{
	while (index != 0 && arr[index]>arr[parent(index)])
	{
		Swap(arr, index, parent(index)); //Swap(arr[index], arr[parent(index)]);
		index = parent(index);//when sift up and after swaping the index updated to paren's index
	}
}

//template <class T>
//void sift_down_MaxHeap(vector<T>&arr, int index, int size)
/*{
while ((left_child(index)<size && arr[index] < arr[left_child(index)])
|| (right_child(index)<size && arr[index] < arr[right_child(index)]))//there are a confusion about this condition
{
int min = index;
if (arr[min] < arr[left_child(index)])
min = left_child(index);
if (arr[min] < arr[right_child(index)] && right_child(index) < size)
min = right_child(index);
if (min == index)
break;
Swap(arr,min, index); //Swap(arr[min], arr[index]);
index = min;
}
}
*/
template <class T>
void sift_down_MaxHeap(vector<T>&arr, int index, int n)
{
	int max_index = index;
	int l = left_child(index);
	int r = right_child(index);
	if (l<n&&arr[l]>arr[max_index])
		max_index = l;
	if (r<n &&arr[r]>arr[max_index])
		max_index = r;
	if (index != max_index)
	{
		Swap(arr, index, max_index);
		sift_down_MaxHeap(arr, max_index, n);
	}
}

template <class T>
void insert(vector<T> & arr, int size, T value)
{
	if (arr.capacity() > (unsigned int size))
		arr[size] = value;
	else
		arr.push_back(value);
	size++;//after the addition because size is pointing on empty place
	sift_up(arr, size - 1)
}

template <class T>
void Extract_Max(vector<T> & arr, int size)
{
	T result = arr[0];
	arr[0] = arr[size - 1];
	size--;
	sift_down(arr, 0, size);
	return result;
}

template <class T>
void HeapSort(vector<T> & arr, int n)
{
	//int size_ = arr.size();
	int temp = 0;
	BuildHeap(arr, n);
	while (n>1)//for (int i = 0; i < n-1; i++)
	{
		Swap(arr, 0, n - 1); //Swap(arr[0], arr[size - 1]);
							 //temp=arr[n-1];
							 //result.push_back(temp);
		n--;
		sift_down_MaxHeap(arr, 0, n);
	}
}

template <class T>
void BuildHeap(vector<T> & arr, int n)
{
	for (int i = (n - 1) / 2; i >= 0; i--)
	{
		sift_down_MaxHeap(arr, i, n);
	}
}


void main()
{
	vector<int> arr;
	int value_, size_;
	//bool finish_flag = false;
	ifstream input("F:\\CSE-DolaMars\\DS\\Heap\\unsorted.txt");//input file directory 
	cin.rdbuf(input.rdbuf()); //redirect std::cin to input.txt!

	while (cin >> value_)
	{
		//cin >> value_;
		arr.push_back(value_);
	}

	ofstream output("F:\\CSE-DolaMars\\DS\\Heap\\33935_MohamedAdel.txt");//output file directory
	cout.rdbuf(output.rdbuf()); //redirect std::cout to out.txt!

	size_ = arr.size();
	HeapSort(arr, size_);
	for (int i = 0; i < arr.size(); i++)
		cout << arr[i] << endl;
	cout << swaps << endl;
}





