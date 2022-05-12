#include <iostream>  
#include <fstream>
#include "string.h"  
#include "AVLtree.h"
#define MAX 100
using namespace std;

//this is an constructor that makes the root NULL
AVLtree::AVLtree()
{
    root = NULL;
}

//this function takes the character that we want to insert and it passes it to the function where the insertion
//takes place
void AVLtree::insert(char* x)
{
    root = insert1(root, x);
}

//this is the function for inserting a word to the tree
TreeNode* AVLtree::insert1(TreeNode* t, char* k)
{
    int i;
    if (Search2(k) == false) //checks if the word does not already exists in the tree
    {
        if (t == NULL) // checks if the node is NULL, which means that the word can be inserted in that node
        {
            t = new TreeNode;
            memcpy(t->word, k, MAX);
            t->freqAVL = 1;
            t->left = NULL;
            t->right = NULL;
        }
        else //if the node is not NULL
        {
            if (memcmp(k, t->word, MAX) < 0) //if the word we want to insert is smaller (alphabetical) than the word of the node
            {
                t->left = insert1(t->left, k);
            }
            else if (memcmp(k, t->word, MAX) > 0) //if the word we want to insert is bigger (alphabetical) than the word of the node            
            {
                t->right = insert1(t->right, k);
            }


            int balance = BalanceFactor(t); //the difference between the height of the left and the right subtree

            //if the tree is unbalanced (balance<-1 || balance>1) the we have 4 cases. In each one, we perform 
            //different rotations to make the tree balanced(-1<=balance<=1)

            if (balance > 1 && memcmp(k, t->left->word, MAX) < 0)
            {
                t = LeftLeft(t);
            }
            else if (balance < -1 && memcmp(k, t->right->word, MAX)>0)
            {
                t = RightRight(t);
            }
            else if (balance > 1 && memcmp(k, t->left->word, MAX) > 0)
            {
                t = LeftRight(t);
            }
            else if (balance < -1 && memcmp(k, t->right->word, MAX) < 0)
            {
                t = RightLeft(t);
            }
        }
    }

    t->h = height(t);
    return t;
}

//this function updates the heights of the subtrees,by increasing by 1, or making them 0 and it returns the height 
//of the tree, which is the bigger height betweeen the left and the right subtree
int AVLtree::height(TreeNode* t)
{
    int LeftHeight, RightHeight;
    if (t == NULL)
        return(0);
    if (t->left == NULL)
        LeftHeight = 0;
    else
        LeftHeight = 1 + t->left->h;
    if (t->right == NULL)
        RightHeight = 0;
    else
        RightHeight = 1 + t->right->h;
    if (LeftHeight > RightHeight)
        return LeftHeight;
    return RightHeight;
}


//this is a function for rotating the tree or the subtree to the right
TreeNode* AVLtree::RightRotation(TreeNode* t1)
{
    TreeNode* t2 = t1->left;
    TreeNode* T2 = t2->right;

    t2->right = t1;
    t1->left = T2;
    t1->h = height(t1);
    t2->h = height(t2);
    return t2;
}

//this is a function for rotating the tree or the subtree to the left
TreeNode* AVLtree::LeftRotation(TreeNode* t2)
{
    TreeNode* t1 = t2->right;
    TreeNode* T2 = t1->left;

    t1->left = t2;
    t2->right = T2;
    t1->h = height(t1);
    t2->h = height(t2);

    return t1;

}
//this is a function for the right right case of unbalanced tree in which a left rotation is performed
TreeNode* AVLtree::RightRight(TreeNode* t)
{
    t = LeftRotation(t);
    return(t);
}

//this is a function for the left left case of unbalanced tree in which a right rotation is performed
TreeNode* AVLtree::LeftLeft(TreeNode* t)
{
    t = RightRotation(t);
    return(t);
}

// this is a function for the left right case of unbalanced tree in which a leftand then a right rotation is performed
TreeNode* AVLtree::LeftRight(TreeNode* t)
{
    t->left = LeftRotation(t->left);
    t = RightRotation(t);
    return(t);
}
//this is a function for the right left case of unbalanced tree in which a right and then a left rotation is performed
TreeNode* AVLtree::RightLeft(TreeNode* t)
{
    t->right = RightRotation(t->right);
    t = LeftRotation(t);
    return(t);
}

//this function returns the difference between the height of left and the right subt
int AVLtree::BalanceFactor(TreeNode* t)
{
    int LeftHeight, RightHeight;
    if (t == NULL)
        return(0);
    if (t->left == NULL)
        LeftHeight = 0;
    else
        LeftHeight = 1 + t->left->h;
    if (t->right == NULL)
        RightHeight = 0;
    else
        RightHeight = 1 + t->right->h;
    return(LeftHeight - RightHeight);
}

//this is a function for inserting every word of the tree in preorder traversal(root, left, right) in the output file
void AVLtree::preorder(TreeNode* t)
{
    if (t != NULL)
    {
        fstream ofs;
        ofs.open("output.txt", ios::app);
        ofs << t->word << " " << t->freqAVL << endl;
        preorder(t->left);
        preorder(t->right);
    }
}

//this is a function for inserting every word of the tree in postorder traversal(right, left, root) in the output file
void AVLtree::postorder(TreeNode* t)
{
    if (t != NULL)
    {
        preorder(t->left);
        preorder(t->right);
        fstream ofs;
        ofs.open("output.txt", ios::app);
        ofs << t->word << " " << t->freqAVL << endl;
    }
}

//this is a function for inserting every word of the tree in inorder traversal(left, root, right) in the output file
void AVLtree::inorder(TreeNode* t)
{
    if (t != NULL)
    {
        fstream ofs;
        ofs.open("output.txt",ios::app);
        inorder(t->left);
        ofs << " " << t->word << " " << t->freqAVL << endl;
        inorder(t->right);
    }
}
//this function takes the we that we want to delete and it passes it to the function where the deletion
//takes place
void AVLtree::Delete(char* x)
{
    root = Delete1(root, x);
}

//this function searches the word while it keeps the tree balanced. When the word is found, it replaces the node with 
//the next node and rebalances the tree
TreeNode* AVLtree::Delete1(TreeNode* t, char* x)
{
    TreeNode* p;
    if (t == NULL)
    {
        return NULL;
    }
    else
    {
        for (int i = 0; i < strlen(x); i++)
            if (x[i] > t->word[i])
            {
                t->right = Delete1(t->right, x);
                if (BalanceFactor(t) == 2)
                    if (BalanceFactor(t->left) >= 0)
                        t = LeftLeft(t);
                    else
                        t = LeftRight(t);
                break;
            }
            else
                if (x[i] < t->word[i])
                {
                    t->left = Delete1(t->left, x);
                    if (BalanceFactor(t) == -2)
                        if (BalanceFactor(t->right) <= 0)
                            t = RightRight(t);
                        else
                            t = RightLeft(t);
                    break;
                }
                else
                {

                    if (t->right != NULL)
                    {
                        p = t->right;
                        while (p->left != NULL)
                            p = p->left;
                        memcpy(t->word, p->word, MAX);
                        t->right = Delete1(t->right, p->word);
                        if (BalanceFactor(t) == 2)
                            if (BalanceFactor(t->left) >= 0)
                                t = LeftLeft(t);
                            else
                                t = LeftRight(t);
                    }
                    else
                        return(t->left);
                    break;
                }
    }
    t->h = height(t);
    return t;
}

//this function searches the word that is given. If the word is found , it is being inserted to the output file,
//with its frequency
void AVLtree::Search(char* x)
{
    TreeNode* p;
    p = root;
    while (p != NULL)
    {
        if (strcmp(p->word, x) > 0)
            p = p->left;
        else
            if (strcmp(p->word, x) < 0)
                p = p->right;
            else
                if (strcmp(p->word, x) == 0)
                {
                    fstream ofs;
                    ofs.open("output.txt", ios::app);
                    ofs << p->word << " " << p->freqAVL << endl;
                    return ;
                }
    }
    return ;
}

//this function searches the word that is given. If the word is found, it increases the frequency of the word by 1 
//and returns true. Otherwise it returns false.
bool AVLtree::Search2(char* x)
{
    TreeNode* p;
    p = root;
    while (p != NULL)
    {
        if (strcmp(p->word, x) > 0)
            p = p->left;
        else
            if (strcmp(p->word, x) < 0)
                p = p->right;
            else
                if (strcmp(p->word, x) == 0)
                {
                    p->freqAVL++;
                    return true;
                }
    }
    return false;
}

//this function prints the time that the AVL tree needed to find 1000 words
void AVLtree::printTime(int num)
{
    ofstream ofs;
    ofs.open("output.txt", ios::app);
    ofs << "******Time taken by AVL Tree: " << num << " microseconds******" << endl;
}

