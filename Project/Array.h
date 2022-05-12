#pragma once

class Array
{
private:
	int position; 
	int SumWords; 
public:
	char** A; //unsorted array
	int* Frequency; //frequency array
	Array(); 
	void addInArray(char*); //this function adds a new word in the array
	bool WordExists(char*); //this function checks if a word is already in the array
	int GetPosition(); 
	int GetSumWords(); 
	void LinearSearch(char*); //linear search
	void DeleteElement(char* value); //this function deletes an element from the array
	void ReallocArray(); //this function adds more space in the array
	void printTime(int); //this function prints the time of linear search
};


