// Algorithm:  BFSS(Brute Force String Search)
// Need:       Checking if individual's PAN number is Valid or not.
// assumption: We assume there are 200 PAN numbers which are valid, open PAN_num.txt for all 200 numbers.
// inputs:     PAN number, whose format is AAAAANNNNA (A - alphabet A to Z, N - number 0 to 9).
// output:     Apply BFSS and check whether PAN number matches with the contents of PAN_num.txt

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cctype>
#include <string>
using namespace std;

class PAN_numbers{
private:
    vector <string> entries;
    int global_count;

public:
    PAN_numbers();

    void welcome();
    void load_from_file();
    void display_data();

    int bfss(const string& T, const string& P);
    bool match_found(const string& search);
};


PAN_numbers::PAN_numbers(){
    global_count = 0;
}

void PAN_numbers::welcome(){
    for (int i = 0; i < 80; i++) 
        cout << "*";
    cout << "\n\n\t\t\t\tSearch Valid PAN number\n\n\n";
    for (int i = 0; i < 80; i++)
        cout << "*";
    cout << "\n\n";
}

void PAN_numbers::load_from_file(){
    ifstream file("PAN_num.txt");

    if (!file){
        cout << "File Not Found\n";
        return;
    }

    string PAN_num;

    while (file >> PAN_num){
        entries.push_back(PAN_num);

        if (global_count < 500)
            global_count++;
        else{
            cout << "Maximum data limit reached.\n";
            break;
        }
    }

    file.close();
}

void PAN_numbers::display_data(){
    for (const auto& entry : entries){
        cout << entry << endl;
    }
}

int PAN_numbers :: bfss(const string& T, const string& P){
    int n = T.size();
    int m = P.size();

    for(int i = 0 ; i <= n-m ; i++){
        int j = 0;
        while(j < m && P[j] == T[i+j]){
            j = j+1;
        }
        if(j == m) return i; // return index of string match
    }
    return -1; // not found
}

bool PAN_numbers :: match_found(const string& search){
    int found = 0;
    for(const auto& entry : entries){
        if(bfss(entry, search) != -1){
            return true; // Valid PAN number
        }
    }
    return false; // Invalid
}

int main(){
    PAN_numbers PAN;
    PAN.welcome();
    PAN.load_from_file();

    int choice;
    cout << "1 - search PAN" << endl;
    cout << "0 - exit" << endl;

    while(-1){
        for (int i = 0; i < 80; i++) cout << "*";

        cout << endl << endl << "Enter choice :";
        cin >> choice;
        switch(choice){
            case 1:{
                string search;
                cout << "Enter PAN number: ";
                cin.ignore();
                getline(cin, search);
                cout << endl;
                if(search.empty()){
                    cout << "search string is empty" << endl;
                    break;
                }
                if(PAN.match_found(search)){
                    cout << "Valid PAN number" << endl;
                }
                else{
                    cout << "Invalid PAN number" << endl;
                }
                break;
            }
            case 0: exit(0);
            default: exit(0);
        }
    }

    return 0;
}
