//Binary Search Tree(b)實作一個 C++ 函式，從 BST 中刪除 key = k 的節點。
#include <iostream>
#include <algorithm>
using namespace std;

//節點結構
struct Node {
    int data;    
    Node* left;     
    Node* right;   
    Node(int val) : data(val), left(nullptr), right(nullptr) {} // 建構元 
};

//插入節點(到BST中)
Node* insert(Node* root, int key) {
    if (!root) return new Node(key);           //空樹直接建立節點
    if (key < root->data)                      //小的往左子樹放
        root->left = insert(root->left, key);
    else                                       //大的或等於的往右子樹放
        root->right = insert(root->right, key);
    return root;
}

//中序走訪BST 輸出節點資料(排序後)
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

//找出右子樹中的最小節點(中序繼承者)
Node* findMin(Node* root) {
    while (root->left) root = root->left;
    return root;
}

//從BST中刪除指定key的節點
Node* deleteNode(Node* root, int key) {
    if (!root) return root; //如果空樹直接返回

    if (key < root->data) {
        //往左子樹遞迴
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->data) {
        //往右子樹遞迴
        root->right = deleteNode(root->right, key);
    }
    else {
        //找到要刪除的節點
        if (!root->left && !root->right) {
            //沒有子節點（葉節點）
            delete root;
            return nullptr;
        }
        else if (!root->left) {
            //只有右子樹
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            //只有左子樹
            Node* temp = root->left;
            delete root;
            return temp;
        }
        else {
            //有兩個子樹
            Node* temp = findMin(root->right);     //找右子樹中最小的節點(中序繼承者)
            root->data = temp->data;               //用中序繼承者替代目前節點值
            root->right = deleteNode(root->right, temp->data); //刪除右子樹中重複的節點
        }
    }
    return root;
}

//計算BST的高度
int height(Node* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}

//主程式：測試插入、刪除與顯示BST
int main() {
    Node* root = nullptr;

    //插入一些節點
    int values[] = { 50, 30, 70, 20, 40, 60, 80 };
    for (int val : values) {
        root = insert(root, val);
    }

    cout << "中序走訪 BST（排序後）:" << endl;
    inorder(root);
    cout << "\n目前高度: " << height(root) << endl;

    //測試刪除
    cout << "\n刪除節點 20（葉節點）..." << endl;
    root = deleteNode(root, 20);
    inorder(root); cout << endl;

    cout << "\n刪除後 BST 高度: " << height(root) << endl;

    cout << "\n刪除節點 30（有一個子節點）..." << endl;
    root = deleteNode(root, 30);
    inorder(root); cout << endl;

    cout << "\n刪除後 BST 高度: " << height(root) << endl;

    cout << "\n刪除節點 50（有兩個子節點）..." << endl;
    root = deleteNode(root, 50);
    inorder(root); cout << endl;

    cout << "\n刪除後 BST 高度: " << height(root) << endl;

    cout << "\n刪除節點 80（有兩個子節點）..." << endl;
    root = deleteNode(root, 80);
    inorder(root); cout << endl;

    cout << "\n刪除後 BST 高度: " << height(root) << endl;
    return 0;
}
