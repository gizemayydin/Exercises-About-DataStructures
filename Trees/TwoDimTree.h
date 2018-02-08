#ifndef _TWODIMTREE_H
#define _TWODIMTREE_H


#include "LinkedList.h"
#include <vector>

/*
-implements the nodes of the tree.
-vertical and horizontal store the rectangles that intersects with the vertical
and horizontal axis of the node
-extent is the rectangle that the node covers
-axisV = vertical axis
-axisH = horizontal axis
*/
class TwoDimTreeNode
{
public:
	//default constructor
	TwoDimTreeNode(); 

	//constructor that takes the extent as a parameter
	TwoDimTreeNode(rectangle extent); 

	~TwoDimTreeNode();
	
	 //returns true if rectangle rect intersects with the vertical axis of that node
	bool isVertical(const rectangle & rect);

	//returns true if rectangle rect intersects with the horizontal axis of that node
	bool isHorizontal(const rectangle & rect); 

	//returns true if the rectangle is added to one of the lists
	bool AddtoList (const rectangle & rect); 

	//if the point (x,y) is intersecting with any of the rectangles stored in Vertical or Horizontal,
	//adds these rectangles to vector v
	void isMatching(int x, int y, vector<rectangle> &v); 


private:
	rectangle Extent;
	LinkedList Vertical, Horizontal;
	TwoDimTreeNode *TopLeft, *TopRight,*BottomLeft, *BottomRight;
	int axisV,axisH;

	friend class TwoDimTree;
	friend class rectangle;
};


/*implements the tree consisting of TwoDimTreeNodes*/
class TwoDimTree
{
public:

	/*constructor*/
	TwoDimTree();

	/*destructor*/
	~TwoDimTree();

	/*constructor that takes the extent of the tree as a parameter*/
	TwoDimTree(rectangle extent);

	/*adds the rectangle rect to the tree having root p*/
	bool AddtoTree (const rectangle & rect, TwoDimTreeNode *p);

	/*is called by the user to add a rectangle rect,it calls AddtoTree*/
	void AddtoTreePublic (const rectangle & rect);

	/*Finds the rectangles that intersect with (x,y) from the tree having 
	root p,	stores them in v*/
	bool Find(TwoDimTreeNode *p,int x,int y, vector <rectangle> &v);

	/*is called by user, calls Find*/
	bool FindPublic (int x,int y, vector<rectangle> &v);

	/*deletes the tree having root p*/
	void makeEmpty(TwoDimTreeNode * & p);

private:
	TwoDimTreeNode *root;
};




#endif