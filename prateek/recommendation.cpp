#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

typedef struct Recommendation {
    char recommendationName[100];
    int visitors;
} Recommendation;

class RecommendationData {
public:
    char locations[150][100];
    char recommendedLocations[150][100];
    int visitors[150];
    int locationCount;

public:
    RecommendationData();

    void welcome();
    void loadData();
    void displayAll();
    void display(vector<Recommendation> &recommendations);
    void search(const string &key, vector<Recommendation> &recommendations, vector<Recommendation> &recentSearches);
    bool valid(const string &input);
    void mergeSort(vector<Recommendation> &recommendations);
    void merge(vector<Recommendation> &recommendations, vector<Recommendation> left, vector<Recommendation> right);
};

RecommendationData::RecommendationData() {
    locationCount = 0;
}

void RecommendationData::welcome() {
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n\t\t\t\tTOURISM RECOMMENDATION ENGINE\n\n\n";
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n";
}

void RecommendationData::loadData() {
    ifstream file("TourismData.txt");

    if (!file) {
        cout << "File Not Found\n";
        return;
    }

    while (file >> locations[locationCount] >> recommendedLocations[locationCount] >> visitors[locationCount]) {
        if (locationCount < 150)
            locationCount++;
        else {
            cout << "Maximum data limit reached.\n";
            break;
        }
    }

    file.close();
}

void RecommendationData::displayAll() {
    for (int i = 0; i < locationCount; i++) {
        cout << setw(50) << locations[i] << setw(50) << recommendedLocations[i] << setw(10) << visitors[i] << endl;
    }
}

void RecommendationData::search(const string &key, vector<Recommendation> &recommendations, vector<Recommendation> &recentSearches) {
    int n, c = 1;
    int m = key.size();
    for (int i = 0; i < locationCount; i++) {
        const char *t = locations[i];
        n = strlen(t);
        for (int j = 0; j <= n - m; j++) {
            int k = 0;
            while (k < m && key[k] == t[j + k]) {
                k = k + 1;
            }
            if (k == m) {
                Recommendation temp;
                while (c) {
                    strcpy(temp.recommendationName, locations[i]);
                    temp.visitors = visitors[i];
                    recentSearches.push_back(temp);
                    i--;
                }
                strcpy(temp.recommendationName, recommendedLocations[i]);
                temp.visitors = visitors[i];
                recommendations.push_back(temp);
            }
        }
    }
}

void RecommendationData::display(vector<Recommendation> &recommendations) {
    string choice;
    for (auto &i : recommendations) {
        cout << i.recommendationName << endl;
        cout << "Do you want more recommendations (yes/no)" << endl;
        getline(cin, choice);
        if (choice == "yes")
            continue;
        else if (choice == "no") {
            cout << "Exiting....." << endl;
            break;
        } else
            cout << "Invalid input... Exiting" << endl;
            break;
    }

}

void RecommendationData::merge(vector<Recommendation> &recommendations, vector<Recommendation> left, vector<Recommendation> right) {
    int p = left.size();
    int q = right.size();
    int i = 0, j = 0, k = 0;
    while (i < p && j < q) {
        if (left[i].visitors <= right[j].visitors) {
            recommendations[k++] = left[i++];
        } else
            recommendations[k++] = right[j++];
    }
    if (i == p) {
        while (j < q) {
            recommendations[k++] = right[j++];
        }
    } else
        while (i < p) {
            recommendations[k++] = left[i++];
        }
}

void RecommendationData::mergeSort(vector<Recommendation> &recommendations) {
    int n = recommendations.size();
    if (n > 1) {
        vector<Recommendation> left(recommendations.begin(), recommendations.begin() + n / 2);
        vector<Recommendation> right(recommendations.begin() + n / 2, recommendations.end());
        mergeSort(left);
        mergeSort(right);
        merge(recommendations, left, right);
    }
}

bool RecommendationData::valid(const string &input) {
    int n = input.size();
    int i;
    for (i = 0; i < n; i++) {
        if (input[i] == ' ')
            break;
    }
    if (i == n)
        return true;
    return false;
}

int main() {
    RecommendationData engine;
    string input;
    vector<Recommendation> recommendations, recentSearches;
    int flag, choice;

    engine.welcome();
    engine.loadData();

    while (c == 0){
        cout << "\n\nMenu:\n";
        cout << "1. Display Data\n";
        cout << "2. Search Location\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                engine.displayAll();
                break;
            case 2: {
                flag = 0;
                while (!flag) {
                    if (!recentSearches.empty()) {
                        cout << "Recently searched locations are: " << endl;
                        for (int i = 0; i < recentSearches.size(); i++)
                            cout << recentSearches[i].recommendationName << endl;
                    }
                    cout << "Enter the location to search: ";
                    cin.ignore();
                    getline(cin, input);
                    flag = engine.valid(input);
                    if (!flag)
                        cout << "Enter the location name with hyphen(-)\n";
                }
                engine.search(input, recommendations, recentSearches);
                if (!recommendations.empty()) {
                    engine.mergeSort(recommendations);
                    engine.display(recommendations);
                } else {
                    cout << "No recommendations found for the given location.\n";
                }
                break;
            }
            case 3:
                cout << "Exiting...." << endl;
                c = 1;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
