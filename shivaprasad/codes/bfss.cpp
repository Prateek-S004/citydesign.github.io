#include <bits/stdc++.h>
using namespace std;



bool bfss(string text, string pattern) 
{
    int n = text.size(), m = pattern.size();

    for (int i = 0; i <= n - m; i++) 
    {  
        int j = 0;
        while (j < m && pattern[j] == text[i + j]) j++;
        if (j == m) return true;
    }
    return false;  
}
