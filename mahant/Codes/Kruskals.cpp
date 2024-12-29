#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <map>
#include <string>
using namespace std;

typedef struct node{
    string start;
    string end;
    float weight;
}T;

class Kruskal{
public:
    vector<T> A;                    // List of edges
    vector<T> mst;                  // Minimum spanning tree
    map<string, string> parent;     // Maps each vertex to its parent
    map<string, int> rank;          // Rank for union by rank

    void load_from_file();
    void display(vector<T> a);

    string find(string u);
    void Union(string u, string v);
    void Merge(vector<T>& B, vector<T>& C, vector<T>& A);
    void MergeSort(vector<T>& A);
    void Kruskals_algo();
};

void Kruskal::load_from_file(){
    ifstream file("city_area.txt");

    if (!file){
        cout << "File Not Found\n";
        return;
    }

    string start, end;
    float cost;
    while (file >> start >> end >> cost){
        A.push_back({start, end, cost});
        parent[start] = start; // Initialize parent for each vertex
        parent[end] = end;
        rank[start] = 0;       // Initialize rank for each vertex
        rank[end] = 0;
    }

    file.close();
}

string Kruskal::find(string u){
    if (parent[u] != u){
        parent[u] = find(parent[u]);
    }
    return parent[u];
}

void Kruskal::Union(string u, string v){
    string rootU = find(u);
    string rootV = find(v);

    if (rootU != rootV){
        if (rank[rootU] > rank[rootV]){
            parent[rootV] = rootU;
        } 
        else if (rank[rootU] < rank[rootV]){
            parent[rootU] = rootV;
        } 
        else{
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

void Kruskal::Merge(vector<T>& B, vector<T>& C, vector<T>& A){
    int p = B.size();
    int q = C.size();
    int i = 0, j = 0, k = 0;
    while (i < p && j < q) {
        if (B[i].weight <= C[j].weight){
            A[k] = B[i];
            i = i + 1;
        } 
        else{
            A[k] = C[j];
            j = j + 1;
        }
        k = k + 1;
    }
    while (i < p){
        A[k] = B[i];
        i++;
        k++;
    }
    while (j < q){
        A[k] = C[j];
        j++;
        k++;
    }
}

void Kruskal::MergeSort(vector<T>& A){
    int n = A.size();
    if (n > 1){
        int mid = n / 2;
        vector<T> B(A.begin()      , A.begin() + mid);  // Copy A[0 ... mid-1] to B
        vector<T> C(A.begin() + mid, A.end()        );  // Copy A[mid ... end-1] to C
        MergeSort(B);
        MergeSort(C);
        Merge(B, C, A);
    }
}

void Kruskal::display(vector<T> a){
    for (int i = 0; i < a.size(); i++){
        cout << i + 1 << ") " << a[i].start << " -> " << a[i].end << " = " << a[i].weight << endl;
    }
}

void Kruskal::Kruskals_algo(){
    // Step 1: Sort by edge weights
    MergeSort(A);

    // Step 2: Process edges to construct MST
    int edges = 0;
    for (int i = 0; i < A.size(); i++){
        string u = A[i].start;
        string v = A[i].end;

        if (find(u) != find(v)) { // If u and v are in different sets
            Union(u, v);
            mst.push_back(A[i]);
            edges++;

            // Stops when MST contains n-1 edges
            if (edges == parent.size() - 1) {
                break;
            }
        }
    }
}

int main(){
    Kruskal k;

    k.load_from_file();
    k.Kruskals_algo();

    cout << "Minimum Spanning Tree:" << endl;
    k.display(k.mst);

    float tot_cost = 0.0;
    for (const auto& x : k.mst){
        tot_cost += x.weight;
    }
    cout << endl << "Total cost : " << tot_cost << endl;
    return 0;
}
