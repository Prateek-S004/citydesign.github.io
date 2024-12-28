#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cctype>
#include <string>
using namespace std;

void display(vector<int> A) {
    int n = A.size();
    for (int i = 0 ; i < n ; i++) {
        cout << A[i] << " ";
    }
    cout << endl << endl;
}

// Bubble Sort
void BubbleSort(vector<int>& A) {
    int n = A.size();
    for(int i = 0 ; i <= n-1 ; i++){
        for(int j = 0 ; j <= n-2-i ; j++){
            if(A[j] > A[j+1]){
                swap(A[j], A[j+1]);
            }
        }
    }
}

// Selection Sort
void SelectionSort(vector<int>& A) {
    int n = A.size();
    for(int i = 0 ; i <= n-2 ; i++){
        int min = i;
        for(int j = i+1 ; j <= n-1 ; j++){
            if(A[j] < A[min]){
                min = j;
            }
        }
        swap(A[i], A[min]);
    }
}

// Insertion Sort
void InsertionSort(vector<int>& A) {
    int n = A.size();
    for(int i = 1 ; i <= n-1 ; i++){
        int V = A[i];
        int j = i-1;
        while(j >= 0 && A[j] > V){
            A[j+1] = A[j];
            j = j-1;
        }
        A[j+1] = V;
    }
}

// Merge Sort
void Merge(vector<int>& B, vector<int>& C, vector<int>& A) {
    int p = B.size();
    int q = C.size();
    int i = 0, j = 0, k = 0;
    while(i < p && j < q){
        if(B[i] <= C[j]){
            A[k] = B[i];
            i = i+1;
        }
        else{
            A[k] = C[j];
            j = j+1;
        }
        k = k+1;
    }
    if(i == p){
        // copy C[j ... q - 1] to A[k ... p + q - 1]
        while (j <= q-1) {
            A[k] = C[j];
            j++;
            k++;
        }
    }
    else{
        // copy B[i ... p - 1] to A[k ... p + q - 1]
        while (i <= p-1) {
            A[k] = B[i];
            i++;
            k++;
        }
    }
}
void MergeSort(vector<int>& A) {
    int n = A.size();
    int mid = n/2;
    if(n > 1){
        vector<int> B(A.begin()       , A.begin() + mid); // copy A[0   ... n/2 -1] to B[0 ... n/2 -1]
        vector<int> C(A.begin() + mid , A.end()        ); // copy A[n/2 ... n -1  ] to C[0 ... n/2 -1]
        MergeSort(B);
        MergeSort(C);
        Merge(B,C,A);
    }
}

// Quick Sort
int Partition(vector<int>& A, int l, int r) {
    int p = A[l];
    int i = l;
    int j = r+1;
    while(i <= j){
        while(A[i] <= p){
            i++;
        }
        while(A[j] >= p){
            j--;
        }
        swap(A[i], A[j]);
    }
    swap(A[i], A[j]);
    swap(A[l], A[j]);
    return j;
}
void QuickSort(vector<int>& A, int l, int r) {
    if(l < r){
        int s = Partition(A, l, r);
        QuickSort(A, l  , s-1);
        QuickSort(A, s+1, r  );
    }
}

// Heap Sort
void HeapBottomUp(vector<int>& H) {
    int n = H.size();
    for (int i = n / 2 ; i >= 1; i--) {
        int k = i;
        int v = H[k];
        bool heap = false;

        while (!heap && 2 * k + 1 < n) { // Ensure there is at least one child
            int j = 2 * k + 1;           // Left child index
            if (j + 1 < n ) { // If right child exists and is greater
                if(H[j] < H[j + 1]){
                    j++;
                } 
            }
            if (v >= H[j]) {
                heap = true;             // If parent is greater or equal, stop
            } else {
                H[k] = H[j];             // Move the larger child up
                k = j;                   // Move down to the child's position
            }
        }
        H[k] = v;                        // Place the original value in the correct position
    }
}


int main() {
    srand(time(0));

    int n;
    cout << "Enter number of elements in a array : ";
    cin >> n;

    vector<int> A;
    for (int i = 0 ; i < n ; i++) { // Add values 1 to n in order
        A.push_back(i + 1); 
    }
    for (int i = 0 ; i < n ; i++) { // shuffle the numbers
        int j = rand() % (i + 1);
        swap(A[i], A[j]);
    }

    cout << "Array with " << n << "elements before sorting : " << endl;
    display(A);

    cout << "1 - Bubble Sort" << endl;
    cout << "2 - Selection Sort" << endl;
    cout << "3 - Insertion Sort" << endl;
    cout << "4 - Merge Sort" << endl;
    cout << "5 - Quick Sort" << endl;
    cout << "6 - Heap Sort (not done)" << endl;
    cout << endl;

    int choice;
    cout << "Enter choice : ";
    cin >> choice;
    switch (choice)
    {
        case 1:{
            BubbleSort(A);
            cout << "Sorting using Bubble Sort : " << endl;
            display(A);
            break;
        }
        case 2:{
            SelectionSort(A);
            cout << "Sorting using Selection Sort : " << endl;
            display(A);
            break;
        }
        case 3:{
            InsertionSort(A);
            cout << "Sorting using Insertion Sort : " << endl;
            display(A);
            break;
        }
        case 4:{
            MergeSort(A);
            cout << "Sorting using Merge Sort : " << endl;
            display(A);
            break;
        }
        case 5:{
            QuickSort(A, 0, A.size() - 1);
            cout << "Sorting using Quick Sort : " << endl;
            display(A);
            break;
        }
        case 6:{
            //HeapSort(A);
            cout << "Sorting using Heap Sort : " << endl;
            display(A);
            break;
        }
        default: exit(0);
    }
    return 0;
}
