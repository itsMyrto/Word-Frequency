#pragma once

class HashingArray
{
private:
	int position3;
	int posNum;
public:
	char** data; 
	int* Frequency3;
	HashingArray();
	int GetPosition3();
	void InsertElements(char*); //Inserting Elements
	void HashSearch(char*,int); //Searching elements
	void printTime(int);
	void ReallocHash(); //Increasing the space of the array 
	bool WordExists(char*); //returns true if a word already exists
};