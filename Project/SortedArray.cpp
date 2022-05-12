#include "SortedArray.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <fstream>
#include <cstring>

using namespace std;
#define MAX 100

using namespace std;

//Constructor
SortedArray::SortedArray()
{
	position2 = 0;
	SumWords = 5000;
	B = new char* [SumWords];
	Frequency2 = new int[SumWords];
	for (int i = 0; i < SumWords; i++)
	{
		Frequency2[i] = 0;
		B[i] = new char[MAX];
	}

}

//This function gets as a parameter a word and returns if the word exists in the array B. If so, it increases the frequency and returns true. Otherwise it returns false.
bool SortedArray::WordExists(char* temp)
{
	int size;

	size = strlen(temp);

	int start = 0, end = position2 - 1, middle;

	while (start <= end)
	{
		middle = (end + start) / 2;

		if (memcmp(B[middle], temp, MAX) == 0)
		{
			Frequency2[middle]++;
			return true;
		}
		else if (memcmp(B[middle], temp, MAX) > 0)
		{
			end = middle - 1;
		}
		else
		{
			start = middle + 1;
		}
	}

	return false;
}

//This function adds more space in the array 
void SortedArray::ReallocArray2()
{
	int* temp1;
	char** temp2;

	SumWords = SumWords + 5000;
	temp1 = new int[SumWords * sizeof(int)];
	temp2 = new char* [SumWords];

	for (int i = 0; i < position2; i++)
	{
		temp1[i] = Frequency2[i];
		temp2[i] = new char[MAX];

		for (int j = 0; j < MAX; j++)
		{
			temp2[i][j] = B[i][j];
		}
	}

	for (int i = position2; i < SumWords; i++)
	{
		temp1[i] = 0;
		temp2[i] = new char[MAX];
	}

	for (int i = 0; i < position2; i++)
	{
		delete[] B[i];
	}

	delete[] Frequency2;
	delete[] B;

	Frequency2 = temp1;
	B = temp2;
}

//this function inserts a word in the array B.
//First it checks if already exist. If it doesnt then it searches for the correct position, so they can be alphabetically placed. To add a new word its necessary to move all the 
//elements from the position where the new word will be added and after, one position right
void SortedArray::insertInSortedArray(char* word)
{
	int size = strlen(word);

	if (position2 == SumWords)
	{
		ReallocArray2();
	}

	if (WordExists(word) == false)
	{
		if (position2 == 0)
		{
			B[position2] = new char[MAX];

			for (int i = 0; i < size; i++)
			{
				B[position2][i] = word[i];
			}

			B[position2][size] = '\0';
			Frequency2[position2] = 1;
			position2++;
		}
		else
		{
			int pos = position2;

			for (int i = 0; i < position2; i++)
			{
				if (memcmp(word, B[i], MAX) < 0)
				{
					pos = i;
					break;
				}
			}


			for (int i = position2; i > pos; i--)
			{
				swap(B[i], B[i - 1]);
				swap(Frequency2[i], Frequency2[i - 1]);
			}

			for (int i = 0; i < size; i++)
			{
				B[pos][i] = word[i];
			}

			B[pos][size] = '\0';
			Frequency2[pos] = 1;
			position2++;

		}
	}
	else
	{
		return;
	}
}

int SortedArray::GetPosition2()
{
	return position2;
}

int SortedArray::GetSumWords2()
{
	return SumWords;
}

//Binary Search
void SortedArray::BinarySearch(char* RandomWords)
{
	int middle;
	int words = 0;
	int bigger, letter, same, count;
	ofstream ofs;
	ofs.open("output.txt", ios::app);


	int start = 0;
	int end = position2 - 1;
	int d = 0;

	while (d == 0 && start <= end)
	{
		middle = (start + end) / 2; //finding the middle element


		if (strcmp(RandomWords, B[middle]) == 0) //if the middle element is the same with the word we are searching for then it prints the word & frequency and returns
		{
			ofs <<B[middle] << " " << Frequency2[middle] << endl;
			d = 1;
			break;
		}
		else
		{
			bigger = 0;
			letter = 0;
			same = 0;
			count = 0;

			while (bigger == 0 && count < 20) //comparing letter by letter so we can find if the word we are searching for is bigger or smaller from the middle element
			{
				if (RandomWords[letter] > B[middle][letter]) 
				{
					same = 0;
					bigger = 1;
				}
				else if (RandomWords[letter] == B[middle][letter])
				{
					same = 1;
					letter++;
				}
				else
				{
					count = 20;
				}
			}

			if (bigger == 1) //if  word > middle element, then we start searching in second half of the array 
			{
				start = middle + 1;
			}
			else
			{
				end = middle - 1; //if word <middle element, then we start searching in the first half of the array
			}
		}
	}
}

//This function deletes and element
//1st step : Searching for the position of the element that we want to delete
//2nd step : Moving all the elements, that were on the right of the deleted element, one position on the left (both in A and Frequency arrays).
//3rd step : Decreasing the number of the array A elements
void SortedArray::DeleteElement2(char* value)
{
	int start = 0, end = position2 - 1, middle, pos;
	bool found = false;

	while (found == false && start <= end)
	{
		middle = (start + end) / 2;

		if (strcmp(B[middle], value) == 0)
		{
			found = true;
			pos = middle;
		}

		else if (strcmp(B[middle], value) > 0)
		{
			end = middle - 1;
		}
		else
		{
			start = middle + 1;
		}
	}

	if (found == true)
	{
		for (int i = pos; i < position2 - 1; i++)
		{
			for (int k = 0; k < MAX; k++)
			{
				swap(B[i][k], B[i + 1][k]);
			}

			swap(Frequency2[i], Frequency2[i + 1]);
		}

		position2--;
	}
	else
	{
		cout << "The word you entered does not exist" << endl;
	}
}

//this function prints the time that binary search needs to find 1000 elements
void SortedArray::printTime(int num)
{
	ofstream ofs;
	ofs.open("output.txt", ios::app);
	ofs << "******Time taken by Sorted Array: " << num << " microseconds******" << endl;
}