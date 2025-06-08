//Binary Search Tree(a)你撰寫一個程式，從一棵空的BST開始，插入n個隨機值，觀察樹的高度height與log₂n的比值
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

//節點結構
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

//插入新節點(到BST中)
Node* insert(Node* root, int key) {
    if (!root) return new Node(key);
    if (key < root->data) root->left = insert(root->left, key);
    else root->right = insert(root->right, key);
    return root;
}

//計算高度
int height(Node* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

int main() 
{
    srand(time(0));

    //n值
    vector<int> ns = { 100, 500, 1000, 2000, 3000, 4000,5000, 6000, 7000, 8000, 9000, 10000 };

    //對所有n做
    for (int n : ns) {
        Node* root = nullptr;  //初始化BST

        //插入n個隨機值
        for (int i = 0; i < n; ++i) {
            int val = rand();  //隨機值
            root = insert(root, val);  //插入到BST中
        }

        //計算高度與高度對log2(n)的比值
        int h = height(root);
        double ratio = h / log2(n);

        //輸出結果：n, 高度, 高度/log2(n)
        cout << "n = " << n << ", height = " << h << ", ratio = " << ratio << endl;
    }

    return 0;
}
