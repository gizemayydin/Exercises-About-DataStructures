#ifndef _LINKEDLIST_H	
#define _LINKEDLIST_H

#include <iostream>

using namespace std;

/*this class creates the rectangles and holds their coordinates*/
class rectangle
{
public:
	
	/*constructor*/
	rectangle(int topCor = -1, int leftCor = -1, int bottomCor = -1, int rightCor = -1)
		: top(topCor), left(leftCor), bottom(bottomCor), right(rightCor) {}

	/*returns true if the lhs rectangle is not equal to the rhs rectangle*/
	bool rectangle::operator != ( const rectangle & rhs )
	{	
		return (this->top != rhs.top || this->left != rhs.left || this->bottom != rhs.bottom || this->right == rhs.right);
	}

	/*assigns the rhs rectangle to the lhs rectangle*/
	rectangle rectangle::operator = ( rectangle rhs )
	{
		this->bottom = rhs.bottom;
		this->left = rhs.left;;
		this->right = rhs.right;
		this->top = rhs.top;
		return *this;
	}

	/*returns true if the given point (x,y) is intersecting with the rectangle*/
	bool rectangle::checkLimits(int x, int y)
	{
		return (left <= x && right > x && y>= top && y < bottom);
	}

	/*prints the rectangle*/
	void rectangle :: printRectangle ()
	{
		cout << top << " " << left << " " << bottom << " " << right << endl;
	}

private:
	int top,left,bottom,right;

	friend class TwoDimTree;
	friend class TwoDimTreeNode;
};


/*this class implements each node of the linked list of rectangles*/
class ListNode
{
	ListNode( const rectangle & theElement = rectangle(), ListNode * n = NULL )
      : element( theElement ), next( n ) { }  // Constructor 

	rectangle element;
    ListNode *next;

    friend class LinkedList;
    friend class ListIterator;
};


/*iterates over the linked list of rectangles*/
class ListIterator
{

public:
	ListIterator( ) : current( nullptr ) {} 
	ListIterator( ListNode *theNode ): current( theNode ) { }
    bool isPastEnd( ) const { return current == nullptr; } //returns true if current == NULL
    void advance( ) { if( !isPastEnd( ) ) current = current->next; } //moves 
    rectangle retrieve( ) const  //gets the element stored in the current position
	{ 
		return current->element; 
	}

private:

	ListNode *current;    // Current position

friend class LinkedList; 
};



/*this class implements a linked list of rectangles*/
class LinkedList
{

public:
	LinkedList(); //constructor
	LinkedList(const LinkedList & rhs); //deep copy constructor
	~LinkedList(); //destructor
	bool isEmpty(); //returns true if the list is empty
	void insert( const rectangle & x, const ListIterator & p ); //inserts an element after *p
	ListIterator zeroth(); //returns an iterator corresponding to the header
    ListIterator first();//returns an iterator corresponding to the first element
    ListIterator find( const rectangle & x ) ; //returns an iterator pointing to x
    ListIterator findPrevious( const rectangle & x ); //returns an iterator pointing to the previos node before x
    void remove( const rectangle & x ); //removes x
	void makeEmpty(); //deletes the list
	const LinkedList & operator=( LinkedList rhs ); //assigns the rhs list to the lhs list

private:
	ListNode *header;

	friend class ListIterator;
};



#endif