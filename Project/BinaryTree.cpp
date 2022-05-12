#include "BinaryTree.h"
#include <cstring>
#include <iostream>
#include <chrono>
#include <cstring>

using namespace std;


BST::BST() {
    root = NULL;
}

BST::~BST() {
    root = makeEmpty(root);
}

void BST::insert(char* x, int num) {

    root = insert(x, num, root);
}

void BST::display() {
    inorder(root);
    cout << endl;
}

void BST::display2()
{
    postorder(root);
}

void BST::display3()
{
    preorder(root);
}

void BST::Search(char* value,bool&found)
{
    Search2(root, value,found);
}

void BST::Search4(char* value)
{
    Search3(root, value);
}

void BST::remove(char* x)
{
    root = remove(x, root);
}

//Step 1: Searching if the word already exists
//Step 2: If not then it is added 
void BST::addInBST(char* word)
{
    bool found = false;

    Search(word,found);

    if (found==false)
    {
        insert(word,1);
        return;
    }
    else
    {
        found = false;
        return;
    }
   
}

//this function prints the time that the binary tree needed to find 1000 words
void BST::printTime(int num)
{
    ofstream ofs;
    ofs.open("output.txt", ios::app);
    ofs << "******Time taken by the Binary Tree: " << num << " microseconds******" << endl;
}