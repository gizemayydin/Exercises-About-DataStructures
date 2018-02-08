#include <iostream>
#include <fstream>
#include <string>
#include "HashTable.h"

using namespace std;

int main()
{
	ifstream input("compout");
	ofstream output("decompout");
	
	HashTable<string> dictionary;
	dictionary.fillASCII(); //fill the ascii characters to the dictionary

	int q,x;
	input >> x;

	output << dictionary.getElement(x); //output the first element
	
	q = x; //now, previous is equal to the first element

	while (input >> x)
	{
		/*is the code x in the dictionary?*/

		if (dictionary.find(x))
		{
			/*if it is, output its text and insert text(q)fc(x) to dict*/
			output << dictionary.getElement(x);
			dictionary.insert(dictionary.getElement(q) + dictionary.getElement(x).substr(0,1));
		}

		else
		{
			/*if it is not, output text(q)fc(q) and insert it to dict*/
			string s = dictionary.getElement(q) + dictionary.getElement(q).substr(0,1); 
			output << s;
			dictionary.insert(s);
		}

		q = x;//now previous is x
	}


	input.close();
	output.close();
	return 0;
}