#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
using namespace std;

void lowercase(string text)
{
    for (auto i : text)
    {
        if (i >= 'A' && i <= 'Z')
        {
            i = 'a' + int(i - 'A');
        }
    }
}

string RemoveHTMLTags(string text)
{
    string ans;

    for (int i = 0; i < text.length(); i++)
    {
        if (ans[i] == '<')
        {
            i++;
            while (i < text.length() && ans[i] != '>')
            {
                i++;
            }
        }

        if (i < text.length())
        {
            ans.push_back(text[i]);
        }
    }
}

string RemovePunctuation(string text)
{
    unordered_map<char, bool> punctuationMap = {
        {'.', true},
        {',', true},
        {'!', true},
        {'?', true},
        {':', true},
        {';', true},
        {'\'', true},
        {'"', true},
        {'-', true},
        {'–', true}, // En dash
        {'—', true}, // Em dash
        {'(', true},
        {')', true},
        {'[', true},
        {']', true},
        {'{', true},
        {'}', true},
        {'...', true},
        {'/', true},
        {'\\', true},
        {'&', true},
        {'*', true},
        {'@', true},
        {'^', true},
        {'_', true},
        {'~', true},
        {'`', true},
        {'|', true},
        {'<', true},
        {'>', true},
        {'#', true},
        {'$', true},
        {'%', true},
        {'+', true},
        {'=', true},
        {'`', true} // Backtick
    };

    string finalText;
    for (auto i : text)
    {
        if (!punctuationMap[i])
        {
            finalText.push_back(i);
        }
    }

    return finalText;
}

vector<vector<string>> tokenization(string text)
{
    vector<vector<string>> tokens;
    int i = 0;
    unordered_map<char, bool> punctuationMap = {
        {'.', true},
        {',', true},
        {'!', true},
        {'?', true},
        {':', true},
        {';', true},
        {'\'', true},
        {'"', true},
        {'-', true},
        {'–', true}, // En dash
        {'—', true}, // Em dash
        {'(', true},
        {')', true},
        {'[', true},
        {']', true},
        {'{', true},
        {'}', true},
        {'...', true},
        {'/', true},
        {'\\', true},
        {'&', true},
        {'*', true},
        {'@', true},
        {'^', true},
        {'_', true},
        {'~', true},
        {'`', true},
        {'|', true},
        {'<', true},
        {'>', true},
        {'#', true},
        {'$', true},
        {'%', true},
        {'+', true},
        {'=', true},
        {'`', true} // Backtick
    };

    while (i < text.size())
    {

        vector<string> line;
        while (i < text.size() && text[i] != '.')
        {
            string word;
            while (i < text.size() && (text[i] != '.' && text[i] != ' ' && !punctuationMap[i]))
            {
                word.push_back(text[i]);
                i++;
            }

            line.push_back(word);

            i++;
        }
        tokens.push_back(line);
    }

    return tokens;
}

string textPre(string text)
{
}