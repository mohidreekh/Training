#include <iostream>
#include<vector>
#include<string>
using namespace std;
struct Node {
    int item;
    Node* left;
    Node* right;

    Node(int n) : item(n), left(nullptr), right(nullptr) {}
};

void getNumbersFromTree(Node* root, string &number, vector<string> &numbers) {

    if (root == nullptr)
        return;

    number += to_string(root->item);

    if (root->left == nullptr && root->right == nullptr)
    {
        numbers.push_back(number);
    }
    else {
        getNumbersFromTree(root->left, number, numbers);
        getNumbersFromTree(root->right, number, numbers);
    }

    number.pop_back();
}

int getSumOfArray(vector<string>numbers) {
    int sum = 0;
    for (int i = 0; i < numbers.size(); i++) {
        sum += stoi(numbers[i]);
    }
    return sum;
}

int main() {
    //Node* root = new Node(1);
    //root->left = new Node(2);
    //root->right = new Node(3);

    Node* root = new Node(4);
    root->left = new Node(9);
    root->right = new Node(0);
    root->left->left = new Node(5);
    root->left->right = new Node(1);

    string number;
    vector<string> numbers;

    getNumbersFromTree(root, number, numbers);

    cout << "\nSum = " << getSumOfArray(numbers) << endl;
}