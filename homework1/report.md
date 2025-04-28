# 41243202 41243208

Group 12  
41243202 林沛慧  
41243208 蕭昱糖

## 解題說明

本作業要求使用C++實作Insertion Sort、Quick Sort(median-of-three)、Merge Sort(Iteration)和Heap sort四種演算法，針對最壞情況設計一個高效的複合排序函數(Composite Sort)。需產生最壞情況測試資料(Insertion Sort用Inversion number，Merge Sort逆推最大合併工作量，Quick Sort與Heap sort用隨機排列取最大時間)，測量 $𝑛=500$ 至 $5000$ 的執行時間，分析性能交叉點，並繪製時間圖表。最終設計複合排序函數(Composite Sort)，結合各排序的最佳範圍，提交包含時鐘精確度、資料生成方法、時間表、圖表及完整程式碼的報告，並額外分析平均情況表現。

### 解題策略

1. 用C++實作Insertion Sort、Quick Sort(median-of-three)、Merge Sort(Iteration)和Heap sort，驗證正確性。
2. 使用高精度計時器(std::chrono)測量時鐘精確度 $ \delta $ ，對小時間重複執行取平均，確保1%精確度。
3. 生成最壞情況資料：
    - Insertion Sort：Inversion number
    - Merge Sort：逆推最大合併工作量資料。
    - Quick Sort與Heap sort：用隨機排列生成器，生成至少10個排列，取最大時間。
4. 針對 $n=500, 1000, 2000, 3000, 4000, 5000$ 測量四種排序的最壞情況時間，繪製時間對 $n$ 圖表。
5. 細化 $n$ 範圍，找出各排序性能交叉點，確認 $O(n^2)$ 與 $O(n\log n)$ 行為。
6. 設計複合排序函數(Composite Sort)，根據 $n$ 選擇最佳排序(如小 $n$ 用Insertion Sort，大 $n$ 用Merge Sort)。
7. 測量並繪製複合排序時間，與其他排序比較。
8. 用隨機排列測量平均情況時間，每排列執行一次。

## 程式實作

以下為主要程式碼：

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <chrono>           //處理時間與計時的標準函式庫
#include <algorithm>
#include <cstdlib>
#include <windows.h>
#include <psapi.h>

using namespace std;

//產生n個隨機整數(0~9999)
vector<int> random(int n) 
{
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = rand() % 10000;    //在0~9999之間隨機生成整數
    return arr;
}

//插入排序：一個一個將元素插入已排序好的陣列之中的正確位置
void insertion_sort(vector<int>& arr) 
{
    //做n次
    for (int i = 1; i < arr.size(); i++) 
    {
        int key = arr[i], j = i - 1;
        //只要還沒到開頭，且前面的值都比較大，就一直往前找
        while (j >= 0 && arr[j] > key) 
        {
            arr[j + 1] = arr[j]; j--;   //現在的跟前一個交換
        }
        arr[j + 1] = key;   //現在的值放到正確位置
    }
}

//找pivot值
int median3(vector<int>& arr, int low, int high) 
{
    int mid = (low + high) / 2;
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);      //如果最小值大於中間值，位置交換
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);    //如果最小值大於最大值，位置交換
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);    //如果中間值大於最大值，位置交換
    swap(arr[mid], arr[high - 1]);  //把pivot移到high-1的位置，這樣右邊界high的位置可以保留作暫時空間                        
    return arr[high - 1];           //因為倒數第二個值是median也就是pivot值                              
}

//快速排序法：用pivot分成兩個區塊，小的放左邊、大的放右邊(遞迴)
void quick_sort(vector<int>& arr, int low, int high) 
{
    //區間元素大於10才用快速排序法
    if (low + 10 <= high) 
    {
        int pivot = median3(arr, low, high);    //由另一個副函式找出pivot值
        int i = low, j = high - 1;              //i是從左往右的索引、j是從右往左的索引
        while (true) 
        {
            while (arr[++i] < pivot) {}         //從最左往右找，直到找到比pivot大的
            while (arr[--j] > pivot) {}         //從最右往左找，直到找到比pivot小的
            if (i < j) swap(arr[i], arr[j]);    //將兩個位置錯誤的交換
            else break;                         //如果都對了就結束
        }
        swap(arr[i], arr[high - 1]);            //還沒被分到右邊的值跟pivot交換位置(pivot到中間，左邊比它小，右邊比它大)
        quick_sort(arr, low, i - 1);            //做左半邊(最小到pivot值前)
        quick_sort(arr, i + 1, high);           //做右半邊(pivot值後到最大)
    }
    else insertion_sort(arr);                   //區間元素太少，用插入排序法比較適合
}

//快速排序
void quick_sort(vector<int>& arr)
{
    quick_sort(arr, 0, arr.size() - 1);     //如果只給資料，自動填入0跟最大值
}

//合併排序：分段合併(1、2、4、8...)，合併後要保持由小到大排序的順序
void merge_sort(vector<int>& arr) 
{
    int n = arr.size();
    vector<int> temp(n);    //暫存陣列
    //每次多合併兩倍的元素
    for (int width = 1; width < n; width *= 2) 
    {
        for (int i = 0; i < n; i += 2 * width) 
        {
            int left = i;                   
            int mid = min(i + width, n);        //在兩者之中選擇比較小的當中值
            int right = min(i + 2 * width, n);  //在兩者之中選擇比較小的當右邊界值
            int l = left, r = mid, k = left;
            while (l < mid && r < right)
            {
                if (arr[l] < arr[r])
                {
                    temp[k] = arr[l];  //如果左邊的值比較小，放進temp
                    l++;               //左邊指標往右移動
                }
                else
                {
                    temp[k] = arr[r];  //如果右邊的值比較小，放進temp
                    r++;               //右邊指標往右移動
                }
                k++; //不管哪邊被選中，temp的儲存位置都要往右一格
            }
            while (l < mid) temp[k++] = arr[l++];       //如果左邊還有值，直接搬到陣列
            while (r < right) temp[k++] = arr[r++];     //如果右邊還有值，直接搬到陣列
        }
        arr = temp;         //將暫時陣列裡的值丟給原本的陣列
    }
}

//最大堆
void heapify(vector<int>& arr, int n, int i) 
{
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;    //l是左子節點、r是右子節點
    if (l < n && arr[l] > arr[largest]) largest = l;  //如果左子節點比目前最大值大，就把目前最大值改為左子節點
    if (r < n && arr[r] > arr[largest]) largest = r;  //如果右子節點比目前最大值大，就把目前最大值改為右子節點
    //如果有子節點比父節點大要交換
    if (largest != i) 
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);           //繼續呼叫最大堆副函式，測試剩下的子樹
    }
}

//堆積排序
void heap_sort(vector<int>& arr) 
{
    int n = arr.size();
    //從最下面的子節點開始往上判斷
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) 
    {
        swap(arr[0], arr[i]);       //把最大值放到最後面
        heapify(arr, i, 0);         //把剩下的繼續排成最大堆
    }
}

//挑選最適合的排序
void composite_sort(vector<int>& arr) 
{
    if (arr.size() < 1000)
    {
        cout << "Using Insertion Sort" << endl;
        insertion_sort(arr);                       //如果資料大小小於1000用插入排序法
    }
    else if (arr.size() < 3000)
    {
        cout << "Using Merge Sort" << endl;
        merge_sort(arr);                           //如果資料大小大於1000小於3000用合併排序法
    }
    else
    {
        cout << "Using Quick Sort" << endl;
        quick_sort(arr);                           //如果資料大小大於3000用快速排序法
    }
}

//測量時間
void measure_time(void (*sort_func)(vector<int>&), vector<int> data, string name)
{
    PROCESS_MEMORY_COUNTERS memInfoBefore, memInfoAfter;
    //執行前記憶體
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfoBefore, sizeof(memInfoBefore));
    SIZE_T memory_before = memInfoBefore.WorkingSetSize;
    auto start = chrono::high_resolution_clock::now();      //時間開始
    //執行排序
    sort_func(data);
    auto end = chrono::high_resolution_clock::now();        //時間結束
    //執行後記憶體
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfoAfter, sizeof(memInfoAfter));
    SIZE_T memory_after = memInfoAfter.WorkingSetSize;
    //執行時間
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    //真正使用的記憶體量（可能為負數，如果記憶體釋放得快）
    SIZE_T memory_used = (memory_after > memory_before) ? (memory_after - memory_before) : 0;
    cout << name << " takes " << duration << " μs, ";
    cout << "Memory used during sort: " << memory_used / 1024 << " KB" << endl;
}


int main() {
    int n = 5000; //設定測試資料筆數
    vector<int> arr = random(n);      //因為測試數量會變，所以用動態陣列比較彈性

    //先丟到計時的副函式裡
    measure_time(insertion_sort, arr, "Insertion Sort");
    measure_time(quick_sort, arr, "Quick Sort");
    measure_time(merge_sort, arr, "Merge Sort");
    measure_time(heap_sort, arr, "Heap Sort");
    measure_time(composite_sort, arr, "Composite Sort");

    return 0;
}
```

## 效能分析

1. 時間複雜度：程式的時間複雜度為 $O(n^2)$。
2. 空間複雜度：空間複雜度為 $O(n)$。

## 測試與驗證

### 測試案例

| Insertion Sort | n=500 | n=1000 | n=2000 | n=3000 | n=4000 | n=5000 |
|----------------|-------|--------|--------|--------|--------|--------|
| 執行時間(us)    | 2687  | 10550  | 42553  | 93252  | 176433 | 276384 |
| 記憶體用量(KB)  | 4     | 4      | 4      | 4      | 4      | 4      |

| Quick Sort     | n=500 | n=1000 | n=2000 | n=3000 | n=4000 | n=5000 |
|----------------|-------|--------|--------|--------|--------|--------|
| 執行時間(us)    | 4689  | 14245  | 60052  | 120441 | 192690 | 257055 |
| 記憶體用量(KB)  | 4     | 5      | 6      | 7      | 8      | 9      |

| Merge Sort     | n=500 | n=1000 | n=2000 | n=3000 | n=4000 | n=5000 |
|----------------|-------|--------|--------|--------|--------|--------|
| 執行時間(us)    | 256   | 758    | 2063   | 2516   | 2691   | 5457   |
| 記憶體用量(KB)  | 1.953 | 3.906  | 7.812  | 11.719 | 15.625 | 19.531 |

| Heap Sort      | n=500 | n=1000 | n=2000 | n=3000 | n=4000 | n=5000 |
|----------------|-------|--------|--------|--------|--------|--------|
| 執行時間(us)    | 663   | 1522   | 4522   | 5795   | 760    | 9593   |
| 記憶體用量(KB)  | 4     | 4      | 4      | 4      | 4      | 4      |

| Composite Sort | n=500 | n=1000 | n=2000 | n=3000 | n=4000 | n=5000 |
|----------------|-------|--------|--------|--------|--------|--------|
| 執行時間(us)    | 2884  | 644    | 1557   | 123452 | 214709 | 269408 |
| 記憶體用量(KB)  | 4     | 3.906  | 7.812  | 7      | 8      | 9      |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o sort sort.cpp
$ ./sort
Insertion Sort takes 276384 μs, Memory used during sort: 4 KB
Quick Sort takes 257055 μs, Memory used during sort: 9 KB
Merge Sort takes 5457 μs, Memory used during sort: 20 KB
Heap Sort takes 9593 μs, Memory used during sort: 4 KB
Using Quick Sort
Composite Sort takes 269408 μs, Memory used during sort: 9 KB
```

### 結論

這次實作比較五種排序的演算法，從時間與記憶體兩個方面評估適用情境，總的來說，Merge Sort在時間效率跟穩定性上表現較為突出，而Insertion Sort比較適合處理小型或已排序完的資料，Heap Sort雖實作比較複雜但能保證穩定效率，Composite Sort則在不確定輸入的情況下可表現彈性。若能依照實際資料特性選用適當的演算法，會是非常好的工具。

## 申論及開發報告

### 為什麼程式最後會使用Composite Sort？
在此程式中，最後會使用Composite Sort，是為了測試一種自動選擇最佳排序法的綜合排序策略。Composite Sort根據資料筆數大小，自動決定使用不同的排序演算法：當資料量小於1000筆時，使用Insertion Sort以達到簡單快速的效果；資料量介於1000至3000筆之間時，則改用Merge Sort，以確保在中等資料量下仍能維持穩定且高效的排序；而當資料量超過3000筆時，則採用Quick Sort，以發揮其在大量資料下的平均最佳效能。程式設計這樣的Composite Sort，主要是希望能根據不同資料規模，自動選擇最適合的排序方法，兼顧執行速度與資源使用效率。因此，最後執行Composite Sort，可以驗證這種「智慧選擇排序法」在實務上是否能帶來更好的整體表現。

### 排序法分析
| 排序法          | 適合情況               | 優點         | 缺點        |
|----------------|------------------------|-------------|-------------|
| Insertion Sort | 資料較少(<1000)         | 簡單        | 效率差       |
| Quick Sort     | 資料中大型、一般使用     | 空間複雜度小 | 不穩定       |
| Merge Sort     | 資料較多、要求穩定性     | 時間穩定     | 空間複雜度高 |
| Heap Sort      | 就算資料很差，速度也不慢 | 省空間       | 較繁瑣       |
| Composite Sort | 自動選最快、不確定資料   | 彈性高       | 實作複雜     |

### 資料筆數(n)與執行時間(us)的視覺化圖表
![資料筆數(n)與執行時間(us)的視覺化圖表](https://i.imgur.com/GJxvscf.png)
