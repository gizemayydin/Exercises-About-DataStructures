#include "LinkedList.h"
#include "TwoDimTree.h"
#include <fstream>
#include <string>

using namespace std;

/*keeps the input coordinate*/
struct coordinate 
{
	coordinate(int x = -1, int y = -1) : x(x),y(y) {}
	int x,y;
};

int main()
{
	/*open rectdb.txt*/
	string line,filename = "rectdb.txt";
	ifstream input;
	input.open(filename.c_str());
	
	/*read the extent and print it*/
	int rtop,rleft,rbottom,rright;
	input >> rtop>> rleft>> rbottom >> rright ;
	rectangle extent(rtop,rleft,rbottom,rright);
	extent.printRectangle();
	
	/*create the tree*/
	TwoDimTree tree (extent);
	
	/*keep getting the rectangles, printing them and inserting to the tree untill there are 
	no rectangles which is indicated by -1*/
	bool thereisRectangle = true;
	while (thereisRectangle)
	{
		input >> rtop;

		if (rtop < 0)
		{
			thereisRectangle = false;
			cout << "-1" << endl << endl;
		}

		else
		{
			input >> rleft >> rbottom >> rright ;
			rectangle r (rtop,rleft,rbottom,rright);
			r.printRectangle();
			tree.AddtoTreePublic(r);
		}
	}


	/*read the coordinates that will be checked untill a coordinate having x = -1 is 
	entered, and store them in the vector "coordinates"*/
	bool thereisPoint = true;
	vector <coordinate> coordinates;
	while (thereisPoint)
	{
		int a,b;
		cin >> a; 
		
		if (a == -1)
			thereisPoint = false;
		else
		{
			cin >> b;
			coordinates.push_back(coordinate(a,b));
		}
	}
	

	/*for each coordinate in the vector "coordinates", store the intersecting
	rectangles and print them.*/
	for (int i = 0; i < coordinates.size(); i++)
	{
		int x = coordinates[i].x;
		int y = coordinates[i].y;
		cout << x << " " << y << endl;
		vector<rectangle> results;

		if(tree.FindPublic(x,y,results))
		{
			cout << results.size() << endl;

			for (int j = 0; j < results.size(); j++)
			{
				results[j].printRectangle();
			}
		}

		else 
			cout << "0" << endl;
	}

	
	cin.ignore();
	cin.get();
	return 0;

}