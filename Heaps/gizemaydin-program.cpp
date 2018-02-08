#include <iostream>
#include "MPQ.h"
#include <fstream>

using namespace std;

enum type { startP, endP };

//the endpoints of the buildings. includes the building number, xcor, ycor and type.
class Coordinate
{
public:
	int x;
	int height;
	int buildingNumber;
	type t;
	Coordinate(int xcor = -1,int h = -1,type ty = startP, int num = -1) : x(xcor), height(h), t(ty), buildingNumber(num) {}

	void operator = (const Coordinate & rhs)
	{
		x = rhs.x;
		height = rhs.height;
		t = rhs.t;
		buildingNumber = rhs.buildingNumber;
	}
};

int ifEqual (vector<Coordinate> a, int x,int y)
{
	//if the xcor of two coordinates are equal, for the algorithm
	//*if both start point, the higher height should be first
	//*else if both end point, the lower height should be first
	//else, the start point should be first
	//since heapsort inverses the array, implement these oppositely.
	int c;

	if (a[x].t == startP && a[y].t == startP)
	{
		if (a[x].height < a[y].height)
			c = x;
		else
			c = y;
	}

	else if (a[x].t == endP && a[y].t == endP)
	{
		if (a[x].height > a[y].height)
			c = x;
		else 
			c = y;
	}

	else
	{
		if(a[x].t == endP)
			c = x;
		else
			c = y;
	}

	return c;
}

void percolateDown2(vector<Coordinate> & a, int hole, int currentSize) 
{
	//modified percolateDown function to take care of equalities.
	//maxChild is the child having the maximum value according to the algorithm standards
	//explained in ifEqual function


	int leftChild, rightChild, maxChild;
	Coordinate temp = a[hole]; //item that will be percolated down
	//int currentSize = currentSize-1;
	bool hasTwoChildren = false;


	for (;hole * 2 <= currentSize ; hole = maxChild)
	{
		hasTwoChildren = false;

		leftChild = hole * 2; 

		if(leftChild != currentSize) // there is a rightChild
		{
			hasTwoChildren = true;
			rightChild = leftChild+1;
		}

		/*find the greatest child*/
		if (hasTwoChildren && a[rightChild].x > a[leftChild].x) 
		{
			maxChild = rightChild; //child is the maximum of the children
		}

		else if (hasTwoChildren && a[rightChild].x < a[leftChild].x)
		{
			maxChild = leftChild;
		}

		else if (hasTwoChildren && a[rightChild].x == a[leftChild].x)
		{
			maxChild = ifEqual(a,rightChild, leftChild);

		}
		else if (!hasTwoChildren)
		{
			maxChild = leftChild;
		}
		

		/*if the child is greater than its parent*/
		if (a[maxChild].x > temp.x) //if child is greater than its parent 
		{
			a[hole] = a[maxChild]; //swap
		}

		else if (a[maxChild].x == temp.x)
		{
			int x = ifEqual(a,maxChild,hole);
			if (x == maxChild) //swap
			{
				a[hole] = a[maxChild];
			}
			else
				break;
		}
		
		else
			break;
	}

	a[hole] = temp; //place temp in its final pos

}

void BuildHeap(vector<Coordinate> & a) 
{
	/*builds a heap using the x value of the given coordinates*/
	int currentSize = a.size()-1;

	for(int i = currentSize/2;i>0;i--)
		percolateDown2(a,i,currentSize);
}

void HeapSort (vector<Coordinate> & a)
{
	BuildHeap(a);

	for (int i = a.size()-1; i > 0; i--)
	{
		Coordinate temp = a[1];
		a[1] = a[i];
		a[i] = temp;

		percolateDown2(a,1,i-1);
	}

}


int main()
{
	int buildingCount = 0;
	vector<Coordinate> cors;
	cors.push_back(Coordinate());
	int numBuildings;

	string filename = "input.txt";
	ifstream input;
	input.open(filename.c_str());

	input >> numBuildings;

	//store the endpoint coordinates in a vector cors.
	for (int i = 0; i < numBuildings; i++)
	{
		int xs, h, xe;
		input >> xs >> h >> xe;

		Coordinate c1(xs,h,startP,++buildingCount);
		Coordinate c2(xe,h,endP,buildingCount);
		
		cors.push_back(c1);
		cors.push_back(c2);
	}

	//heap sort this vector
	HeapSort(cors);

	//instantiate a MPQ class object with given size.
	MPQ<int> heap(2*numBuildings + 1);

	//if there are no buildings starting at 0, height at that point is 0
	if (cors[1].x != 0)
	{
		cout << "0 0" << endl;
	}

	//untill all coordinates are used
	for (int i = 1; i < cors.size(); i++)
	{
		Coordinate temp = cors[i];

		int oldMax = heap.getMax().height;

		//if it is a startP, insert it to heap, else remove it
		if (temp.t == startP)
		{
			heap.insert(temp.height, temp.buildingNumber);
		}

		else
		{
			heap.remove(temp.buildingNumber);
		}

		int newMax = heap.getMax().height;

		//if the maximum changes, output this point.
		//if endpoint, output x,currentMax
		if (oldMax != newMax)
		{
			if (temp.t == startP)
				cout << temp.x << " " << temp.height << endl;
			else
				cout << temp.x << " " << newMax << endl;
		}
	}

	cin.ignore();
	cin.get();
	return 0;
}