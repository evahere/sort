//
// Created by Administrator on 2019/11/9.
//

#ifndef SORT_SORTHELPER_H
#define SORT_SORTHELPER_H

#include <iostream>
#include <cassert>
#include <ctime>

using namespace std;

namespace SortHelper {
    // 生成有n个元素的随机数组，每个元素的随机范围为[rangeL,rangeR]
    int *generateRandomArray(int n, int rangeL, int rangeR) {
        assert(rangeL <= rangeR);

        int *arr = new int[n];
        srand(time(NULL));
        for (int i = 0; i < n; i++)
            arr[i] = rand() % (rangeR - rangeL + 1) + rangeL;
        return arr;
    }

    int *generateNearlyOrderArray(int n, int swapTimes)
    {
        int *arr = new int[n];
        for(int i = 0; i < n; i++)
            arr[i] = i;
        srand(time(NULL));
        for(int i = 0; i < swapTimes; i++)
        {
            int posX = rand() % n;
            int posY = rand() % n;
            swap(arr[posX], arr[posY]);
        }

        return arr;
    }

    int *copyIntArray(int arr[], int n) {
        int *a = new int[n];
        copy(arr, arr + n, a);
        return a;
    }

    template<typename T>
    void printArray(T arr[], int n)         // 打印结果
    {
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;

        return;
    }

    template<typename T>
    bool isSorted(T arr[], int n)       // 判断排序是否正确执行
    {
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1])
                return false;
        }
        return true;
    }

    template<typename T>
    void timeSort(const string &sortName, void(*sort)(T[], int), T arr[], int n)  // 测试排序运行时间
    {
        clock_t startTime = clock();
        sort(arr, n);
        clock_t endTime = clock();

        assert(isSorted(arr, n));
        cout << sortName << ": " << double(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
//        assert(isSorted(arr, n));

        return;
    }
}

#endif //SORT_SORTHELPER_H
