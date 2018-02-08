#ifndef _MPQ_H
#define _MPQ_H

#include <vector>

using namespace std;

/*nodes in the heap hold a label and an associated height*/

template <class Object>
struct Node
{
	Object height;
	int label;
	Node (Object h = -1, int l = -1) : height(h), label(l) {}
};

template <class Object>
class MPQ
{
public:
	MPQ(int capacity = 0);
	~MPQ();
	void insert(Object height, int label);
	Node<Object> remove(int label);
	Node<Object> getMax();
	bool isEmpty();

private:

	int currentSize;
	vector<Node<Object>> heap;
	vector<int> location;
	void percolateDown(int hole);
};

template <class Object>
MPQ<Object> :: MPQ (int capacity) : heap(capacity), location(capacity)
{
	//initialize each vector component to -1 to indicate empty
	//insert 0,0 as initialization
	currentSize = 1;
	heap[1].height = 0;
	heap[1].label = 0;
	location[0] = 1;

	for (int i = 0; i < location.size(); i++)
	{
		location[i] = -1;
	}
}

template <class Object>
MPQ<Object> :: ~MPQ()
{
	//make the vectors logically empty
	currentSize = 0;

	for (int i = 0; i < heap.size(); i++)
	{
		heap[i].height = -1;
		heap[i].label = -1;
	}

	for (int i = 0; i < location.size(); i++)
	{
		location[i] = -1;
	}
}

template <class Object>
void MPQ<Object> :: percolateDown(int hole) 
{
	int child;
	Node<Object> temp = heap[hole]; //item that will be percolated down

	/*this loop iterates as long as hole has a child. 
	after each iteration, hole is equal to the child.*/
	for (;hole * 2 <= currentSize ; hole = child)
	{
		child = hole * 2; //2i

		if (child != currentSize && heap[child+1].height > heap[child].height) //if there is another child
		{
			child++; //child is the maximum of the children
		}

		if (heap[child].height > temp.height) //if child is greater than its parent 
		{
			//swap and update location accordingly
			int x = heap[hole].label;
			int y = heap[child].label;
			location[x] = -1;
			location[y] = hole;
			heap[hole] = heap[child];
		}

		else
			break;
	}

	heap[hole] = temp; //place temp in its final pos
	location[temp.label] = hole;

}

template <class Object>
void MPQ<Object> :: insert(Object height, int label)
{
	int hole = ++currentSize;

	//swap until you find the right pos, update location accordingly
	for (;hole > 1 && height > heap[hole/2].height ; hole /= 2)
	{
		int swappedLabel = heap[hole/2].label;//the label of the swapped
		location[swappedLabel] = hole;
		heap[hole] = heap[hole/2];
	}
	
	heap[hole] = Node<Object>(height,label);
	location[label] = hole;
}

template <class Object>
Node<Object> MPQ<Object> :: getMax()
{
	//return the maximum elt of the heap
	return heap[1];
}

template <class Object>
bool MPQ<Object> :: isEmpty()
{
	//return true if the heap is empty
	return (currentSize==0);
}

template <class Object>
Node<Object> MPQ<Object> :: remove (int label)
{
	//remove the height component with given label

	int pos = location[label]; //the elt to be removed is in pos pos in the heap
	Node<Object> tobereturned = heap[pos];

	if (pos == currentSize)//just delete the elt if it is the last one
	{
		heap[pos].height = -1;
		heap[pos].label = -1;
		location[label] = -1;
		currentSize--;
	}

	else
	{
		//isnert the last element to the removed position and percolate down
		heap[pos] = heap[currentSize];
		int labelOfLast = heap[currentSize].label;
		location[labelOfLast] = pos;
		location[label] = -1;
		currentSize--;
		percolateDown(pos);
	}

	return tobereturned;
}
#endif