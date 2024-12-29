#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cctype>
#include <string>
#include <algorithm>
using namespace std;

string rand_PAN(){
    string first_three;
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // First three characters: sequence of alphabets from AAA to ZZZ
    for (int i = 0; i < 3; ++i){
        first_three += chars[rand() % 26];
    }
    
    // Fourth character: type of PAN holder (e.g., P for Individual, C for Company, H for HUF, etc.)
    string types = "PCHFTBLJG";
    char fourth = types[rand() % types.length()];
    
    // Fifth character: first letter of the PAN holder's last name/surname
    char fifth = chars[rand() % 26];
    
    // Next four characters: numeric characters from 0001 to 9999
    string next_four;
    for (int i = 0; i < 4; ++i){
        next_four += '0' + rand() % 10;
    }
    
    // Last character: alphabetic check digit
    char last = chars[rand() % 26];
    
    return first_three + fourth + fifth + next_four + last;
}

int main(){
    srand(static_cast<unsigned int>(time(0)));
    vector<string> pan_numbers;
    int n;
    cout << "Enter n PAN numbers to be generated : ";
    cin >> n;
    for (int i = 0; i < n; ++i){
        pan_numbers.push_back(rand_PAN());
    }
    for (const auto& pan : pan_numbers){
        cout << pan << endl;
    }
    return 0;
}
