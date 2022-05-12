#define MAX 100

struct TreeNode {
    char word[MAX];
    int freqAVL;
    TreeNode* right;
    TreeNode* left;
    int h;
};
class AVLtree
{

public:

    AVLtree();
    TreeNode* root;
    TreeNode* insert1(TreeNode*, char*);
    void insert(char* x);
    int height(TreeNode*);
    TreeNode* Delete1(TreeNode*, char*);
    void Delete(char* x);
    TreeNode* RightRotation(TreeNode*);
    TreeNode* LeftRotation(TreeNode*);
    TreeNode* RightRight(TreeNode*);
    TreeNode* LeftLeft(TreeNode*);
    TreeNode* LeftRight(TreeNode*);
    TreeNode* RightLeft(TreeNode*);
    int BalanceFactor(TreeNode*);
    void preorder(TreeNode*);
    void inorder(TreeNode*);
    void postorder(TreeNode*);
    void Search(char* x);
    bool Search2(char* x);
    void printTime(int);


};

