#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <vector>

using namespace std;

template <class Object>
int hashFunction (const Object & key, int tableSize)
{
	/*hashes the given key and returns the hash value*/

	int hashVal = 0;

	for (int i = 0; i < key.length(); i++)
	{
		hashVal = 37*hashVal + key[i];
	}

	hashVal = hashVal%tableSize;

	if(hashVal < 0)
		hashVal += tableSize;

	return hashVal;
}


template <class Object>
class HashTable
{
public:

	HashTable(int size = 4096); //constructor
	bool find (const Object & x); //returns true if x is in the hash table
	bool insert(const Object & x); //returns true if it can insert c to the hash table
	enum EntryType {ACTIVE, EMPTY, DELETED}; //specifies whether the entry is active, empty, deleted
	void fillASCII(); //fills the ASCII characters to the hash table
	int getCode(const Object & x); //returns the code field of a hash entry with given element

private:

	struct HashEntry
	{
		/*stores the element, its code and whether it is active or not*/
		Object element;
		EntryType info;
		int code;
		HashEntry(const Object & e = Object(), EntryType i = EMPTY,int code=0) : element(e), info(i),code(code) {};
		int returnCode(){return code;};
	};

	vector<HashEntry> myArray; //the hash table
	int currentSize; //stores the number of elts in the table

	int findPos(const Object & x); //finds the position of a given element with linear probing
	bool isActive (int currentPos); //returns true if the cell is active
	int findPos_insert(const Object & x); //used in insert function, similar to findPos
};


template <class Object>
HashTable<Object>::HashTable(int size = 4096) : myArray(size)
{
	currentSize = 0; //current size is initially 0
}

template <class Object>
void HashTable<Object> :: fillASCII()
{
	/*from its ascii code find the char, convert to string, and insert*/

	for (int i = 0; i < 256; i++)
	{
		char ch = i;
		string s(1,ch);
		insert(s);
	}

}

template <class Object>
int HashTable<Object> :: findPos(const Object & x)
{
	/*if the returned hash value is occupied (collision!) use linear probing
	to find another cell*/

	int counter = 0;
	int currentPos = hashFunction(x,4096);
	
	while (myArray[currentPos].info != EMPTY && myArray[currentPos].element != x && counter < 4096)
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
int HashTable<Object> :: findPos_insert(const Object & x)
{
	/*same but used in insert function*/

	if(currentSize < 4096)
	{
		int currentPos = hashFunction(x,myArray.size());
	
		while (myArray[currentPos].info != EMPTY && myArray[currentPos].element != x)
			currentPos = (currentPos +1) % 4096;
	
		return currentPos;
	}

	else
		return -1;
}

template <class Object>
bool HashTable<Object> :: isActive (int currentPos)
{
	return myArray[currentPos].info == ACTIVE;
}

template <class Object>
bool HashTable<Object> :: find (const Object & x)
{
	/*find the position of the element, return true if that position is occupied*/
	int currentPos = findPos(x);
	if(currentPos != -1 && isActive(currentPos))
		return true;
	return false;
}


template <class Object>
bool HashTable<Object> :: insert(const Object & x)
{
	/*insert x and increment the current size*/
	int currentPos = findPos_insert(x);

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

template <class Object>
int HashTable<Object> :: getCode(const Object & x)
{
	/*return the code of the element x*/
	int currentPos = findPos(x);
	if(currentPos != -1 && isActive(currentPos))
		return myArray[currentPos].code;
	else 
		return -1;
}

#endif