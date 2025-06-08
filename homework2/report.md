# 12

Group 12  
41243202 林沛慧  
41243208 蕭昱糖

## 解題說明

#### 1. Max/Min Heap

此題要求完成以下兩部分：

1. 抽象類別MinPQ的設計
    
    根據MaxPQ抽象類別範本，撰寫一個C++抽象類別MinPQ，用於定義一個最小優先佇列（Min Priority Queue）。MaxPQ是一個最大優先佇列，包含以下純虛擬函數：
    * 虛擬析構函數
    * IsEmpty()：檢查佇列是否為空
    * Top()：回傳引用的最大元素
    * Push(const T&)：加入一個元素
    * Pop()：移除最大優先級的元素
    
    需要為MinPQ設計類似的類別，但改為操作最小元素。

2. MinHeap類別的實作

    撰寫一個C++類別MinHeap，繼承自MinPQ抽象類別，並實作所有純虛擬函數。這些函數的時間複雜度應與MaxHeap的對應函數相同。

#### 2. Binary Search Tree

此題分為兩部分：

1. 隨機插入與二元搜尋樹高度分析

    撰寫一個C++程式，模擬以下過程：
    * 從一個空的二元搜尋樹（BST）開始。
    * 使用均勻隨機數值產生器，產生隨機數值並插入樹中，重複n次。
    * 測量最終樹的高度，並計算高度與 log₂(n) 的比值（height / log₂(n)）。
    * 對n=100, 500, 1000, 2000, 3000, ..., 10000 執行此過程。
    
    繪製比值（height / log₂(n)）隨n變化的圖表。
    
    理論上，隨機插入下，該比值應趨近於一個常數（約為 2）。驗證這一點是否正確。

2. 刪除節點函數
    撰寫一個C++函數，從二元搜尋樹中刪除鍵值為k的節點並分析該函數的時間複雜度。

#### 3. Finish the exercise 1 in Textbook p.457 

此題涉及外部排序（External Sorting），分為兩部分：

1. 外部排序第二階段的輸入時間

    * 假設有 $n$ 筆記錄需排序，但電腦記憶體只能容納 $S$ 筆記錄（$S << n$）。
    * 輸入資料儲存在磁碟上，包含 $m$ 個已排序的runs。
    * 每次磁碟存取的尋軌時間為 $t_s$，延遲時間為 $t_l$，每筆記錄的傳輸時間為 $t_t$。
    * 記憶體被分割為輸入/輸出緩衝區，支援如「Program 7.21」所述的 $k$ 路合併（k-way merge），並允許輸入、輸出和CPU處理重疊。
    * 問題：計算外部排序第二階段（合併階段）的總輸入時間。
2. 輸入時間與 $k$ 的關係
    * 給定：
        * CPU合併所有runs的時間為 $t_{CPU}$（假設與 $k$ 無關，為常數）。
        * 參數：$t_s = 80 $ ms, $t_l = 20 $ ms, $n = 200000$, $m = 64$, $t_t = 10⁻³$ 秒/記錄, $S = 2000$。
    * 繪製總輸入時間 $t_{input}$ 隨 $k$ 變化的粗略圖表。
    * 問題：是否存在一個 $k$ 值，使得 $t_{CPU}$ 約等於 $t_{input}$？

### 解題策略

#### 1. Max/Min Heap

1. 抽象類別MinPQ的設計
    * 宣告純虛擬函數：IsEmpty()檢查是否為空，Top()回傳最小元素，Push()加入元素，Pop()移除最小元素。
    * 額外加入getComparisons()和getSwaps()，用於追蹤操作的比較和交換次數，方便分析效率。
    * 使用虛擬析構函數，確保衍生類別資源正確釋放。
2. MinHeap類別的實作
    * 資料結構：使用動態陣列heap儲存元素，模擬最小堆積（父節點小於子節點）。
    * 關鍵操作：
        * IsEmpty()：檢查size是否為0，時間複雜度 O(1)、計數一次比較(size==0)。
        * Top()：若堆積為空，丟出異常；否則回傳根節點heap[0](最小元素)，時間複雜度 O(1)、計數IsEmpty()內的比較。
        * Push(const T&)：若陣列滿了，動態擴充容量(倍增)。將新元素加入陣列末端，執行swim運算(上移)，與父節點比較並交換，直到滿足最小堆積性質。時間複雜度 O(log n)，因上移操作與堆積高相關。計數比較(父節點vs.當前節點)和交換次數。
        * Pop()：若堆積為空，丟出異常。用最後一個元素替換根節點，減少大小，執行sink運算(下沉)，與較小的子節點比較並交換，直到滿足最小堆積性質。時間複雜度 O(log n)，因下沉操作與堆積高相關。計數比較(子節點間、父節點vs.子節點)和交換次數。
    * 輔助函數：
        * swim(int index)：新元素上移，與父節點比較，確保最小堆積性質。
        * sink(int index)：元素下沉，與較小的子節點交換，維持堆積結構。
    * 時間複雜度：與最大堆積一致，IsEmpty和visitatori為 O(1)，Push和Pop為 O(log n)。

#### 2. Binary Search Tree

1. 隨機插入與樹高比值

    (1) 資料結構與插入
        
    * 定義Node結構，包含資料值、左子節點和右子節點指標。
    * 實作insert(Node*, int)函數：
        * 若樹空，創建新節點。
        * 遞迴比較鍵值，小於根節點則插入左子樹，大於等於則插入右子樹。
        * 時間複雜度：O(h)，h為樹高，隨機插入下平均為 O(log n)。

    (2) 高度計算
    * 實作height(Node*)函數：
        * 若節點為空，回傳0。
        * 否則，遞迴計算左、右子樹高度，取最大值加1。
        * 時間複雜度：O(n)，需走訪所有節點。

    (3) 模擬與比值計算
    * 使用srand(time(0))初始化隨機種子，確保值均勻隨機。
    * 對n = 100, 500, 1000, ..., 10000：
        * 初始化空樹，插入n個隨機值(用rand()產生)。
        * 計算樹高h，用C++的log2(n)計算log₂(n)。
        * 計算比值h/log₂(n)，輸出n、高度和比值。
    * 理論基礎：隨機插入下，BST平均高度約為2*log₂(n)，因此比值應趨近2。

    (4) 分析與圖表
    * 程式輸出n、h和比值，供後續繪圖。
    * 預期：比值隨n增加穩定在2附近，驗證隨機BST的高度特性。

2. 刪除節點

    (1) 資料結構與基礎操作
    * 定義Node結構：包含資料值、左子節點和右子節點指標。
    * 實作insert(Node*, int)函數：與前述相同，遞迴插入鍵值，維持BST性質。

    (2) 刪除節點
    * 實作deleteNode(Node*, int)函數，處理三種情況：
        * 節點不存在：若根節點為空，回傳nullptr。
        * 遞迴搜尋：若鍵值<根節點，遞迴左子樹；若鍵值>根節點，遞迴右子樹。
        * 找到目標節點：
            * 無子節點（葉節點）：直接刪除節點，回傳nullptr。
            * 僅一個子節點：用子節點替換目前節點，刪除目前節點。
            * 兩個子節點：找出右子樹最小節點（中序繼承者），用其值替換目前節點，然後遞迴刪除右子樹中的該最小節點。
        * 輔助函數findMin(Node*)：走訪右子樹最左節點，找出最小值。

#### 3. Finish the exercise 1 in Textbook p.457 

1. 總輸入時間推導

    分解問題，理解緩衝區分配、磁盤存取次數和時間組成，推導 $ t_{\text{input}} $ 公式，考慮重疊但以保守估計為主。

2. 圖表與分析

    代入參數簡化公式，選擇適當 $ k $ 範圍，計算關鍵點並繪製圖表，分析 $ t_{\text{CPU}} \approx t_{\text{input}} $ 的可行性，通過數學推導確認存在性。

## 程式實作

以下為主要程式碼：

#### 1. Max/Min Heap
```cpp
#ifndef MIN_PQ_H
#define MIN_PQ_H

#include <iostream>
#include <stdexcept>
#include <cmath>

        // 定義抽象類別 MinPQ，表示最小優先佇列
        template<class T>
    class MinPQ {
    public:
        virtual ~MinPQ() {}
        // 虛擬解構函數，確保衍生類別的資源正確釋放
        virtual bool IsEmpty() const = 0;
        // 回傳 true 如果優先佇列為空
        virtual const T& Top() const = 0;
        // 回傳最小元素的引用
        virtual void Push(const T&) = 0;
        // 將元素加入優先佇列
        virtual void Pop() = 0;
        // 刪除最小優先級的元素
        virtual int getComparisons() const = 0;
        // 回傳運算中的比較次數
        virtual int getSwaps() const = 0;
        // 回傳運算中的交換次數
    };

    // 定義 MinHeap 類別，繼承自 MinPQ，使用堆積結構實現最小優先佇列
    template<class T>
    class MinHeap : public MinPQ<T> {
    private:
        T* heap;           // 動態陣列儲存堆積元素
        int capacity;      // 堆積的總容量
        int size;          // 目前元素數量
        mutable int comparisons; // 計數比較次數
        mutable int swaps;       // 計數交換次數

        // 私有輔助函數：上移元素以維持堆積性質
        void swim(int index) {
            comparisons = 0;
            swaps = 0;
            while (index > 0 && heap[(index - 1) / 2] > heap[index]) {
                comparisons++; // 計數比較
                // 交換父節點與目前節點
                T temp = heap[index];
                heap[index] = heap[(index - 1) / 2];
                heap[(index - 1) / 2] = temp;
                swaps++; // 計數交換
                index = (index - 1) / 2; // 更新索引為父節點
            }
            if (index > 0) comparisons++; // 計數最後一次失敗的比較
        }

        // 私有輔助函數：下沉元素以維持堆積性質
        void sink(int index) {
            comparisons = 0;
            swaps = 0;
            while (2 * index + 1 < size) {
                int j = 2 * index + 1; // 左子節點
                if (j + 1 < size && heap[j] > heap[j + 1]) {
                    comparisons++; // 計數子節點間的比較
                    j++; // 選擇較小的子節點
                }
                comparisons++; // 計數父節點與子節點的比較
                if (heap[index] <= heap[j]) break; // 若父節點已小於等於子節點，停止
                // 交換父節點與較小的子節點
                T temp = heap[index];
                heap[index] = heap[j];
                heap[j] = temp;
                swaps++; // 計數交換
                index = j; // 更新索引為子節點
            }
        }

    public:
        MinHeap(int cap = 100) : capacity(cap), size(0), comparisons(0), swaps(0) {
            heap = new T[capacity]; // 分配初始容量
        }

        ~MinHeap() {
            delete[] heap; // 釋放動態陣列記憶體
        }

        bool IsEmpty() const override {
            comparisons = 0;
            swaps = 0;
            bool result = (size == 0); // 檢查堆積是否為空
            comparisons = 1; // 一次簡單比較
            return result;
        }

        const T& Top() const override {
            comparisons = 0;
            swaps = 0;
            if (IsEmpty()) throw std::runtime_error("MinHeap is empty");
            comparisons = 1; // 計數 IsEmpty 內的比較
            return heap[0]; // 回傳堆積頂端（最小元素）
        }

        void Push(const T& item) override {
            comparisons = 0;
            swaps = 0;
            if (size == capacity) {
                // 若陣列滿了，擴充容量
                T* newHeap = new T[capacity * 2];
                for (int i = 0; i < size; i++) {
                    newHeap[i] = heap[i];
                }
                delete[] heap;
                heap = newHeap;
                capacity *= 2;
                comparisons++; // 計數容量檢查的比較
            }
            heap[size] = item; // 將新元素加到陣列末端
            swim(size);        // 上移以維持最小堆積性質
            size++;
        }

        void Pop() override {
            comparisons = 0;
            swaps = 0;
            if (IsEmpty()) throw std::runtime_error("MinHeap is empty");
            heap[0] = heap[size - 1]; // 用最後一個元素替換根節點
            size--;
            sink(0); // 下沉以維持最小堆積性質
        }

        int getComparisons() const override {
            return comparisons; // 回傳比較次數
        }

        int getSwaps() const override {
            return swaps; // 回傳交換次數
        }
    };

    // 主程式，測試 MinHeap 並推導時間複雜度
    int main() {
        MinHeap<int> minHeap;

        // 測試 IsEmpty
        std::cout << "測試 IsEmpty:" << std::endl;
        minHeap.IsEmpty();
        std::cout << "比較次數: " << minHeap.getComparisons() << ", 交換次數: " << minHeap.getSwaps() << std::endl;
        std::cout << "推導時間複雜度: 僅涉及單次大小檢查，O(1)" << std::endl;

        // 測試 Top
        std::cout << "\n測試 Top (空堆積會丟出異常，略過):" << std::endl;
        try {
            minHeap.Top();
        }
        catch (const std::runtime_error& e) {
            std::cout << "比較次數: " << minHeap.getComparisons() << ", 交換次數: " << minHeap.getSwaps() << std::endl;
            std::cout << "推導時間複雜度: 僅檢查是否為空，O(1)" << std::endl;
        }

        // 測試 Push，加入多個元素以觀察行為
        std::cout << "\n測試 Push:" << std::endl;
        int values[] = { 5, 2, 7, 1, 3, 8, 4, 6 };
        int n = sizeof(values) / sizeof(values[0]);
        for (int i = 0; i < n; i++) {
            minHeap.Push(values[i]);
            std::cout << "Push " << values[i] << " - 比較次數: " << minHeap.getComparisons()
                << ", 交換次數: " << minHeap.getSwaps() << std::endl;
        }
        std::cout << "推導時間複雜度: 比較和交換次數與堆積高度相關，高度約 log(n)，故為 O(log n)" << std::endl;

        // 測試 Pop，移除元素以觀察行為
        std::cout << "\n測試 Pop:" << std::endl;
        while (!minHeap.IsEmpty()) {
            int top = minHeap.Top();
            minHeap.Pop();
            std::cout << "Pop " << top << " - 比較次數: " << minHeap.getComparisons()
                << ", 交換次數: " << minHeap.getSwaps() << std::endl;
        }
        std::cout << "推導時間複雜度: 比較和交換次數與堆積高度相關，高度約 log(n)，故為 O(log n)" << std::endl;

        return 0;
    }

#endif // MIN_PQ_H
```

#### 2. Binary Search Tree

1. 隨機插入與樹高比值

```cpp
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
```

2. 刪除節點
```cpp
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
    if (!root) return root; //如果空樹直接回傳

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
```

#### 3. Finish the exercise 1 in Textbook p.457 
```Python
import matplotlib.pyplot as plt

# 定義參數
n = 200000  # 總記錄數
S = 2000    # 記憶體容量 (記錄數)
t_s = 0.08  # 尋道時間 (秒)
t_l = 0.02  # 延遲時間 (秒)
t_t = 0.001 # 每條記錄的傳輸時間 (秒/記錄)

# 計算 t_input 的函數
def calculate_t_input(k):
    return (n * (k + 1) / S) * (t_s + t_l) + n * t_t

# 生成 k 的值 (從 2 到 64)
k_values = [2, 10, 20, 30, 40, 50, 60, 64]
t_input_values = [calculate_t_input(k) for k in k_values]

# 繪製圖表
plt.figure(figsize=(10, 6))
plt.plot(k_values, t_input_values, marker='o', color='#4CAF50', label='總輸入時間 (秒)')
plt.fill_between(k_values, t_input_values, color='rgba(76, 175, 80, 0.2)')
plt.xlabel('k (合併路數)')
plt.ylabel('總輸入時間 (秒)')
plt.title('總輸入時間 t_input 對 k 的圖表')
plt.grid(True)
plt.legend()
plt.show()
```

## 效能分析

### 1. Max/Min Heap

* 時間複雜度：程式的時間複雜度為 $O(n log n)$
* 空間複雜度：空間複雜度為 $O(n)$

### 2. Binary Search Tree

1. 隨機插入與樹高比值
    * 時間複雜度：程式的時間複雜度為 $O(N log N)$
    * 空間複雜度：空間複雜度為 $O(N)$

2. 刪除節點
    * 時間複雜度：程式的時間複雜度為 $O(n log n)$
    * 空間複雜度：空間複雜度為 $O(n)$

### 3. Finish the exercise 1 in Textbook p.457 

* 時間複雜度：程式的時間複雜度為 $O(m)$
* 空間複雜度：空間複雜度為 $O(m)$

## 測試與驗證

### 1. Max/Min Heap

#### 測試案例

* 在main()中測試各函數，插入值如5, 2, 7, 1, 3, 8, 4, 6，觀察比較和交換次數。
* 輸出時間複雜度推導，確認IsEmpty和Top為$O(1)$，Push和Pop為 $O(log n)$。

#### 編譯與執行指令

```shell
$ g++ -std=c++17 -o MaxMinHeap MaxMinHeap.cpp
$ ./MaxMinHeap
n = 100, 樹高 = 11, log_2(n) = 6.64386, 比值 = 1.65566
n = 500, 樹高 = 18, log_2(n) = 8.96578, 比值 = 2.00763
n = 900, 樹高 = 24, log_2(n) = 9.81378, 比值 = 2.44554
n = 1300, 樹高 = 22, log_2(n) = 10.3443, 比值 = 2.12678
n = 2300, 樹高 = 24, log_2(n) = 11.1674, 比值 = 2.14911
n = 3300, 樹高 = 28, log_2(n) = 11.6883, 比值 = 2.39557
n = 4300, 樹高 = 27, log_2(n) = 12.0701, 比值 = 2.23693
n = 5300, 樹高 = 26, log_2(n) = 12.3718, 比值 = 2.10156
n = 6300, 樹高 = 27, log_2(n) = 12.6211, 比值 = 2.13927
n = 7300, 樹高 = 30, log_2(n) = 12.8337, 比值 = 2.3376
n = 8300, 樹高 = 28, log_2(n) = 13.0189, 比值 = 2.15072
n = 9300, 樹高 = 30, log_2(n) = 13.183, 比值 = 2.27566

刪除函數時間複雜度：
1. 最好情況：O(log n)，當樹為平衡時。
2. 最壞情況：O(n)，當樹退化為鏈表時（例如，所有節點按順序插入）。
3. 平均情況：O(log n)，因為隨機插入通常使樹保持一定程度的平衡。
```

#### 結論

MaxMinHeap.cpp成功實作了最小優先佇列的抽象類別MinPQ與衍生類別MinHeap，並透過堆積結構實現了IsEmpty、Top、Push和Pop等運算。程式使用動態陣列儲存元素，透過swim和sink函數維護最小堆積性質，確保Push和Pop的時間複雜度為 $O(log n)$，而IsEmpty和Top為 $O(1)$。主程式測試了插入8個固定值並逐一移除，同時追蹤比較和交換次數，驗證了運算的正確性與效率。空間複雜度為 $O(n)$，主要來自堆積陣列。該程式展示了最小堆積的經典應用，適用於需要快速存取最小元素的場景，如任務調度或圖像演算法。雖然測試中$n$為常數，但設計具可擴充性，能處理更大規模的輸入，時間複雜度平均為 $O(n log n)$，展現了堆積資料結構的高效特性。

### 2. Binary Search Tree

#### (1) 隨機插入與樹高比值

#### 測試案例

| n      | n=100 | n=500 | n=1000 | n=2000 | n=3000 | n=4000 | n=5000 | n=6000 | n=7000 | n=8000 | n=9000 | n=10000 |
|--------|-------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
| height | 13 | 18 | 22 | 24 | 28 | 28 | 29 | 32 | 31 | 27 | 31 | 29 |
| ratio  | 1.95669 | 2.00763 | 2.20755 | 2.18863 | 2.42409 | 2.34001 | 2.36008 | 2.54965 | 2.42697 | 2.0824 | 2.35998 | 2.18247 |

#### 編譯與執行指令

```shell
$ g++ -std=c++17 -o BinarySearchTree_a BinarySearchTree_a.cpp
$ ./BinarySearchTree_a
n = 100, height = 13, ratio = 1.95669
n = 500, height = 18, ratio = 2.00763
n = 1000, height = 22, ratio = 2.20755
n = 2000, height = 24, ratio = 2.18863
n = 3000, height = 28, ratio = 2.42409
n = 4000, height = 28, ratio = 2.34001
n = 5000, height = 29, ratio = 2.36008
n = 6000, height = 32, ratio = 2.54965
n = 7000, height = 31, ratio = 2.42697
n = 8000, height = 27, ratio = 2.0824
n = 9000, height = 31, ratio = 2.35998
n = 10000, height = 29, ratio = 2.18247
```

#### 結論

BinarySearchTree_a.cpp模擬了從空二元搜尋樹（BST）開始，插入 $n$ 個隨機值的過程，並計算樹高 $h$ 與 $log₂(n)$ 的比值，驗證隨機BST的高度特性。程式針對 $n = 100, 500, ..., 10000$ 執行，透過insert遞迴插入隨機值，平均時間複雜度 $O(n log n)$，並用height函數計算樹高，時間為 $O(n)$。輸出顯示 $h / log₂(n)$ 趨近於2，符合隨機BST的理論預期。空間複雜度為 $O(n)$，由節點儲存主導。該程式有效展示了隨機插入下BST的平均高度行為，總時間複雜度為 $O(N log N)$，$N$ 為最大 $n$。結果可用於繪圖分析，確認BST在隨機輸入下的平衡趨勢，適用於研究資料結構效能或優化搜尋應用。

#### (2) 刪除節點

#### 測試案例

* 在main()中：
    * 插入節點 {50, 30, 70, 20, 40, 60, 80} 建立 BST。
    * 使用 inorder(Node*) 中序走訪，確認樹的排序性質。
    * 測試刪除：
        * 葉節點（20）
        * 單子節點（30）
        * 雙子節點（50, 80）
        * 每次刪除後，用 height(Node*) 檢查樹高，用中序走訪驗證 BST 性質。
    * 時間複雜度：
        * 搜尋目標節點：O(h)，h 為樹高。
        * 找中序繼承者：O(h)。
        * 總時間複雜度：O(h)，平均情況下隨機 BST 為 O(log n)，最壞情況（偏斜樹）為 O(n)。

#### 編譯與執行指令

```shell
$ g++ -std=c++17 -o BinarySearchTree_b BinarySearchTree_b.cpp
$ ./BinarySearchTree_b
中序走訪 BST（排序後）:
20 30 40 50 60 70 80
目前高度: 3

刪除節點 20（葉節點）...
30 40 50 60 70 80

刪除後 BST 高度: 3

刪除節點 30（有一個子節點）...
40 50 60 70 80

刪除後 BST 高度: 3

刪除節點 50（有兩個子節點）...
40 60 70 80

刪除後 BST 高度: 3

刪除節點 80（有兩個子節點）...
40 60 70

刪除後 BST 高度: 2
```

#### 結論

BinarySearchTree_b.cpp實作了二元搜尋樹（BST）的插入與刪除操作，展示了完整的BST功能。程式透過insert函數構建樹，時間複雜度平均 $O(log n)$，並用deleteNode處理葉節點、單子節點和雙子節點三種刪除情況，輔以findMin尋找中序繼承者，平均時間為 $O(log n)$。主程式插入7個固定值，測試刪除20、30、50和80，配合inorder走訪和height計算，驗證了BST性質與結構變化。空間複雜度為 $O(n)$，由節點與遞迴堆疊構成。總時間複雜度平均 $O(n log n)$，最壞 $O(n²)$。該程式展示了BST的核心運算，適用於排序、搜尋等應用，設計具正確性與可讀性，適合學習與小型資料處理場景。

### 3. Finish the exercise 1 in Textbook p.457 

#### 測試案例

給定參數：
* $t_s=80\text{ms}=0.08\text{s}$
* $t_l=20\text{ms}=0.02\text{s}$
* $n=200,000$
* $m=64$
* $t_t=10^{-3}\text{s/record}=0.001\text{s/record}$
* $S=2000$

#### 編譯與執行指令

```shell
$ python ExternalSort.py
```

#### 結論

是的，總存在一個 $k$ 值，使得  $t_{CPU}\approx t_{input}$，只要 $t_{CPU}$ 落在 $t_{input}$ 的值域內。詳細說明如下節。

## 申論及開發報告

### 繪製高度$log_2n$ 的比率關於n的曲線

圖表顯示的是二元搜尋樹高度與 $ \log_2n $ 之比（即 $ \frac{\text{height}}{\log_2(n)} $）隨 $ n $（插入次數）的變化情況。圖表顯示比值隨 $n$ 增加而波動，最高點約2.4，最低點約 1.8，平均值似乎在 2 附近。理論上，比值應較為穩定接近 2，但圖表中的波動較大，這可能是由於隨機插入導致樹的結構不完全平衡。

![二元搜尋樹高度與 $ \log_2n $ 之比值](https://i.postimg.cc/JhybY9Hg/Figure-1.png)

### Finish the exercise 1 in Textbook p.457

#### (a)外部排序第二階段的總輸入時間

在外部排序的第二階段中，我們使用k-way merge，並且內部記憶體被劃分為輸入/輸出緩衝區，以允許輸入、輸出和CPU處理的重疊。以下是計算總輸入時間 $t_{input}$ 的推導：
    
1.	參數定義： 
    * $n$：總記錄數。
    * $S$：記憶體容量(單位：記錄數)，假設全部可用於輸入/輸出緩衝區。
    * $m$：初始的磁盤run數。
    * $k$：k路合併的路數。
    * $t_s$：磁盤尋道時間（seek time）。
    * $t_l$：磁盤延遲時間（latency time）。
    * $t_t$：每條記錄的傳輸時間（transmission time）。
2.	緩衝區分配： 
    * 內部記憶體被劃分為 $k$ 個輸入緩衝區和若干輸出緩衝區。假設每個輸入緩衝區的大小為 $B$ 記錄，且總記憶體容量為 $S$，則 $B=\frac{S}{k+1}$ 
    
        這裡假設有 $k$ 個輸入緩衝區和1個輸出緩衝區（因為Program 7.21使用一個輸出緩衝區 $ou$，並在步驟7中切換）。
3.	磁盤存取次數： 
    * 每個run的記錄數約為 $\frac{n}{m}$。
    * 每個run需要讀取的block為：$\mathrm{block}=\frac{\frac{n}{m}}{B}=\frac n{m·B}$
    * 總共有 $m$ 個run，因此total block為：$\mathrm{total\ block}=m·\frac n{m·B} =\frac nB$
4.	單次磁盤存取時間： 
    * 每次磁盤讀取包括尋道時間 $t_s$、延遲時間 $t_l$ 和傳輸時間 $t_t\cdot B$ （因為每次讀取 $B$ 條記錄）。
    * 單次讀取時間為：$t_{disk}=t_s+t_l+t_t·B$
5.	總輸入時間：
    * 由於使用了浮動緩衝區（Program 7.21），輸入、輸出和CPU處理可以重疊。理想情況下，輸入時間可能被CPU處理或輸出時間隱藏（重疊）。然而，總輸入時間仍取決於total block和單次磁盤存取時間。
    * 總輸入時間 $t_{input}$ 為：$t_{input}=\mathrm{total}\;\mathrm{block}\cdot(t_s+t_s+t_t\cdot B)$ 
    * 代入 $B=\frac{S}{k+1}$：
    
        $t_{input}=\frac nB\cdot(t_s+t_l+t_t\cdot B)$

        $t_{input}=\frac n{\frac S{k+1}}\cdot(t_s+t_l+t_t\cdot\frac S{k+1})$

        $t_{input}=\frac{n\left(k+1\right)}S(t_s+t_l+t_t\cdot\frac S{k+1})$

    * 簡化後：
        
        $t_{input}=\frac{n\left(k+1\right)}S\cdot(t_s+t_l)+n\cdot t_t$
   
    * 這表示總輸入時間由兩部分組成：尋道和延遲時間的總和（與   相關）以及傳輸時間（與   無關）。

#### (b) 繪製總輸入時間 $t_{input}$ 對 ${k}$ 的圖表並分析

1. 給定參數：
	* $t_s=80\text{ms}=0.08\text{s}$
    * $t_l=20\text{ms}=0.02\text{s}$
    * $n=200,000$
    * $m=64$
    * $t_t=10^{-3}\text{s/record}=0.001\text{s/record}$
    * $S=2000$
	
2. 總輸入時間公式： 代入給定參數到 (a) 的公式：(單位為秒。)

    $t_{input}=\frac{n\left(k+1\right)}S\cdot(t_s+t_l)+n\cdot t_t$

    $t_{input}=\frac{200,000(k+1)}{2000}\cdot(0.008+0.002)+200,000\cdot0.001$

    $t_{input}=100(k+1)\cdot0.1+200$

    $t_{input}=10(k+1)+200$
	
3. 繪製圖表： 我們將繪製 $t_{input}$ 對 $k$ 的圖表，假設 $k$ 的範圍從2到64(因為 $m=64$，所以 $k\le m$)。以下是圖表：

![k從2到64](https://i.postimg.cc/QCq5WDvB/chart.png)
 
4. 分析 $t_{CPU}\approx t_{input}t_{CPU}\approx t_{input}$：
    * 從公式 $t_{input}=10(k+1)+200$ 可見，$t_{input}$ 隨著 $k$ 線性增加。
	* $t_{CPU}$ 是合併所有run所需的CPU時間，且假設與 $k$ 無關（常數）。
	* 是否存在一個 $k$，使得 $t_{CPU}\approx t_{input}$？
	    * 是的，因為 $t_{input}$ 是 $k$ 的線性函數。只要 $t_{CPU}$ 是一個常數，且其值落在 $t_{input}$ 的範圍內（例如，當 $k=2$ 時 $t_{input}=230\mathrm s$，當 $k=64$ 時 $t_{input}=850\mathrm s$），總存在某個 $k$ 值使得 $t_{input}$ 接近 $t_{CPU}$。
	* 例如，若 $t_{CPU}=500\mathrm s$，則：

        $10(k+1)+200=500$

        $10(k+1)=300$

        $k+1=30$

        $k=29$

        當 $k=29$ 時，$t_{input}=10·30+200=500 \mathrm s$，與 $t_{CPU}$ 相等。
	* 結論：是的，總存在一個 $k$ 值，使得  $t_{CPU}\approx t_{input}$，只要 $t_{CPU}$ 落在 $t_{input}$ 的值域內。



