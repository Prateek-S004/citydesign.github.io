#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cctype>
#include <string>
using namespace std;

typedef struct tree{
    int start;
    int end;
    int weight;
}T;

class krusikal{
    public:
        int n;
        vector<T> A;
        vector<T> mst;
        vector<int> arr;

        void read_arr();
        void display(vector<T> a);

        int find(int u, int v);
        void Union(int u, int v);
        void Merge(vector<T>& B, vector<T>& C, vector<T>& A);
        void MergeSort(vector<T>& A);
        void Krusikals_algo();
};

void krusikal::read_arr(){
    cout << "Enter number of edges : ";
    cin >> n;
    int s,e,w;
    for(int i = 0 ; i < n ; i++){
        cout << i+1 << ":" << endl;
        cout << "Enter starting node : ";
        cin >> s;
        cout << "Enter ending node : ";
        cin >> e;
        cout << "Enter weight of edge : ";
        cin >> w;
        cout << endl;

        A.push_back(T{s,e,w});
        cin.ignore();
    }
}

int krusikal::find(int u, int v){
    if(arr[u] == arr[v]) return 1;
    else return 0;
}

void krusikal::Union(int u, int v){
    int temp = arr[u];
    for(int i = 0 ; i < arr.size() ; i++){
        if(arr[i] == temp){
            arr[i] = arr[v];
        }
    }
}

void krusikal::Merge(vector<T>& B, vector<T>& C, vector<T>& A) {
    int p = B.size();
    int q = C.size();
    int i = 0, j = 0, k = 0;
    while(i < p && j < q){
        if(B[i].weight <= C[j].weight){
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

void krusikal::MergeSort(vector<T>& A) {
    int n = A.size();
    int mid = n/2;
    if(n > 1){
        vector<T> B(A.begin()       , A.begin() + mid); // copy A[0   ... n/2 -1] to B[0 ... n/2 -1]
        vector<T> C(A.begin() + mid , A.end()        ); // copy A[n/2 ... n -1  ] to C[0 ... n/2 -1]
        MergeSort(B);
        MergeSort(C);
        Merge(B,C,A);
    }
}

void krusikal::display(vector<T> a){
    for(int i = 0 ; i < a.size() ; i++){
        cout << i+1 << ") " << a[i].start << " -> " << a[i].end << " = " << a[i].weight << endl;
    }
}

void krusikal::Krusikals_algo(){
    // Step1 : Sort by edge weights
    MergeSort(A);

    // Step2 : Initialize array with vertices
    arr.resize(n+1 + 1); // n+1 represents number of vertices
    for (int i = 0; i <= n+1; i++){
        arr[i] = i;
    }

    // Step 3: using find and union
    int i = 0, count = 0;
    while(count < arr.size() - 1 && i < n){
        if(!find(A[i].start, A[i].end)){
            Union(A[i].start, A[i].end);
            mst.push_back(A[i]);
            count++;
        }
        i++;
    }
}

int main(){
    krusikal k;

    k.read_arr();
    cout << "Before sorting : " << endl;
    k.display(k.A);

    k.MergeSort(k.A);
    cout << "After sorting : " << endl;
    k.display(k.A);

    k.Krusikals_algo();
    cout << "Applying krusikal's Algorithm : " << endl;
    cout << "Root of minimum spanning tree is : " << k.arr[0] << endl;
    k.display(k.mst);
}
