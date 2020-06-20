#include <iostream>
//#include <winbase.h>

#include "SortHelper.h"

using namespace std;


template <typename T>
void selectionSort(T arr[], int n)          // ѡ������
{
    for(int i = 0; i < n;i++)
    {
        // Ѱ��[i,n)���������Сֵ
        int minIndex = i;
        for(int j = i + 1;j < n;j++)
        {
            if(arr[j] < arr[minIndex])
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]);
    }
}

template <typename T>
void insertionSort1(T arr[], int n)          // ��������
{
    for(int i = 1; i < n; i++)
    {
        for(int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
        {
            swap(arr[j], arr[j - 1]);
        }
    }
}

template <typename T>
void insertionSort2(T arr[], int n)          // ��������
{
    for(int i = 1; i < n; i++)
    {
        T tmp = arr[i];     // Ѱ��Ԫ��arr[i]���ʵĲ���λ��
        int j;              // ����Ԫ��tmpӦ�ò����λ��
        for(j = i; j > 0 && arr[j - 1] > tmp; j--)
        {
            arr[j] = arr[j - 1];
        }
        arr[j] = tmp;
    }
}


// �鲢����
// ��arr[l...mid]��arr[mid+1...r]�����ֽ��й鲢
template <typename T>
void __merge(T arr[], int l, int mid, int r)
{
//    T aux[r - l + 1];
    T *aux = new T[r - l + 1];
    for(int i = l; i <= r; i++){
        aux[i - l] = arr[i];
    }
    int i = l, j = mid + 1;
    for(int k = l; k <= r; k++)
    {
        if (i > mid)
        {
            arr[k] = aux[j - l];
            j++;
        }
        else if(j > r)
        {
            arr[k] = aux[i - l];
            i++;
        }
        else if(aux[i - l] < aux[j - l])
        {
            arr[k] = aux[i - l];
            i++;
        }
        else
        {
            arr[k] = aux[j - l];
            j++;
        }
    }
    delete[] aux;
}

// �ݹ�ʹ�ù鲢���򣬶�arr[l...r]�ķ�Χ��������
template <typename T>
void __mergeSort(T arr[], int l, int r)
{
    if(l >= r){
        return;
    }
    int mid = l + (r - l) / 2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid + 1, r);
    if(arr[mid] > arr[mid + 1]) {
        __merge(arr, l, mid, r);
    }
}

template <typename T>
void mergeSort(T arr[], int n)
{
    __mergeSort(arr, 0, n - 1);
}


//��������1.0
//��arr[l...r]���ֽ���partition����
//����p��ʹ��arr[l...p-1] < arr[p] < arr[p+1...r]
template <typename T>
int __partition(T arr[], int l, int r){
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T v = arr[l];
    //arr[l+1...j] < v; arr[j+1...i) > v
    int j = l;
    for(int i = l + 1; i <= r; i++){
        if(arr[i] < v){
            swap(arr[j + 1], arr[i]);
            j++;
        }
    }
    swap(arr[l], arr[j]);
    return j;
}

//��arr[l...r]���ֽ��п�������
template <typename T>
void __quickSort(T arr[], int l, int r){
    if(l >= r){
        return;
    }
//    if(r - l <= 15){
//        insertionSort2(arr, l, r);
//        return;
//    }
    int p = __partition(arr, l, r);
    __quickSort(arr, l, p - 1);
    __quickSort(arr, p + 1, r);
}

template <typename T>
void quickSort(T arr[], int n){
    srand(time(NULL));
    __quickSort(arr, 0, n - 1);
}


//��������2.0 ˫·����
//��arr[l...r]���ֽ���partition����
//����p��ʹ��arr[l...p-1] < arr[p] ; arr[p+1...r] > arr[p]
template <typename T>
int __partition2(T arr[], int l, int r){
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T v = arr[l];
    //arr[l+1...i) <= v; arr[j...r] >= v
    int i = l + 1, j = r;
    while(true){
        while(i <= r && arr[i] < v){
            i++;
        }
        while(j >= l + 1 && arr[j] > v){
            j--;
        }
        if(i > j){
            break;
        }
        swap(arr[i], arr[j]);
        i++;
        j--;
    }
    swap(arr[l], arr[j]);
    return j;
}

//��arr[l...r]���ֽ��п�������
template <typename T>
void __quickSort2(T arr[], int l, int r){
    if(l >= r){
        return;
    }
//    if(r - l <= 15){
//        insertionSort2(arr, l, r);
//        return;
//    }
    int p = __partition2(arr, l, r);
    __quickSort2(arr, l, p - 1);
    __quickSort2(arr, p + 1, r);
}

template <typename T>
void quickSort2(T arr[], int n){
    srand(time(NULL));
    __quickSort2(arr, 0, n - 1);
}


//��������3.0 ��·����
//��arr[l...r]��Ϊ <v; ==v; >v������
//֮��ݹ�� <v; >v�����ּ���������·���Ŵ���
template <typename T>
void __quickSort3Ways(T arr[], int l, int r){
    if(l >= r){
        return;
    }
    //partition
    swap(arr[l], arr[rand() % (r - l + 1) + l]);
    T v = arr[l];
    int lt = l;
    int gt = r + 1;
    int i = l + 1;
    while(i < gt){
        if(arr[i] < v){
            swap(arr[i], arr[lt + 1]);
            lt++;
            i++;
        }
        else if(arr[i] > v){
            swap(arr[i], arr[gt - 1]);
            gt--;
        }
        else{
            i++;
        }
    }
    swap(arr[l], arr[lt]);
    __quickSort3Ways(arr, l, lt - 1);
    __quickSort3Ways(arr, gt, r);
}

template <typename T>
void quickSort3Ways(T arr[], int n){
    srand(time(NULL));
    __quickSort3Ways(arr, 0, n - 1);
}

int main()
{
    int n = 10000000;

    // ����1 һ���Բ���
    cout<<"Test for random array, size = "<<n<<", random range [0, "<<n<<"]"<<endl;
    int *arr = SortHelper::generateRandomArray(n, 0, n);
//    int *arr2 = SortHelper::copyIntArray(arr, n);
//    int *arr3 = SortHelper::copyIntArray(arr, n);
    int *arr4 = SortHelper::copyIntArray(arr, n);
    int *arr5 = SortHelper::copyIntArray(arr, n);
    int *arr6 = SortHelper::copyIntArray(arr, n);
    int *arr7 = SortHelper::copyIntArray(arr, n);

//    SortHelper::timeSort("Selection Sort ", selectionSort, arr, n);
//    SortHelper::timeSort("Insertion Sort1", insertionSort1, arr2, n);
//    SortHelper::timeSort("Insertion Sort2", insertionSort2, arr3, n);
    SortHelper::timeSort("Merge Sort     ", mergeSort, arr4, n);
    SortHelper::timeSort("Quick Sort1.0     ", quickSort, arr5, n);
    SortHelper::timeSort("Quick Sort2.0     ", quickSort2, arr6, n);
    SortHelper::timeSort("Quick Sort3.0     ", quickSort3Ways, arr7, n);

    delete[] arr;
//    delete[] arr2;
//    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;

    cout << endl;

    // ����2 ���Խ������������
    // ���ڽ������������, ����Խ����, InsertionSort��ʱ������Խ������O(n)
    // ���Կ��Գ���, ��swapTimes�Ƚϴ�ʱ, MergeSort����
    // ���ǵ�swapTimesС��һ���̶�, InsertionSort��ñ�MergeSort��
    int swapTimes = 100;
    assert( swapTimes >= 0 );

    cout<<"Test for nearly ordered array, size = "<<n<<", swap time = "<<swapTimes<<endl;
    arr = SortHelper::generateNearlyOrderArray(n, swapTimes);
//    arr2 = SortHelper::copyIntArray(arr, n);
//    arr3 = SortHelper::copyIntArray(arr, n);
    arr4 = SortHelper::copyIntArray(arr, n);
    arr5 = SortHelper::copyIntArray(arr, n);
    arr6 = SortHelper::copyIntArray(arr, n);
    arr7 = SortHelper::copyIntArray(arr, n);

//    SortHelper::timeSort("Selection Sort ", selectionSort, arr, n);
//    SortHelper::timeSort("Insertion Sort1", insertionSort1, arr2, n);
//    SortHelper::timeSort("Insertion Sort2", insertionSort2, arr3, n);
    SortHelper::timeSort("Merge Sort     ", mergeSort, arr4, n);
    SortHelper::timeSort("Quick Sort1.0     ", quickSort, arr5, n);
    SortHelper::timeSort("Quick Sort2.0     ", quickSort2, arr6, n);
    SortHelper::timeSort("Quick Sort3.0     ", quickSort3Ways, arr7, n);

    delete[] arr;
//    delete[] arr2;
//    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;

    cout << endl;

    // ����3 �����ظ����ݱȽ϶������

    cout<<"Test for random array, size = "<<n<<", random range [0, 10]"<<endl;
    arr = SortHelper::generateRandomArray(n, 0, 10);
//    arr2 = SortHelper::copyIntArray(arr, n);
//    arr3 = SortHelper::copyIntArray(arr, n);
    arr4 = SortHelper::copyIntArray(arr, n);
    arr5 = SortHelper::copyIntArray(arr, n);
    arr6 = SortHelper::copyIntArray(arr, n);
    arr7 = SortHelper::copyIntArray(arr, n);

//    SortHelper::timeSort("Selection Sort ", selectionSort, arr, n);
//    SortHelper::timeSort("Insertion Sort1", insertionSort1, arr2, n);
//    SortHelper::timeSort("Insertion Sort2", insertionSort2, arr3, n);
    SortHelper::timeSort("Merge Sort     ", mergeSort, arr4, n);
//    SortHelper::timeSort("Quick Sort1.0     ", quickSort, arr5, n);
    SortHelper::timeSort("Quick Sort2.0     ", quickSort2, arr6, n);
    SortHelper::timeSort("Quick Sort3.0     ", quickSort3Ways, arr7, n);

    delete[] arr;
//    delete[] arr2;
//    delete[] arr3;
    delete[] arr4;
    delete[] arr5;
    delete[] arr6;
    delete[] arr7;

    return 0;
}