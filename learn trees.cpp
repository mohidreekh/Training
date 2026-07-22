#include <iostream>
#include<algorithm>
using namespace std;


struct Node {
	int item;
	Node* left;
	Node* right;

    int height = 0;
};

struct  Tnode
{
    char data;
    bool isEndOfWord = 0;

    Tnode* left, * mid, * right;
};

Tnode* newNode(char val) {
    Tnode* node = new Tnode;
    node->data = val;
    node->isEndOfWord = false;
    node->left = node->mid = node->right = nullptr;

    return node;
}


void insertTST(Tnode*& root, char* word) {
    if (!root) {
        root = newNode(*word);
    }

    if ((*word) < root->data) {
        insertTST(root->left, word);
    }
    else if (*word > root->data)
    {
        insertTST(root->right, word);
    }
    else
    {
        if (*(word + 1) != '\0')
            insertTST(root->mid, word + 1);
        else
            root->isEndOfWord = true;
    }
}

void traversTST(Tnode* root, string word)
{
    if (root == nullptr)
        return;

    traversTST(root->left, word);


    string current = word + root->data;


    if (root->isEndOfWord) {
        cout << current << "   ";
    }

    traversTST(root->mid, current);

    traversTST(root->right, word);
}


int getHeight(Node* n) {

    if (n == nullptr)
        return 0;
    else
        return n->height;
}

int getBalance(Node* n) {
    if (n == nullptr)
    {
        return 0;
    }

    return getHeight(n->left) - getHeight(n->right);
}


Node* rightRotate(Node* n) {
    Node* x = n->left;
    Node* tempRight = n->right;

    x->right = n;
    n->left = tempRight;

    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

Node* leftRotate(Node* n) {
    Node* x = n->right;
    Node* tempLeft = n->left;

    x->left = n;
    n->right = tempLeft;

    n->height = 1 + max(getHeight(n->left), getHeight(n->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}


Node* insert(Node* root, int val) {

    if (root == nullptr) {
        Node* newNode = new Node;
        newNode->item = val;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->height = 0;
        return newNode;
    }


    if (val > root->item) {
        root->right = insert(root->right, val);
    }
    else {
        root->left = insert(root->left, val);
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && val < root->left->item){
        // L-L
        return rightRotate(root);
    }
    else if (balance > 1 && val > root->left->item){
        // L-R
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    else if (balance < -1 && val < root->right->item){
        // R-L
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    else if (balance < -1 && val > root->right->item){
        // R-R
        return leftRotate(root);
    }

    return root;
}

void travers(Node* root) {

    if (root == nullptr)
        return;

    travers(root->left);

    cout << root->item << "  ";

    travers(root->right);

}

int main() {
    //AVL Tree
	Node* root = new Node;
    root->item = 10;
    root->left = nullptr;
    root->right = nullptr;

    int arr[10] = { 20,15,7,3,23,50,33,8,1,5 };
    int x;
	for (int i = 0; i < 10; i++)
	{
		insert(root, arr[i]);
	}

    travers(root);


    //Tnode* root = nullptr;

    //char words[][20] = {
    //    "cat",
    //    "car",
    //    "cart",
    //    "dog",
    //    "door",
    //    "apple",
    //    "app",
    //    "bat",
    //    "ball",
    //    "banana"
    //};


    //for (int i = 0; i < 10; i++)
    //{
    //    insertTST(root, words[i]);
    //}

    //string word = "";
    //traversTST(root, word);
}