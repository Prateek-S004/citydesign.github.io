#include <bits/stdc++.h>
#include <fstream>


using namespace std;

double calculateDistance(pair<int, int> userCoord, pair<int, int> entityCoord) {
    return sqrt(pow(userCoord.first - entityCoord.first, 2) + pow(userCoord.second - entityCoord.second, 2));
}

bool bfss(const string text, const string pattern) {
    int n = text.size();
    int m = pattern.size();

    for (int i = 0; i <= n - m; i++) {
        bool match = true;

        for (int j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) {
                match = false;
                break;
            }
        }

        if (match) {
            return true;
        }
    }

    return false;
}

void InsertionSort(vector<tuple<string, pair<int, int>, double>>& entities) {
    int n = entities.size();
    for (int i = 1; i < n; i++) {
        auto key = entities[i];
        int j = i - 1;
        while (j >= 0 && get<0>(entities[j]) > get<0>(key)) {
            entities[j + 1] = entities[j];
            j--;
        }
        entities[j + 1] = key;
    }
}

void Merge(vector<tuple<string, pair<int, int>, double>>& B, vector<tuple<string, pair<int, int>, double>>& C, vector<tuple<string, pair<int, int>, double>>& A) {
    int p = B.size();
    int q = C.size();
    int i = 0, j = 0, k = 0;
    while (i < p && j < q) {
        if (get<2>(B[i]) <= get<2>(C[j])) {
            A[k++] = B[i++];
        } else {
            A[k++] = C[j++];
        }
    }
    while (i < p) A[k++] = B[i++];
    while (j < q) A[k++] = C[j++];
}

void MergeSort(vector<tuple<string, pair<int, int>, double>>& A) {
    int n = A.size();
    if (n > 1) {
        int mid = n / 2;
        vector<tuple<string, pair<int, int>, double>> B(A.begin(), A.begin() + mid);
        vector<tuple<string, pair<int, int>, double>> C(A.begin() + mid, A.end());
        MergeSort(B);
        MergeSort(C);
        Merge(B, C, A);
    }
}

int Partition(vector<tuple<string, pair<int, int>, double>>& entities, int l, int r, pair<int, int> userCoord) {
    double pivot = calculateDistance(userCoord, get<1>(entities[l]));
    int i = l;
    int j = r + 1;
    while (true) {
        while (i < r && calculateDistance(userCoord, get<1>(entities[++i])) <= pivot);
        while (j > l && calculateDistance(userCoord, get<1>(entities[--j])) >= pivot);
        if (i >= j) break;
        swap(entities[i], entities[j]);
    }
    swap(entities[l], entities[j]);
    return j;
}

void QuickSort(vector<tuple<string, pair<int, int>, double>>& entities, int l, int r, pair<int, int> userCoord) {
    if (l < r) {
        int s = Partition(entities, l, r, userCoord);
        QuickSort(entities, l, s - 1, userCoord);
        QuickSort(entities, s + 1, r, userCoord);
    }
}

vector<tuple<string, pair<int, int>, double>> readCityData(const string& filename) {
    vector<tuple<string, pair<int, int>, double>> entities;
    ifstream file(filename);
    string name;
    int x, y;
    double rating;

    if (file.is_open()) {
        while (file >> name >> x >> y >> rating) {
            entities.push_back({name, {x, y}, rating});
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }

    return entities;
}

int main() {
    
    vector<tuple<string, pair<int, int>, double>> entities = readCityData("city.txt");

    while (true) {
        cout << "\nCity Search Engine Menu:\n";
        cout << "1. Search by pattern in entity name\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            string pattern;
            cout << "Enter the pattern to search: ";
            cin >> pattern;

            vector<tuple<string, pair<int, int>, double>> matchingEntities;

            for (const auto& entity : entities) {
                if (bfss(get<0>(entity), pattern)) {
                    matchingEntities.push_back(entity);
                }
            }

            if (matchingEntities.empty()) {
                cout << "No matches found for pattern: " << pattern << endl;
                continue;
            }

            cout << "Matching entities found:\n";
            for (const auto& entity : matchingEntities) {
                cout << get<0>(entity) << endl;
            }

            bool sortAgain = true;
            while (sortAgain) {
                cout << "How would you like to sort the results?\n";
                cout << "1. Lexicographic order\n";
                cout << "2. Rating order\n";
                cout << "3. Distance from user\n";
                cout << "Enter your choice: ";

                cin >> choice;

                if (choice == 1) {
                    InsertionSort(matchingEntities);
                    cout << "Sorted by Lexicographic order:\n";
                    for (const auto& entity : matchingEntities) {
                        cout << get<0>(entity) << endl;
                    }
                } else if (choice == 2) {
                    MergeSort(matchingEntities);
                    cout << "Sorted by Rating:\n";
                    for (const auto& entity : matchingEntities) {
                        cout << get<0>(entity) << " Rating: " << get<2>(entity) << endl;
                    }
                } else if (choice == 3) {
                    pair<int, int> userCoord;
                    cout << "Enter your coordinates (x y): ";
                    cin >> userCoord.first >> userCoord.second;
                    QuickSort(matchingEntities, 0, matchingEntities.size() - 1, userCoord);
                    cout << "Sorted by Distance from (" << userCoord.first << ", " << userCoord.second << "):\n";
                    for (const auto& entity : matchingEntities) {
                        double dist = calculateDistance(userCoord, get<1>(entity));
                        cout << get<0>(entity) << " Distance: " << dist << endl;
                    }
                } else {
                    cout << "Invalid choice!\n";
                    continue;
                }

                char sortChoice;
                cout << "Would you like to sort the results again (Y/N)? ";
                cin >> sortChoice;
                if (sortChoice == 'N' || sortChoice == 'n') {
                    sortAgain = false;
                }
            }

            char contChoice;
            cout << "Press 'C' to continue searching or 'E' to exit: ";
            cin >> contChoice;

            if (contChoice == 'E' || contChoice == 'e') {
                cout << "Exiting...\n";
                break;
            }

        } else if (choice == 2) {


            
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}
