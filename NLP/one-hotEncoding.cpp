#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include<unordered_set>
using namespace std;

vector<vector<vector<int>>> OneHotEncoding(const vector<vector<string>>& words) {
    // Count the number of unique words
    unordered_map<string, int> st;
    int n = 0;
    for (const auto& line : words) {
        for (const auto& word : line) {
            if (!st.count(word)) {
                st[word] = n;
                n++;
            }
        }
    }

    // Create the one-hot encoding vector
    vector<vector<vector<int>>> wordcount;
    for (const auto& line : words) {
        vector<vector<int>> WordLineCount;
        for (const auto& word : line) {
            vector<int> temp(n, 0);
            temp[st[word]] = 1; // Set the position of the word to 1
            WordLineCount.push_back(temp);
        }
        wordcount.push_back(WordLineCount);
    }

    return wordcount;
}




int mai()
{

}