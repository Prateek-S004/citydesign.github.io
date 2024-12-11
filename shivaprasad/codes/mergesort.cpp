#include <bits/stdc++.h>
using namespace std;

void merge(vector<int> &b, vector<int> &c, vector<int> &a) {
    int i = 0, j = 0, k = 0, p = b.size(), q = c.size();
    while (i < p && j < q) a[k++] = (b[i] <= c[j]) ? b[i++] : c[j++];
    i == p ? copy(c.begin() + j, c.end(), a.begin() + k) : copy(b.begin() + i, b.end(), a.begin() + k);
}

void mergesort(vector<int> &a)
{
    int n = a.size();
    if(n > 1)
    {
        vector<int> b(a.begin(), a.begin() + n/2);
        vector<int> c(a.begin() + n/2, a.end());
        mergesort(b);
        mergesort(c);
        merge(b, c, a);
    }
}

/*

int main()
{
    srand(time(NULL));
    int n = rand() % (20);
    vector<int> a(n);
    for(int &i : a ) i = rand() % 1000;
    cout << "BEFORE SORTING: ";
    for(int i : a) cout << i << ' ';
    cout << "\nAFTER SORTING: ";
    mergesort(a);
    for(int i : a)cout << i << ' ';
}

*/