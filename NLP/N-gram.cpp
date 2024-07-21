#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <unordered_set>
using namespace std;

vector<vector<int>> NBagOfWords(const vector<vector<string>> &words , int n )
{
    map<vector<int>, int> Vcount;
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
int n=0;

    for (const auto &line : words)
    {
        vector<int>temp;
        for(int i=0;i+n<=line.size();i++)
        {
            for(int j=i;j<i+n;j++)
            {
                temp.push_back(st[line[j]]);
            }
        }

        if(!Vcount.count(temp))
        {
            Vcount[temp]=n;
            n++;
        }

    }





    vector<vector<int>> wordcount;
       for (const auto &line : words)
    {
        vector<int>temp(n,0);
        for(int i=0;i+n<=line.size();i++)
        {
            vector<int>curr;
            for(int j=i;j<i+n;j++)
            {
                curr.push_back(st[line[j]]);
            }
              temp[Vcount[curr]]++;
        }

        wordcount.push_back(temp);

      

    }


    return wordcount;
}
