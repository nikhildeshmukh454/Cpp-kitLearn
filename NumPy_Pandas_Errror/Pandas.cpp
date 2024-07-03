#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class DataFrame
{
private:
    vector<vector<string>> data;
    vector<string> dataTypes; // Stores data type for each column

public:
    void readCSV(const string &filename)
    {
        ifstream file(filename);
        if (!file.is_open())
        {
            cerr << "Error: Failed to open file " << filename << endl;
            return;
        }

        string line;
        if (getline(file, line))
        { // Read the header row for data types
            stringstream ss(line);
            string cell;

            while (getline(ss, cell, ','))
            {
                dataTypes.push_back(cell); // Assuming each cell is a data type indicator
            }
        }

        while (getline(file, line))
        {
            stringstream ss(line);
            vector<string> row;
            string cell;

            while (getline(ss, cell, ','))
            {
                row.push_back(cell);
            }

            data.push_back(row);
        }

        file.close();
    }

    void head(int n = 5)
    {
        cout << "First " << n << " rows:" << endl;
        displayRows(0, n);
    }

    void tail(int n = 5)
    {
        cout << "Last " << n << " rows:" << endl;
        int start = data.size() - n;
        if (start < 0)
            start = 0;
        displayRows(start, data.size());
    }

    void info()
    {
        cout << "DataFrame Info:" << endl;
        cout << "Number of rows: " << data.size() << endl;
        if (!data.empty())
        {
            cout << "Number of columns: " << data[0].size() << endl;
            cout << "Column names and types: " << endl;
            for (size_t i = 0; i < data[0].size(); ++i)
            {
                cout << setw(15) << left << data[0][i] << ": " << dataTypes[i] << endl;
            }
            cout << endl;
        }
    }

    template <typename T>
    T get(int i, int j)
    {
        stringstream ss(data[i][j]);
        T value;
        ss >> value;
        return value;
    }

    void setColumnDataTypes(vector<string> &newTypes)
    {
        dataTypes = newTypes;
    }

private:
    void displayRows(int start, int end)
    {
        for (int i = start; i < end && i < data.size(); ++i)
        {
            for (const auto &cell : data[i])
            {
                cout << setw(15) << left << cell;
            }
            cout << endl;
        }
        cout << endl;
    }
};

int main()
{
    
}
