#pragma once
#include<iostream>
#include <fstream>
#define MAX 100
#include <chrono>
#include <cstring>

using namespace std;


class BST
{
    //The struct corresponds to a tree node
private:
    struct node {
        char* data;
        int freq;
        node* left;
        node* right;
    };

    //the root of the binary search tree
    node* root;

    //this function deletes the tree
    node* makeEmpty(node* t) {
        if (t == NULL)
            return NULL;
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        return NULL;
    }
  

    //this function inserts a word in the tree
    
    node* insert(char* x,int num, node* t)
    {
        if (t == NULL)
        {
            t = new node;
            t->data = new char[strlen(x) + 1];
            t->freq = num;
            memcpy(t->data, x, strlen(x));
            t->data[strlen(x)] = '\0';
            t->left = t->right = NULL;
        }
        else if (memcmp(x, t->data, MAX) < 0)
            t->left = insert(x, num, t->left);
        else if (memcmp(x, t->data, MAX) > 0)
            t->right = insert(x, num, t->right);
        return t; 
    }
   

    //this function removes a word from the tree
    node* remove(char* x, node* t) {
        node* temp;
        if (t == NULL)
            return NULL;
        else if (strcmp(x, t->data) < 0)
            t->left = remove(x, t->left);
        else if (strcmp(x, t->data) > 0)
            t->right = remove(x, t->right);
        else if (t->left && t->right)
        {
            temp = findMin(t->right);
            t->data = temp->data;
            t->freq = temp->freq;
            t->right = remove(t->data, t->right);
        }
        else
        {
            temp = t;
            if (t->left == NULL)
                t = t->right;
            else if (t->right == NULL)
                t = t->left;
            delete temp;
        }

        return t;
    }

    //this function searches for a word in a tree + prints in the file the word and the frequency
    void Search3(node* t, char* value)
    {
        
        if (t != NULL)
        {

            if (strcmp(t->data, value) == 0)
            {   
                ofstream ofs;
                ofs.open("output.txt", ios::app);
                ofs << t->data << " " << t->freq << endl;
                return;
            }
            else if (strcmp(t->data, value) > 0)
            {
                Search3(t->left, value);
            }
            else if (strcmp(t->data, value) < 0)
            {
                Search3(t->right, value);
            }

        }
    }

    //This function prints the elements using inorder
    void inorder(node* t) {
        static int c = 0;
        ofstream ofs;
        ofs.open("output.txt", ios::app);
        if (t == NULL)
            return;
        inorder(t->left);
        ofs <<++c <<".)" << t->data << " " << t->freq << endl;
        inorder(t->right);
    }

    //This function prints the elements using postorder
    void  postorder(node* t)
    {
        ofstream ofs;
        ofs.open("output.txt", ios::app);
        if (t == NULL)
            return;
        postorder(t->left);
        postorder(t->right);
        ofs << t->data << " " << t->freq << endl;
    }

    //This function prints the elements using preorder
    void  preorder(node* t)
    {
        ofstream ofs;
        ofs.open("output.txt", ios::app);
        if (t == NULL)
            return;
        ofs << t->data << " " << t->freq << endl;
        postorder(t->left);
        postorder(t->right);
    }

    //this function searches if a word already exists in the binary tree
    void Search2(node* t, char* value,bool&found)
    {

        if (t != NULL)
        {
            if (strcmp(t->data, value) == 0)
            {
                found = true;
                t->freq++;
               
                return;
            }
            else if (strcmp(t->data, value) > 0)
            {            
                Search2(t->left, value,found);
            }
            else if (strcmp(t->data, value) < 0)
            {
                Search2(t->right, value,found);
            }
        }
    }
    
    //this function finds the node with the minimum value
    node* findMin(node* t)
    {
        if (t == NULL)
            return NULL;
        else if (t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }

    //this function finds the node with the maximum value
    node* findMax(node* t) {
        if (t == NULL)
            return NULL;
        else if (t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }


public:

    BST();

    ~BST();

    void insert(char* x, int num);

    void Search(char* d,bool&);

    void Search4(char* d);

    void display();

    void display2();

    void display3();

    void remove(char*);

    void printTime(int);

    void addInBST(char *);

};