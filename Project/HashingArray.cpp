#include "HashingArray.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <cmath>
#define MAX 100

using namespace std;

HashingArray::HashingArray()
{
	position3 = 0;
	posNum = 2000;
	data = new char* [posNum];
	Frequency3 = new int[posNum];

	for (int i = 0; i < posNum; i++)
	{
		Frequency3[i] = 0;
		data[i] = new char[MAX];
		data[i][0] = '\0';
	}
}

int HashingArray::GetPosition3()
{
	return position3;
}

//this function returns true if the word already exists in the hash table
bool HashingArray::WordExists(char* temp)
{
	int size, pos, j;
	bool found = false;

	int code = 0; 
	for (int i = 0; i < strlen(temp); i++)
	{
		code = code + (int)temp[i]*i;  //calculating using the hash function the position in which the word might have been inserted in the hash table
	}
	pos = code % posNum;

	j = pos;

	while (found == false)
	{
		if (strcmp(data[j], temp) == 0)
		{
			Frequency3[j]++;
			found = true;
		}
		if (j == posNum - 1) //if we are in the last position of the array then we start searching from position 0 (returns true)
		{
			j = 0;
		}
		else
		{
			j++;
			if (j == pos) // return false - the word does not exist in the array
			{
				break;
			}
			else if (data[j][0] == '\0') //if the data[j][0] is empty it means that there is no way that the word we are searching for has already been added in the array (returns false)
			{
				break;
			}

		}
	}

	return found;
}

//Step 1: Converting the word into an integer by multiplying the ascii code from each letter with the position of the letter inside the word and adding the previous products
//Step 2: Finding the position on the array by dividing the previous sum with the number of the total positions of the array and taking the modulo.
void HashingArray::InsertElements(char* word)
{
	int pos, size, j;

	if (position3 == (posNum*50)/100) //if the hash table is half full then we expand the array (2x more space)
	{
		ReallocHash(); 
	}

	if (WordExists(word) == false)
	{
		if (word[0] == '\0')
		{
			return;
		}

		size = strlen(word);
		int code = 0;
		for (int i = 0; i < strlen(word); i++)
		{
			code = code + (int)word[i] * i; 
		}
		pos = code % posNum;

		j = pos;
		
		while (data[j][0] != '\0') //loop when collision happens, searching for the next position
		{
			if (j == posNum - 1)
			{
				j = 0;
			}
			else
			{
				j++;
			}
		}

		for (int k = 0; k < size; k++)
		{
			data[j][k] = word[k];
		}

		data[j][size] = '\0';
		Frequency3[j] = 1;
		position3++;
	}
	else
	{
		return;
	}

}

//Searching an element in the array
void HashingArray::HashSearch(char* randwords,int code)
{

	int pos, size, j;
	bool found;

	ofstream ofs;
	ofs.open("output.txt", ios::app);

	size = strlen(randwords);

	pos = code % posNum;

	j = pos;
	found = false;

	while (found == false)
	{
		if (strcmp(data[j], randwords) == 0)
		{
			found = true;
			ofs << data[j] << " " << Frequency3[j] << endl;
		}

		if (j == posNum - 1)
		{
			j = 0;
		}

		else
		{
			j++;

		}
	}
}

//if the array is full and we need more space , this function binds more space + adds all the elements from the beginning. 
void HashingArray::ReallocHash()
{
	int size, pos, j;
	char** temp;
	int current = posNum;
	posNum = posNum * 2; //2x more space
	temp = new char* [posNum];
	int* tempfreq;
	tempfreq = new int[posNum];

	for (int i = 0; i < posNum; i++)
	{
		tempfreq[i] = 0;
		temp[i] = new char[MAX];
		temp[i][0] = '\0';

	}

	for (int i = 0; i < current; i++)
	{
		size = strlen(data[i]);

		int code = 0;
		for (int m = 0; m < strlen(data[i]); m++)
		{
			code = code + (int)data[i][m] * m; //calculating using the hash function the position in which the word is going to be inserted in the hash table
		}
		pos = code % posNum; //now the hash function changes since the posNum is two times bigger than the previous one

		j = pos;

		while (temp[j][0] != '\0')
		{
			if (j == posNum - 1)
			{
				j = 0;
			}
			else
			{
				j++;
			}
		}

		for (int k = 0; k < size; k++)
		{
			temp[j][k] = data[i][k];
		}

		temp[j][size] = '\0';
		tempfreq[j] = Frequency3[i];
	}
	
	for (int i = 0; i < current; i++) //deleting both arrays
		delete[] data[i];

	delete[] data;
	delete[] Frequency3;
	data = temp;
	Frequency3 = tempfreq;
}

//prints the time that the hash search needed to find 1000 words
void HashingArray::printTime(int time)
{
	ofstream ofs;
	ofs.open("output.txt", ios::app);
	ofs << "******Time taken by Hash Array: " << time << " microseconds******" << endl;
}
