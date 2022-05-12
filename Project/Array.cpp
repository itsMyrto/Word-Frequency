#include "Array.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <cstring>

#define MAX 100

using namespace std;

//The constructor creates two parallel arrays, one for the words and one for the frequency of each word. Both arrays will start with 5000 positions. 
Array::Array()
{
    position = 0;
    SumWords = 5000;
    A = new char* [SumWords];
    Frequency = new int[SumWords];

    for (int i = 0; i < SumWords; i++)
        Frequency[i] = 0;
}

int Array::GetPosition()
{
    return position;
}

int Array::GetSumWords()
{
    return SumWords;
}

//This function adds extra space in the array. 
//First Step: Create 2 new parallel arrays with 5000 more positions
//Second Step: Copy all the words & the frequencies in the new arrays
//Third Step: Delete the old arrays

void Array::ReallocArray()
{
    int* temp1;
    char** temp2;

    SumWords = SumWords + 5000;
    temp1 = new int[SumWords * sizeof(int)];
    temp2 = new char* [SumWords];

    for (int i = 0; i < position; i++)
    {
        temp1[i] = Frequency[i];
        temp2[i] = new char[MAX];

        for (int j = 0; j < MAX; j++)
        {
            temp2[i][j] = A[i][j];
        }
    }

    for (int i = position; i < SumWords; i++)
    {
        temp1[i] = 0;
    }

    for (int i = 0; i < position; i++)
    {
        delete[] A[i];
    }

    delete[] Frequency;
    delete[] A;

    Frequency = temp1;
    A = temp2;
}


//This function gets as a parameter a word and returns if the word exists in the array A (public member of the class - where we save the different words). If so, it increases the
//frequency and returns true. Otherwise (if it doesnt exist) it returns false.
bool Array::WordExists(char* temp)
{
    for (int i = 0; i < position; i++)
    {
        if (strcmp(A[i], temp) == 0)
        {
            Frequency[i]++;
            return true;
        }
    }

    return false;
}

//This function first checks if there is available space to add a new word. If not then it calls the function ReallocArray to get some more space
//Then it searches if the word that got as a parameter already exists in the array. If it doesnt, then it is added. 
void Array::addInArray(char* temp)
{
    int size;
    size = strlen(temp);
    
    if (position == SumWords)
    {
        ReallocArray();
    }

    if (WordExists(temp) == false)
    {
        A[position] = new char[MAX];
        memcpy(A[position], temp, size);
        A[position][size] = '\0';
        Frequency[position]=1;
        position++;
    }
    else
    {
        return;
    }
}

//Linear Search for a word + prints it in the output text

void Array::LinearSearch(char* RandomWords)
{
    
    int i, j;
    ofstream ofs;
    ofs.open("output.txt", ios::app);

    
    for (j = 0; j < GetPosition(); j++)
    {
        if (strcmp(RandomWords, A[j]) == 0)
        {    
            ofs << A[j] << " " << Frequency[j] << endl;
            break;
        }

    }

}

//This function deletes a word from the array A.
//1st step : Searching for the position of the element that we want to delete
//2nd step : Moving all the elements, that were on the right of the deleted element, one position on the left (both in A and Frequency arrays).
//3rd step : Decreasing the number of the array A elements
void Array::DeleteElement(char* value)
{
    int pos = -1;

    for (int i = 0; i < position; i++)
    {
        if (strcmp(value, A[i]) == 0)
        {
            pos = i;
            cout << "Found!" << endl;
            break;
        }
    }

    if (pos == -1)
    {
        cout << "It doenst exist" << endl;
        return;
    }

    for (int i = pos; i < position - 1; i++)
    {
        for (int k = 0; k < MAX; k++)
        {
            swap(A[i][k], A[i + 1][k]);
        }

        swap(Frequency[i], Frequency[i + 1]);
    }

    position--;

    return;

}

void Array::printTime(int time)
{
    ofstream ofs;
    ofs.open("output.txt", ios::app);
    ofs << "******Time taken by Unsorted Array: " << time << " seconds******" << endl;
}