#include "LinkedList.h"

using namespace std;

/*explanations about the functions are on the header "LinkedList.h"*/

LinkedList:: LinkedList()
{
	header = new ListNode();
	header->next = NULL;
}

LinkedList :: ~LinkedList()
{

	ListIterator itr = zeroth();
	while (itr.isPastEnd())
	{
		ListIterator temp = itr;
		delete itr.current;
		itr = temp;
	}

}

bool LinkedList::isEmpty()
{
	bool isEmpty = false;
	if (header == NULL)
	{
		isEmpty = true;
	}
	else if (header != NULL)
	{
		if(header->next == NULL)
			isEmpty = true;
	}

	return isEmpty;
}


void LinkedList::insert(const rectangle & x, const ListIterator & p)
{
	if(p.current != nullptr)
		p.current->next = new ListNode (x,p.current->next);
}

ListIterator LinkedList :: find (const rectangle & x )
{
	ListNode *itr = header->next;

	while (itr != nullptr && itr->element != x)
		itr = itr -> next;

	return ListIterator(itr);
}

ListIterator LinkedList:: findPrevious (const rectangle & x)
{
	ListNode *itr = header;

    while( itr->next != nullptr && itr->next->element != x )
		itr = itr->next;

    return ListIterator( itr );

}

void LinkedList:: remove (const rectangle & x)
{
	ListIterator p = findPrevious( x );

	if( p.current->next != nullptr )
	{
		ListNode *oldNode = p.current->next;
		p.current->next = p.current->next->next;
		delete oldNode;
	}
}

ListIterator LinkedList :: zeroth()
{
	return ListIterator(header);
}

ListIterator LinkedList :: first()
{
	return ListIterator (header->next);
}

void LinkedList :: makeEmpty()
{
	while(!isEmpty())
		remove(first().retrieve());
}

const LinkedList &  LinkedList::operator=(LinkedList rhs )
{
	if( this != &rhs )
	{
		makeEmpty( );
		ListIterator ritr = rhs.first();
        ListIterator itr = zeroth( );
		for( ; !ritr.isPastEnd( ); ritr.advance( ), itr.advance( ) )
			insert( ritr.retrieve( ), itr );
	}
    
	return *this;
}

LinkedList::LinkedList( const LinkedList & rhs )
{
    header = new ListNode;
    *this = rhs; 
}

