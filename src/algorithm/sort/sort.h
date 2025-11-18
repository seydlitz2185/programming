#include <iostream>
#include <math.h>
#define ElementType int
using namespace std;
/// @brief
/// @param a
/// @return

// 打印数组
void print_array(int a[], int N)
{
    for (int i = 0; i < N; ++i)
    {
        cout << a[i] << " ";
    }
    printf("\n");
}

// 交换两个元素，按引用传递
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}


void swim(int a[],int k){
    while((k+1)/2-1 && a[k] < a[(k+1)/2-1]){
        swap(a[k],a[(k+1)/2-1]);
        k = (k+1)/2-1;
    }
}

void sink(int a[],int N,int k){
    int t = k;
    if(((k+1)*2-1)<N && a[(k+1)*2 -1]< a[t]) t = (k+1)*2-1;
    if(((k+1)*2)<N && a[(k+1)*2 ]< a[t]) t = (k+1)*2;
    if(k !=t){
        cout<<"swap"<<k<<" "<<a[k]<<" "<<t<<" "<<a[t]<<endl;
        swap(a[k],a[t]);
        sink(a,N,t);
    }
}
// 所有排序在进行前后都打印一遍数组，用于人工检验排序结果
// 冒泡排序
void BubbleSort(int a[], int N)
{
    print_array(a, N);
    for (int i = 1; i < N; i++)
    {
        int t = i;
        for (int j = i; j > 0; j--)
        {
            if (a[t] < a[j - 1])
            {
                swap(a[t], a[j - 1]);
                t = j - 1;
            }
        }
    }
    print_array(a, N);
    return;
}
// 快速排序
void QuickSortHelper(int a[], int l, int r)
{
    if (l >= r)
        return;
    // 枢轴值永远选择最左边的元素；
    int pivot = a[l], i = l - 1, j = r + 1;
    while (i < j)
    {
        do
            i++;
        while (a[i] < pivot);
        do
            j--;
        while (a[j] > pivot);
        if (i < j)
            swap(a[i], a[j]);
    }
    QuickSortHelper(a, l, j);
    QuickSortHelper(a, j + 1, r);
}
void QuickSort(int a[], int N)
{
    print_array(a, N);
    QuickSortHelper(a, 0, N - 1);
    print_array(a, N);
}

// 简单插入排序
void InsertionSort(int a[], int N)
{
    print_array(a, N);
    for (int i = 1; i < N; ++i)
    {
        for (int j = i; j > 0; --j)
        {
            if (a[j] < a[j - 1])
            {
                swap(a[j], a[j - 1]);
                // printf("\nswap a[%d] and a[%d]\n",j,j-1);
            }
        }
    }
    print_array(a, N);
    return;
}
// 二分插入排序
void BinarySearchInsertionSort(int a[], int N)
{
    print_array(a, N);
    for (int i = 1; i < N; i++)
    {
        int l = 0, r = i;
        while (l < r)
        {
            int mid = (l + r) / 2;
            // printf("%d %d %d\n",l,mid,r);
            if (a[mid] > a[i])
            {
                r = mid;
            }
            else
            {
                l = mid + 1;
            }
        }
        // int temp = a[i];
        for (int j = i; j > l; --j)
            swap(a[j], a[j - 1]);
        //    a[j] = a[j - 1];
        //  a[l] = temp;
    }
    print_array(a, N);
    return;
}
// 希尔排序,待优化
void ShellSortBad(int a[], int N)
{
    print_array(a, N);
    // 排序的步长从N/2开始逐步减半，最后一趟排序是步长为1的选择排序
    int offset = N;
    int length = 1;
    while ((offset /= 2) > 0)
    {
        // length = ceil(N / offset);
        // printf("offset is %d;length is %d\n",offset,length);
        int start = 0;
        while (start < offset)
        {
            //  printf("a[%d]=%d ",start,a[start]);
            for (int i = start + offset; i < N; i += offset)
            {
                // int sentinal = a[i];
                //  printf("a[%d]=%d ",i,a[i]);
                for (int j = i; j - offset >= 0; j -= offset)
                {
                    if (a[j] < a[j - offset])
                        swap(a[j], a[j - offset]);
                    /*
                    if (a[j] < a[j - offset])
                    {
                        a[j] = a[j - offset];
                        a[j - offset] = sentinal;
                //        printf("\nswap a[%d] and a[%d]\n",j,j-offset);
                    }*/
                }
            }
            start++;
            //    printf("\n");
        }
        // print_array(a, N);
    }
    print_array(a, N);
    return;
}
// 希尔排序，借助chatGPT优化
// 优化策略：在最内层循环中，当发现前一个元素大于当前元素时，直接交换即可。
// 相当于最内层使用冒泡排序
void ShellSort(int a[], int N)
{
    print_array(a, N); // 打印原始数组

    int offset = N;           // 初始步长
    while ((offset /= 2) > 0) // 步长逐渐减半
    {
        for (int start = 0; start < offset; start++) // 针对每个子数组进行插入排序
        {
            for (int i = start + offset; i < N; i += offset) // 遍历该子数组
            {
                for (int j = i; j - offset >= 0 && a[j] < a[j - offset]; j -= offset)
                {
                    swap(a[j], a[j - offset]); // 交换元素
                }
            }
        }
    }
    print_array(a, N); // 打印排序后的数组
}

// 选择排序
void SelectSort(int a[], int N)
{
    print_array(a, N);
    for (int i = 0; i < N; i++)
    {
        int min = i;
        for (int j = i; j < N; j++)
        {
            if (a[j] < a[min])
            {
                min = j;
            }
        }
        int temp = a[min];
        for (int j = min; j > i; j--)
        {
            swap(a[j], a[j - 1]);
        }
    }
    print_array(a, N);
}
// 堆排序
void HeapSort(int a[], int N)
{
    print_array(a, N);
    int* b = (int *)malloc(sizeof(int)*N);
    for(int i =0 ;i<N;i++){
        b[i] = a[i];
    }
    for(int i = N/2; i>=0;i--) {
        sink(b,N,i);
    }
    //print_array(b, N);
    for(int i=0;i<N;i++){
        a[i] = b[0];
        b[0] = b[N-i-1];
        sink(b,N-i-1,0);
        //print_array(b, N-i-1);
    }
    print_array(a, N);
}

void MergeSortHelper(int a[], int tmp[], int l, int r)
{
    if (l >= r)
        return; // Base case: no need to merge if subarray has 1 or 0 elements

    int mid = (l + r) / 2;
    MergeSortHelper(a, tmp, l, mid);     // Sort the left half
    MergeSortHelper(a, tmp, mid + 1, r); // Sort the right half

    // Merge the two sorted halves
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r)
    {
        if (a[i] < a[j])
        {
            tmp[k++] = a[i++];
        }
        else
        {
            tmp[k++] = a[j++];
        }
    }

    while (i <= mid)
        tmp[k++] = a[i++];
    while (j <= r)
        tmp[k++] = a[j++];

    for (i = l; i <= r; i++)
        a[i] = tmp[i];
}

void MergeSort(int a[], int N)
{
    print_array(a, N);
    int * tmp = (int*)malloc(sizeof(int)*N); // Temporary array to store merged result
    MergeSortHelper(a, tmp, 0, N - 1);
    print_array(a, N);
}