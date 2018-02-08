#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{

	HashTable<string> dictionary = HashTable<string>();
	dictionary.fillASCII(); //fill ascii to the dictionary

	char ch;

	ifstream input("compin");
	ofstream output("compout");

	string p,c;

	input.get(ch);
	p = ch;

	while (!input.eof())
	{
		input.get(ch);

		if (input.eof())
			break;

		c = ch;

		/*is p+c added to the dictionary? if so, it is the longest prefix.*/
		if (dictionary.find(p+c))
		{
			p = p+c;
		}

		/*if not, output the code of longest prefix and add p+c to the dictionary.
	    longest prefix is now c.*/
		else
		{
			output << dictionary.getCode(p) << " " ;
			dictionary.insert(p+c);
			p = c;
		}

	}

	output << dictionary.getCode(p) << " ";

	input.close();
	output.close();
	return 0;
}
