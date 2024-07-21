#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <unordered_set>
using namespace std;

vector<vector<int>> BagOfWords(const vector<vector<string>> &words)
{
    unordered_map<string, int> st;
    int n = 0;
    for (const auto &line : words)
    {
        for (const auto &word : line)
        {
            if (!st.count(word))
            {
                st[word] = n;
                n++;
            }
        }
    }

    vector<vector<int>> wordcount;
    for (const auto &line : words)
    {
        vector<int> temp(n, 0);
        for (const auto &word : line)
        {
            temp[st[word]]++; // Increment the count of the word
        }
        wordcount.push_back(temp);
    }

    return wordcount;
}

vector<vector<int>> BagOfWordsBinary(const vector<vector<string>> &words)
{
    unordered_map<string, int> st;
    int n = 0;
    for (const auto &line : words)
    {
        for (const auto &word : line)
        {
            if (!st.count(word))
            {
                st[word] = n;
                n++;
            }
        }
    }

    vector<vector<int>> wordcount;
    for (const auto &line : words)
    {
        vector<int> temp(n, 0);
        for (const auto &word : line)
        {
            temp[st[word]] = 1;
        }
        wordcount.push_back(temp);
    }

    return wordcount;
}
