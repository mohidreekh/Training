#include <iostream>
#include<algorithm>
using namespace std;

struct Node {
	int item;
	Node* left;
	Node* right;
};


Node* insert(Node* root, int val) {

    if (root == nullptr) {
        Node* newNode = new Node;
        newNode->item = val;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    if (val > root->item) {
        root->right = insert(root->right, val);
    }
    else {
        root->left = insert(root->left, val);
    }
    return root;
}


int kthSmallestValue(Node* root, int &k, int &result) {
    if (root == nullptr)
        return 0;

    kthSmallestValue(root->left, k, result);

    k--;
    if (k > 0) {
        cout << root->item << "  ";
    }
    else if(k == 0)
        result = root->item;
    

    kthSmallestValue(root->right, k, result);

}

int main() {
	Node* root = new Node;
    root = nullptr;

    int arr[10] = { 5,6,3,2,4,1 };
    int k = 3;

    int x;
	for (int i = 0; i < 6; i++)
	{
		root = insert(root, arr[i]);
	}

    int result;
    cout << kthSmallestValue(root, k, result);
    cout << "\n Result:" << result;
}