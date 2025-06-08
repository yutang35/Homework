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
        // 回傳操作中的比較次數
        virtual int getSwaps() const = 0;
        // 回傳操作中的交換次數
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
