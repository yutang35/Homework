#include <iostream>
#include <vector>
#include <string>
#include <chrono>           //�B�z�ɶ��P�p�ɪ��зǨ禡�w
#include <algorithm>
#include <cstdlib>
#include <windows.h>
#include <psapi.h>


using namespace std;

//����n���H�����(0~9999)
vector<int> random(int n) 
{
    vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = rand() % 10000;    //�b0~9999�����H���ͦ����
    return arr;
}

//���J�ƧǡG�@�Ӥ@�ӱN�������J�w�ƧǦn���}�C���������T��m
void insertion_sort(vector<int>& arr) 
{
    //��n��
    for (int i = 1; i < arr.size(); i++) 
    {
        int key = arr[i], j = i - 1;
        //�u�n�٨S��}�Y�A�B�e�����ȳ�����j�A�N�@�����e��
        while (j >= 0 && arr[j] > key) 
        {
            arr[j + 1] = arr[j]; j--;   //�{�b����e�@�ӥ洫
        }
        arr[j + 1] = key;   //�{�b���ȩ�쥿�T��m
    }
}

//��pivot��
int median3(vector<int>& arr, int low, int high) 
{
    int mid = (low + high) / 2;
    if (arr[low] > arr[mid]) swap(arr[low], arr[mid]);      //�p�G�̤p�Ȥj�󤤶��ȡA��m�洫
    if (arr[low] > arr[high]) swap(arr[low], arr[high]);    //�p�G�̤p�Ȥj��̤j�ȡA��m�洫
    if (arr[mid] > arr[high]) swap(arr[mid], arr[high]);    //�p�G�����Ȥj��̤j�ȡA��m�洫
    swap(arr[mid], arr[high - 1]);  //��pivot����high-1����m�A�o�˥k���high����m�i�H�O�d�@�ȮɪŶ�                        
    return arr[high - 1];           //�]���˼ƲĤG�ӭȬOmedian�]�N�Opivot��                              
}

//�ֳt�ƧǪk�G��pivot������Ӱ϶��A�p������B�j����k��(���j)
void quick_sort(vector<int>& arr, int low, int high) 
{
    //�϶������j��10�~�Χֳt�ƧǪk
    if (low + 10 <= high) 
    {
        int pivot = median3(arr, low, high);    //�ѥt�@�Ӱƨ禡��Xpivot��
        int i = low, j = high - 1;              //i�O�q�����k�����ޡBj�O�q�k����������
        while (true) 
        {
            while (arr[++i] < pivot) {}         //�q�̥����k��A�������pivot�j��
            while (arr[--j] > pivot) {}         //�q�̥k������A�������pivot�p��
            if (i < j) swap(arr[i], arr[j]);    //�N��Ӧ�m���~���洫
            else break;                         //�p�G����F�N����
        }
        swap(arr[i], arr[high - 1]);            //�٨S�Q����k�䪺�ȸ�pivot�洫��m(pivot�줤���A����񥦤p�A�k��񥦤j)
        quick_sort(arr, low, i - 1);            //�����b��(�̤p��pivot�ȫe)
        quick_sort(arr, i + 1, high);           //���k�b��(pivot�ȫ��̤j)
    }
    else insertion_sort(arr);                   //�϶������Ӥ֡A�δ��J�ƧǪk����A�X
}

//�ֳt�Ƨ�
void quick_sort(vector<int>& arr)
{
    quick_sort(arr, 0, arr.size() - 1);     //�p�G�u����ơA�۰ʶ�J0��̤j��
}

//�X�ֱƧǡG���q�X��(1�B2�B4�B8...)�A�X�֫�n�O���Ѥp��j�ƧǪ�����
void merge_sort(vector<int>& arr) 
{
    int n = arr.size();
    vector<int> temp(n);    //�Ȧs�}�C
    //�C���h�X�֨⭿������
    for (int width = 1; width < n; width *= 2) 
    {
        for (int i = 0; i < n; i += 2 * width) 
        {
            int left = i;                   
            int mid = min(i + width, n);        //�b��̤�����ܤ���p������
            int right = min(i + 2 * width, n);  //�b��̤�����ܤ���p����k��ɭ�
            int l = left, r = mid, k = left;
            while (l < mid && r < right)
            {
                if (arr[l] < arr[r])
                {
                    temp[k] = arr[l];  //�p�G���䪺�Ȥ���p�A��itemp
                    l++;               //������Щ��k����
                }
                else
                {
                    temp[k] = arr[r];  //�p�G�k�䪺�Ȥ���p�A��itemp
                    r++;               //�k����Щ��k����
                }
                k++; //���ޭ���Q�襤�Atemp���x�s��m���n���k�@��
            }
            while (l < mid) temp[k++] = arr[l++];       //�p�G�����٦��ȡA�����h��}�C
            while (r < right) temp[k++] = arr[r++];     //�p�G�k���٦��ȡA�����h��}�C
        }
        arr = temp;         //�N�Ȯɰ}�C�̪��ȥᵹ�쥻���}�C
    }
}

//�̤j��
void heapify(vector<int>& arr, int n, int i) 
{
    int largest = i, l = 2 * i + 1, r = 2 * i + 2;    //l�O���l�`�I�Br�O�k�l�`�I
    if (l < n && arr[l] > arr[largest]) largest = l;  //�p�G���l�`�I��ثe�̤j�Ȥj�A�N��ثe�̤j�ȧאּ���l�`�I
    if (r < n && arr[r] > arr[largest]) largest = r;  //�p�G�k�l�`�I��ثe�̤j�Ȥj�A�N��ثe�̤j�ȧאּ�k�l�`�I
    //�p�G���l�`�I����`�I�j�n�洫
    if (largest != i) 
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);           //�~��I�s�̤j��ƨ禡�A���ճѤU���l��
    }
}

//��n�Ƨ�
void heap_sort(vector<int>& arr) 
{
    int n = arr.size();
    //�q�̤U�����l�`�I�}�l���W�P�_
    for (int i = n / 2 - 1; i >= 0; i--) 
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) 
    {
        swap(arr[0], arr[i]);       //��̤j�ȩ��̫᭱
        heapify(arr, i, 0);         //��ѤU���~��Ʀ��̤j��
    }
}

//�D��̾A�X���Ƨ�
void composite_sort(vector<int>& arr) 
{
    if (arr.size() < 1000)
    {
        cout << "Using Insertion Sort" << endl;
        insertion_sort(arr);                       //�p�G��Ƥj�p�p��1000�δ��J�ƧǪk
    }
    else if (arr.size() < 3000)
    {
        cout << "Using Merge Sort" << endl;
        merge_sort(arr);                           //�p�G��Ƥj�p�j��1000�p��3000�ΦX�ֱƧǪk
    }
    else
    {
        cout << "Using Quick Sort" << endl;
        quick_sort(arr);                           //�p�G��Ƥj�p�j��3000�Χֳt�ƧǪk
    }
}

//���q�ɶ�
void measure_time(void (*sort_func)(vector<int>&), vector<int> data, string name)
{
    PROCESS_MEMORY_COUNTERS memInfoBefore, memInfoAfter;
    //����e�O����
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfoBefore, sizeof(memInfoBefore));
    SIZE_T memory_before = memInfoBefore.WorkingSetSize;
    auto start = chrono::high_resolution_clock::now();      //�ɶ��}�l
    //����Ƨ�
    sort_func(data);
    auto end = chrono::high_resolution_clock::now();        //�ɶ�����
    //�����O����
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfoAfter, sizeof(memInfoAfter));
    SIZE_T memory_after = memInfoAfter.WorkingSetSize;
    //����ɶ�
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
    //�u���ϥΪ��O����q�]�i�ର�t�ơA�p�G�O��������o�֡^
    SIZE_T memory_used = (memory_after > memory_before) ? (memory_after - memory_before) : 0;
    cout << name << " takes " << duration << " �gs, ";
    cout << "Memory used during sort: " << memory_used / 1024 << " KB" << endl;
}


int main() {
    int n = 5000; //�]�w���ո�Ƶ���
    vector<int> arr = random(n);      //�]�����ռƶq�|�ܡA�ҥH�ΰʺA�}�C����u��

    //�����p�ɪ��ƨ禡��
    measure_time(insertion_sort, arr, "Insertion Sort");
    measure_time(quick_sort, arr, "Quick Sort");
    measure_time(merge_sort, arr, "Merge Sort");
    measure_time(heap_sort, arr, "Heap Sort");
    measure_time(composite_sort, arr, "Composite Sort");

    return 0;
}