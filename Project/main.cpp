#include <iostream>
#include <fstream>
#include <cstring>
#include <chrono>
#include "Array.h"
#include "SortedArray.h"
#include "BinaryTree.h"
#include "HashingArray.h"
#include "AVLtree.h"
#define MAX 100
#define NumOfRand 1000

using namespace std;
using namespace chrono;

int main()
{
	ofstream ofs;
	fstream file;
	string word, filename;
	int size, j;
	int posOfRand = 0;
	char** randwords;
	randwords = new char* [NumOfRand];
	int *randkey = new int[NumOfRand];
	int tempPosition;


	//opening the file that contains the text
	filename = "gutenberg.txt";
	file.open(filename.c_str());

	//Creating objects from different types of data structures
	Array WordArray;
	SortedArray WordArray2;
	HashingArray WordArray3;
	BST binarytree;
	AVLtree avltree;
	
	while (file >> word) //reading every word from the file 
	{
		j = 0;
		size = word.size(); //this variable contains the number of letters that a word has.

		while (j < size) //in this loop we remove all the punctuations and also change capitals to small letters. 
		{
			char* temp; 
			temp = new char[MAX];
			tempPosition = 0;

			while ((word[j] < 65 || word[j] > 122) || (word[j] > 90 && word[j] < 97)) //this loop searches for the first letter of the word. For example: ***the -> t
			{
				j++; 

				if (j == size) //if j==size it means that there are only symbols and no letters
					break;
			}
		
			while ((word[j] >= 97 && word[j] <= 122) || (word[j] >= 65 && word[j] <= 90)) //this loop changes the capital letters to small letters using the ascii code
			{
				if (word[j] >= 65 && word[j] <= 90)
				{
					temp[tempPosition] = word[j] + 32; 
					tempPosition++;
					j++;
				}
				else
				{
					temp[tempPosition] = word[j];
					tempPosition++;
					j++;
				}
			}

			temp[tempPosition] = '\0'; //adding '\0' -> end of the word

			if (temp[0] == '\0') //if temp[0] = '\0' then there is no word so it continues in the next loop		
			{
				j++;
				continue;
			}


			if (posOfRand < NumOfRand) //picking the first 1000 words & calculating for each word the key for the hash table search 
			{
				randwords[posOfRand] = new char[MAX];
				memcpy(randwords[posOfRand], temp, MAX);
				randkey[posOfRand] = 0;

				for (int l = 0; l < strlen(randwords[posOfRand]); l++)
				{
					randkey[posOfRand] = randkey[posOfRand] + (int)randwords[posOfRand][l] * l; 
				}

				posOfRand++;
			}

			//inserting a word in all types of data structures
			WordArray.addInArray(temp); //unsorted array
			WordArray2.insertInSortedArray(temp); //sorted array
			WordArray3.InsertElements(temp); //hast table
			binarytree.addInBST(temp); //binary search tree
			avltree.insert(temp); //avl tree
			j++;
			delete[] temp;
		}
		
	}


	//Output file
	ofs.open("output.txt");

	//deleting a word from the unsorted array & printing the elements after the deletation
	/*
	WordArray.DeleteElement((char*)"the");

	for (int i = 0; i < WordArray.GetPosition(); i++)
	{
		ofs << i + 1 << ".) " << WordArray.A[i] << " " << WordArray.Frequency[i] << endl;
	}
	*/


	//deleting a word from the sorted array & printing the elements after the deletation
	/*
	WordArray2.DeleteElement2((char*)"the");
	for (int i = 0; i < WordArray2.GetPosition2(); i++)
	{
		ofs << i + 1 << ".) " << WordArray2.B[i] << " " << WordArray2.Frequency2[i] << endl;
	}
	*/


	// inorder - postorder and preorder for the binary search tree
	 /*
	 ofs << "Inorder: " << endl;
	 binarytree.display();

	 ofs << "Postorder: " << endl;
	 binarytree.display2();

	 ofs << "Preorder: " << endl;
	 binarytree.display3();
	 */


	 //Deleting a word from Binary Search Tree & printing the elements after the deletation
	  /*
	  binarytree.remove((char*)"the");
	  binarytree.display();
	  */

	  //inorder - postorder and preorder for the avl tree
	  /*
		 avltree.inorder(avltree.root);
		 avltree.postorder(avltree.root);
		 avltree.preorder(avltree.root);
	 */

	 //Deleting a word from avl tree
	 //avltree.Delete((char*) "the");


	//finding the duration of different data structures 

	auto start = high_resolution_clock::now();
	for (int i = 0; i < NumOfRand; i++)
	{
		WordArray.LinearSearch(randwords[i]);
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast <microseconds> (stop - start);
	WordArray.printTime(duration.count());


	auto start2 = high_resolution_clock::now();
	for (int i = 0; i < NumOfRand; i++)
	{
		WordArray2.BinarySearch(randwords[i]);
	}
	auto stop2 = high_resolution_clock::now();
	auto duration2 = duration_cast<microseconds>(stop2 - start2);
	WordArray2.printTime(duration2.count());

	
	auto start3 = high_resolution_clock::now();
	for (int i = 0; i < NumOfRand; i++)
	{
		binarytree.Search4(randwords[i]);
	}
	auto stop3 = high_resolution_clock::now();
	auto duration3 = duration_cast <microseconds> (stop3 - start3);
	binarytree.printTime(duration3.count());
	


	auto start4 = high_resolution_clock::now();
	for (int i = 0; i < NumOfRand; i++)
	{
		avltree.Search(randwords[i]);
	}
	auto stop4 = high_resolution_clock::now();
	auto duration4 = duration_cast <microseconds> (stop4 - start4);
	avltree.printTime(duration4.count());


	auto start5 = high_resolution_clock::now();
	for (int i = 0; i < NumOfRand; i++)
	{
		WordArray3.HashSearch(randwords[i],randkey[i]);
	}
	auto stop5 = high_resolution_clock::now();
	auto duration5 = duration_cast <microseconds> (stop5 - start5);
	WordArray3.printTime(duration5.count());
	

	return 0;
}
