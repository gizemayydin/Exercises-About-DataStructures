#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <vector>

using namespace std;

//template <class Object>
int hashFunction (const int & key, int tableSize)
{
	return key%tableSize;
}


template <class Object>
class HashTable
{
public:

	HashTable(int size = 4096); //constructor
	bool find (const int & x);//return true if the code is is in dictionary
	bool insert(const Object & x);//insert the object x
	enum EntryType {ACTIVE, EMPTY, DELETED}; //specify the type of hash entry
	void fillASCII(); //fill the ascii characters to the hash table
	Object getElement(const int & x); //get the element with code x

private:

	struct HashEntry
	{
		/*store the element, its code and entry type*/
		Object element;
		EntryType info;
		int code;
		HashEntry(const Object & e = Object(), EntryType i = EMPTY,int code=0) : element(e), info(i),code(code) {};
		int returnCode(){return code;};
	};

	vector<HashEntry> myArray; //hash table
	int currentSize;//number of elements in the table

	int findPos(const int & x); //the position of the code x
	bool isActive (int currentPos); //return true if that cell is occupied
};


template <class Object>
HashTable<Object>::HashTable(int size = 4096) : myArray(size)
{
	//initially current size is zero
	currentSize = 0;
}

template <class Object>
void HashTable<Object> :: fillASCII()
{
	/*fill the ascii characters to the hash table*/
	for (int i = 0; i < 256; i++)
	{
		char ch = i;
		string s(1,ch);
		insert(s);
	}

}

template <class Object>
int HashTable<Object> :: findPos(const int & x)
{
	/*find the position of a code using linear probing if there is collision*/
	int counter = 0;
	int currentPos = hashFunction(x,4096);
	
	while (myArray[currentPos].info != EMPTY && myArray[currentPos].code != x && counter < 4096)
	{
		currentPos = (currentPos +1) % 4096;
		counter++;
	}	

	if (counter >= 4096)
	{
		return -1;
	}

	return currentPos;
}

template <class Object>
bool HashTable<Object> :: isActive (int currentPos)
{
	//return true if the cell is active
	return myArray[currentPos].info == ACTIVE;
}

template <class Object>
bool HashTable<Object> :: find (const int & x)
{
	/*return true if the code x exists*/
	int currentPos = findPos(x);
	if(currentPos != -1 && isActive(currentPos))
		return true;
	return false;
}

template <class Object>
Object HashTable<Object> :: getElement(const int & x)
{
	//return the element having the code x
	return myArray[findPos(x)].element;
}

template <class Object>
bool HashTable<Object> :: insert(const Object & x)
{
	//insert the object x to the dictionary
	int currentPos = findPos(currentSize);

	if (currentPos != -1)
	{
		if(!isActive(currentPos))
		{
			myArray[currentPos] = HashEntry(x,ACTIVE,currentSize);
			currentSize++;
		}
			return true;
	}

	return false;
}
#endif