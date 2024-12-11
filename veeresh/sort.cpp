#include <iostream>
using namespace std;


int Partition(int A[], int l, int r) {
    int p = A[l]; 
    int i = l + 1;
    int j = r;

    while (true) {
        while (i <= r && A[i] <= p) {
            i++;
        }
        while (j >= l && A[j] > p) {
            j--;
        }

        if (i >= j) {
            break;
        }
        swap(A[i], A[j]);
    }
    swap(A[l], A[j]);
    return j;
}

void QuickSort(int A[], int l, int r) {
    if (l < r) {
        int s = Partition(A, l, r); 
        QuickSort(A, l, s - 1);     
        QuickSort(A, s + 1, r);     
    }
}

int main() {
    int A[] = {7, 8, 9, 1, 5};
    int n = sizeof(A) / sizeof(A[0]);

    QuickSort(A, 0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << A[i] << " ";
    }
    return 0;
}
