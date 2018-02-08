#include "TwoDimTree.h"
#include <iostream>
using namespace std;

/*detailed explanation is on the header "TwoDimTree.h"*/

TwoDimTreeNode :: TwoDimTreeNode ()
{	
	TopLeft = NULL;
	TopRight = NULL;
	BottomLeft = NULL;
	BottomRight = NULL;
	Horizontal = LinkedList();
	Vertical = LinkedList();
}



TwoDimTreeNode :: TwoDimTreeNode (rectangle extent)
{
	/*initializes the private data*/
	TopLeft = NULL;
	TopRight = NULL;
	BottomLeft = NULL;
	BottomRight = NULL;
	Horizontal = LinkedList();
	Vertical = LinkedList();
	Extent = extent;
	axisH = (extent.top + extent.bottom) / 2;
	axisV = (extent.right + extent.left) / 2;
}


TwoDimTreeNode :: ~TwoDimTreeNode()
{
	Horizontal.~LinkedList();
	Vertical.~LinkedList();

}

bool TwoDimTreeNode :: isVertical (const rectangle & rect)
{
	return (rect.left<=axisV && rect.right >=axisV);
}

bool TwoDimTreeNode :: isHorizontal (const rectangle & rect)
{
	return (rect.top <= axisH && rect.bottom >= axisH);
}

bool TwoDimTreeNode :: AddtoList (const rectangle & rect)
{
	/*inserts the rectangle to horizontal, then checks the Vertical if it cannot insert.
	Returns false if it cannot insert to both of them.*/
	
	bool isAdded = true;

	if(isHorizontal(rect))
		Horizontal.insert(rect,Horizontal.zeroth());

	else if (!isHorizontal(rect) && isVertical(rect))
		Vertical.insert(rect,Vertical.zeroth());

	else 
		isAdded = false;

	return isAdded;
}


TwoDimTree :: TwoDimTree ()
{
	root = NULL;
}



TwoDimTree :: TwoDimTree (rectangle extent)
{
	/*creates the root node with given extent*/
	root = new TwoDimTreeNode (extent);	
}

TwoDimTree :: ~TwoDimTree()
{
	/*calls makeEmpty to destruct the tree*/
	makeEmpty(root);

}

void TwoDimTree :: makeEmpty (TwoDimTreeNode * & p)
{
	/*delete the left,right,top,bottom trees recursively untill 
	they are all deleted.*/
	if( p != NULL )
    {
		makeEmpty( p->TopLeft );
		makeEmpty( p -> TopRight );
		makeEmpty (p ->BottomLeft);
		makeEmpty (p -> BottomRight);
		delete p;
	}

	p = NULL;

}


bool TwoDimTree :: AddtoTree (const rectangle & rect, TwoDimTreeNode *p)
{
	/*
	-try adding the rectangle rect to the node *p, if cannot, try to add rect to
	the right child of p by calling the same function recursively for that child.
	-If that child does not exist, create it.
	-Do not create a new node if the area of the node is smaller than 1.
	-returns false if the rectangle cannot be inserted.
	*/
	if(p->AddtoList(rect))
		return true;

	else 
	{
		int top = p->Extent.top,bottom = p->Extent.bottom ,right = p->Extent.right ,left = p->Extent.left;
		int length = (bottom - top);
		int width = (right - left);

		if (rect.bottom < p->axisH && rect.right < p->axisV)
		{	
			if(p->TopLeft == NULL && length> 1 && width > 1)
				p->TopLeft = new TwoDimTreeNode(rectangle(p->Extent.top,p->Extent.left,(p->Extent.bottom + p->Extent.top)/2,(p->Extent.right + p->Extent.left)/2));
			AddtoTree (rect,p->TopLeft);
		}
		else if (rect.bottom < p->axisH && rect.left > p->axisV)
		{	
			if(p->TopRight == NULL  && length> 1 && width > 1)
				p->TopRight = new TwoDimTreeNode(rectangle(p->Extent.top,(p->Extent.left + p->Extent.right)/2,(p->Extent.bottom + p->Extent.top)/2,p->Extent.right));
			AddtoTree(rect,p->TopRight);
		}	
		else if(rect.top > p->axisH && rect.right < p-> axisV)
		{	
			if(p->BottomLeft == NULL  && width> 1 && length > 1)
				p->BottomLeft = new TwoDimTreeNode(rectangle((p->Extent.top + p->Extent.bottom)/2,p->Extent.left,p->Extent.bottom,(p->Extent.right + p->Extent.left)/2));
			AddtoTree(rect,p->BottomLeft);
		}
		else if (rect.top > p->axisH && rect.left > p->axisV)
		{	
			if(p->BottomRight == NULL  && length > 1 && width > 1)
				p->BottomRight = new TwoDimTreeNode(rectangle((p->Extent.top + p->Extent.bottom)/2,(p->Extent.left + p->Extent.right)/2,p->Extent.bottom,p->Extent.right));
			AddtoTree(rect,p->BottomRight);
		}
		else
			return false;
	}

}

void TwoDimTree :: AddtoTreePublic (const rectangle & rect)
{
	/*call AddtoTree*/
	if (!AddtoTree(rect,root))
		throw ("cannot add to tree");
}

bool TwoDimTree :: FindPublic (int x,int y, vector<rectangle> &v)
{
	/*call Find*/
	return Find(root,x,y,v);
}

bool TwoDimTree :: Find(TwoDimTreeNode* p,int x,int y, vector<rectangle> &v)
{
	/*
	-store the rectangles in v if there are any rectangles intersecting with (x,y) in node 
	*p by calling isMatching.
	-after that, call Find for the appropriate child recursively untill there are no childs the check.
	-call isMatching for that children too.
	- return false if there are no intersecting rectangles.
	*/
	
	p->isMatching (x,y,v);

	if (x < p->axisV && y < p->axisH  && p->TopLeft != NULL)
	{
		Find(p->TopLeft,x,y,v);
	}
	
	else if (x > p->axisV && y < p->axisH && p->TopRight != NULL)
	{
		Find(p->TopRight,x,y,v);
	}
	
	else if (x < p->axisV && y > p->axisH && p->BottomLeft != NULL)
	{
		Find(p->BottomLeft,x,y,v);
	}

	else if (x > p->axisV && y > p->axisH && p->BottomRight != NULL)
	{
		Find(p->BottomRight,x,y,v);
	}

	else
		return (v.size()>0);
}


void TwoDimTreeNode ::isMatching(int x , int y, vector<rectangle> &v)
{
	/*
	-For the given node, check if there are any rectangles in Vertical and Horizontal that 
	intersect with (x,y)
	-store them in vector v,
	*/
	
	ListIterator itrH = Horizontal.zeroth();
	ListIterator itrV = Vertical.zeroth();

	while(!itrH.isPastEnd())
	{
		rectangle r;
		if(!itrH.isPastEnd())
			r = itrH.retrieve();
		
		if (r.checkLimits(x,y))
		{
			v.push_back(r);
		}

		itrH.advance();
	}

	while(!itrV.isPastEnd())
	{
		rectangle r = itrV.retrieve();
		if (r.checkLimits(x,y))
		{
			v.push_back(r);
		}

		itrV.advance();
	}
}

