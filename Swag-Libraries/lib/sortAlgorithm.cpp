#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>

void quickSort(std::vector<int> &a, int left, int right)
{
    if(left < right)
    {
        int pivot = a[left];
        int low = left, high = right;

        // 把数组分成两半，左边的小于pivot，右边的大于pivot
        while(low < high)
        {
            while(high > low && a[high] > pivot)
            {
                high--;
            }
            if(low < high)// 1
                a[low] = a[high];

            while(low < high && a[low] < pivot)
            {
                low++;
            }
            if(low < high)// 2
                a[high] = a[low];
        }
        // 因为你不知道在哪个while之后结束，所以1，2两处都要加一个判断。

        a[low] = pivot;

        quickSort(a, left, low-1);
        quickSort(a, low+1, right);
    }
}


void insertSort(std::vector<int> &a)
{
    for(int i = 1; i<a.size(); i++)
    {
        for(int j = i-1; j>=0 && a[j+1]<a[j]; j--)
            std::swap(a[j+1],a[j]);
    }
}

void maxHeapfix(std::vector<int> &a, int heapSize, int index)
{
    int iMax = index;
    int iLeft = 2*index + 1;
    int iRight = 2*index + 2;


    if(iLeft < heapSize && a[iLeft]>a[iMax])
        iMax = iLeft;
    if(iRight < heapSize && a[iRight]>a[iMax])
        iMax = iRight;
    

    if(iMax != index)
    {
        std::swap(a[iMax], a[index]);
        maxHeapfix(a, heapSize, iMax);
    }
}

void heapSort(std::vector<int> &a)
{
    int n = a.size();

    // 构建最大堆，数组小于3就会直接跳过这里
    for(int i = n/2-1; i>=0; i--)
    {
        maxHeapfix(a, n, i);
    }


    // 排序
    for(int i = n-1; i>0; i--)
    {
        std::swap(a[0], a[i]);
        maxHeapfix(a, i, 0);
    }
}


void shellSort(std::vector<int> &a)
{
    int n = a.size();


    for(int gap = n/2; gap>0; gap/=2)
        for(int i = gap; i < n; i++)
            for(int j = i-gap; j>=0 && a[j+gap]<a[j]; j-=gap)
                std::swap(a[j+gap], a[j]);
}



void merge(std::vector<int> &a, int l, int m, int r)
{
    // 用一个辅助数组
    std::vector<int> tmp;
    int i = l, j = m+1;

    
    while(i<=m && j<=r)
    {
        if(a[i] <= a[j])
            tmp.push_back(a[i++]);
        else
            tmp.push_back(a[j++]);
    }

    // 拷贝剩下的数据
    while(i<=m)
        tmp.push_back(a[i++]);
    while(j<=r)
        tmp.push_back(a[j++]);

    for(int i = 0; i<tmp.size(); i++)
        a[l+i] = tmp[i];

}

void mergeSort(std::vector<int> &a, int l, int r)
{
    if(l<r)
    {
        int m = l + (r-l)/2;


        mergeSort(a, l, m);
        mergeSort(a, m+1, r);
        merge(a, l, m, r);
    }

}


void bubbleSort(std::vector<int> &a)
{
    for(int i = 0; i<a.size(); i++)
        for(int j = 1; j<a.size()-i; j++)
            if(a[j] > a[j-1])    
                std::swap(a[j], a[j-1]);
}

int main()
{
    {
        std::vector<int> a = {3,0,1,8,7,2,5,4,9,6};
        std::vector<int> b = {3,0,1,8,7,2,5,4,9,6};
        std::sort(b.begin(),b.end());
        quickSort(a, 0, a.size()-1);
        assert(a == b);
    }

    {
        std::vector<int> a = {3,0,1,8,7,2,5,4,9,6};
        std::vector<int> b = {3,0,1,8,7,2,5,4,9,6};
        std::sort(b.begin(),b.end());
        insertSort(a);
        assert(a == b);
    }

    {
        std::vector<int> a = {3,0,1,8,7,2,5,4,9,6};
        std::vector<int> b = {3,0,1,8,7,2,5,4,9,6};
        std::sort(b.begin(),b.end());
        heapSort(a);
        assert(a == b);
    }


    {
        std::vector<int> a = {3,0,1,8,7,2,5,4,9,6};
        std::vector<int> b = {3,0,1,8,7,2,5,4,9,6};
        std::sort(b.begin(),b.end());
        shellSort(a);
        assert(a == b);
    }


    {
        std::vector<int> a = {3,0,1,8,7,2,5,4,9,6};
        std::vector<int> b = {3,0,1,8,7,2,5,4,9,6};
        std::sort(b.begin(),b.end());
        mergeSort(a, 0, a.size()-1);
        assert(a == b);
    }


    
    {
        std::vector<int> a = {3,0,1,8,7,2,5,4,9,6};
        std::vector<int> b = {3,0,1,8,7,2,5,4,9,6};
        std::sort(b.begin(),b.end());
        bubbleSort(a, 0, a.size()-1);
        assert(a == b);
    }
}