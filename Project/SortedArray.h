#pragma once

class SortedArray
{
private:
	int position2; 
	int SumWords; 
public:
	char** B; //sorted array
	int* Frequency2; //frequency array
	SortedArray();
	void insertInSortedArray(char*); //this function adds a new word in the array
	void BinarySearch(char* randwords); //binary search
	void DeleteElement2(char*); //this function deletes an element
	int GetPosition2(); 
	int GetSumWords2(); 
	void printTime(int);
	void ReallocArray2(); //this function adds more space in the array
	bool WordExists(char*); //this function finds if a word already exists in the array
};