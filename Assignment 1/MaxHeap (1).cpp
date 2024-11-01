#include <iostream>
using namespace std;

const int max_size = 10000;

class maxHeap
{
    int A[max_size] = {0};
    int T;

public:
    maxHeap(int *arr, int n)
    {
        T = n;
        for (int i = 0; i < T; i++)
            A[i] = arr[i];
        buildMaxHeap
    }

    void maxHeapify(int index) // O(logn)
    {
        int item = A[index], i = 2 * index + 1;
        while (i < T)
        {
            if (i + 1 < T and A[i + 1] > A[i])
                i++;
            if (A[i] <= item)
                break;
            A[(i - 1) / 2] = A[i];
            i = 2 * i + 1;
        }
        A[(i - 1) / 2] = item;
    }

    void buildMaxHeap() // O(n)
    {
        for (int i = T / 2 - 1; i >= 0; i--)
            maxHeapify(i);
    }

    int extractMaxElement() // O(1)
    {
        return A[0];
    }

    void deleteFromMaxHeap() // O(logn)
    {
        A[0] = A[T - 1];
        T--;
        maxHeapify(0);
    }

    void insert(int element) // O(logn)
    {

        int i = T;
        while (i > 0 and A[(i - 1) / 2] < element)
        {
            A[i] = A[(i - 1) / 2];
            i = (i - 1) / 2;
        }
        A[i] = element;
        T++;
    }

    void heapSort() // O(nlogn)
    {
        buildMaxHeap();
        int len = T;
        for (int i = T - 1; i >= 0; i--)
        {
            int max_ele = extractMaxElement();
            deleteFromMaxHeap();
            A[i] = max_ele;
        }
        cout << "Sorted Array: ";
        for (int i = 0; i < len; i++)
            cout << A[i] << " ";
    }
};

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    maxHeap h1(arr, n);
    h1.heapSort();
    return 0;
}

/*
10
30 6 56 64 16 20 18 9 28 42
*/