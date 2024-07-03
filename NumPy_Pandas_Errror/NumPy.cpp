#include <iostream>
#include <bits/stdc++.h>
#include <numeric>
#include <random>
using namespace std;

class NumPy
{
public:
    //-------------- Array Creation and Manipulation --------------//
    // zeros
    vector<vector<int>> zeros(int n = 1, int m = 1)
    {
        vector<vector<int>> Zero(n, vector<int>(m, 0));
        return Zero;
    }

    // ones
    vector<vector<int>> ones(int n = 1, int m = 1)
    {
        vector<vector<int>> Zero(n, vector<int>(m, 1));
        return Zero;
    }

    // arange
    vector<int> arange(int s, int e)
    {
        vector<int> Arange(e - s + 1);
        for (int index = 0; index <= e - s; index++)
        {
            Arange[index] = index + s;
        }

        return Arange;
    }

    // linspace
    vector<float> linspace(int start, int stop, int num)
    {
        vector<float> spaced;
        if (num == 1)
        {
            spaced.push_back((stop + start) / 2.0f);
            return spaced;
        }

        float step = (stop - start) / static_cast<float>(num - 1);

        for (int i = 0; i < num; ++i)
        {
            spaced.push_back(start + i * step);
        }

        return spaced;
    }

    // reshape
    vector<vector<int>> reshape(int x, int y, vector<int> &Array)
    {
        vector<vector<int>> RArray(x, vector<int>(y));
        if (x * y != Array.size())
        {
            cout << "Error: Given Reshape parameters are invalid\n";
            return RArray;
        }
        else
        {
            int k = 0;
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < y; j++)
                {
                    RArray[i][j] = Array[k];
                    k++;
                }
            }
            return RArray;
        }
    }

    // flatten
    vector<int> flatten(vector<vector<int>> &Array)
    {
        vector<int> FArray;
        for (int i = 0; i < Array.size(); i++)
        {
            for (int j = 0; j < Array[0].size(); j++)
            {
                FArray.push_back(Array[i][j]);
            }
        }
        return FArray;
    }

    //-------------- Mathematical Operations --------------//
    // add
    vector<float> add(const vector<float> &vec1, const vector<float> &vec2)
    {
        if (vec1.size() != vec2.size())
        {
            cout << "Error: Vectors must be of the same length" << endl;
            return {};
        }

        vector<float> result(vec1.size());
        for (size_t i = 0; i < vec1.size(); ++i)
        {
            result[i] = vec1[i] + vec2[i];
        }

        return result;
    }

    // subtract
    vector<float> subtract(const vector<float> &vec1, const vector<float> &vec2)
    {
        if (vec1.size() != vec2.size())
        {
            cout << "Error: Vectors must be of the same length" << endl;
            return {};
        }

        vector<float> result(vec1.size());
        for (size_t i = 0; i < vec1.size(); ++i)
        {
            result[i] = vec1[i] - vec2[i];
        }

        return result;
    }

    // multiply
    vector<float> multiply(const vector<float> &vec1, const vector<float> &vec2)
    {
        if (vec1.size() != vec2.size())
        {
            cout << "Error: Vectors must be of the same length" << endl;
            return {};
        }

        vector<float> result(vec1.size());
        for (size_t i = 0; i < vec1.size(); ++i)
        {
            result[i] = vec1[i] * vec2[i];
        }

        return result;
    }

    // divide
    vector<float> divide(const vector<float> &vec1, const vector<float> &vec2)
    {
        if (vec1.size() != vec2.size())
        {
            cout << "Error: Vectors must be of the same length" << endl;
            return {};
        }

        vector<float> result(vec1.size());
        for (size_t i = 0; i < vec1.size(); ++i)
        {
            if (vec2[i] == 0)
            {
                cout << "Error: Division by zero at index " << i << endl;
                return {};
            }
            result[i] = vec1[i] / vec2[i];
        }

        return result;
    }

    // dot_product
    float dot_product(const vector<float> &vec1, const vector<float> &vec2)
    {
        if (vec1.size() != vec2.size())
        {
            cout << "Error: Vectors must be of the same length" << endl;
            return 0;
        }
        float dot_product = 0;
        for (int i = 0; i < vec1.size(); ++i)
        {
            dot_product += vec1[i] * vec2[i];
        }
        return dot_product;
    }

    // matmul
    vector<vector<float>> matmul(const vector<vector<float>> &mat1, const vector<vector<float>> &mat2)
    {
        int rows1 = mat1.size();
        int cols1 = mat1[0].size();
        int rows2 = mat2.size();
        int cols2 = mat2[0].size();

        if (cols1 != rows2)
        {
            cout << "Error: Matrices cannot be multiplied" << endl;
            return {};
        }

        vector<vector<float>> result(rows1, vector<float>(cols2, 0));

        for (int i = 0; i < rows1; ++i)
        {
            for (int j = 0; j < cols2; ++j)
            {
                for (int k = 0; k < cols1; ++k)
                {
                    result[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }

        return result;
    }

    // sum
    float sum(const vector<float> &vec)
    {
        return accumulate(vec.begin(), vec.end(), 0.0f);
    }

    // mean
    float mean(const vector<float> &vec)
    {
        if (vec.empty())
        {
            cout << "Error: Vector is empty" << endl;
            return 0;
        }
        return sum(vec) / vec.size();
    }

    // Standard Deviation
    float standardDeviation(const vector<float> &vec)
    {
        if (vec.empty())
        {
            cout << "Error: Vector is empty" << endl;
            return -1.0;
        }

        float vecMean = mean(vec);
        float sum = 0;

        for (auto i : vec)
        {
            sum += abs(i - vecMean);
        }

        sum /= vec.size();

        return sqrt(sum);
    }

    // min
    int min(const vector<int> &vec)
    {
        int min_val = numeric_limits<int>::max();

        if (vec.empty())
        {
            cout << "Error: Vector is empty" << endl;
            return min_val;
        }

        for (auto num : vec)
        {
            if (num < min_val)
            {
                min_val = num;
            }
        }

        return min_val;
    }

    // max
    int max(const vector<int> &vec)
    {
        int max_val = numeric_limits<int>::min();

        if (vec.empty())
        {
            cout << "Error: Vector is empty" << endl;
            return max_val;
        }

        for (auto num : vec)
        {
            if (num > max_val)
            {
                max_val = num;
            }
        }

        return max_val;
    }

    //-------------- Linear Algebra --------------//
    // inverse
    vector<vector<float>> inverse(vector<vector<int>> Eqn)
    {
        int n = Eqn.size();
        if (n != Eqn[0].size())
        {
            return vector<vector<float>>();
        }

        vector<vector<float>> Inv(n, vector<float>(n, 0.0));
        for (int i = 0; i < n; i++)
        {
            Inv[i][i] = 1;
        }

        vector<vector<float>> A(n, vector<float>(n, 0.0));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                A[i][j] = Eqn[i][j];
            }
        }

        for (int i = 0; i < n; i++)
        {
            float diag = A[i][i];
            for (int j = 0; j < n; j++)
            {
                A[i][j] /= diag;
                Inv[i][j] /= diag;
            }

            for (int row = 0; row < n; row++)
            {
                if (row != i)
                {
                    float factor = A[row][i];
                    for (int col = 0; col < n; col++)
                    {
                        A[row][col] -= A[i][col] * factor;
                        Inv[row][col] -= Inv[i][col] * factor;
                    }
                }
            }
        }

        return Inv;
    }

    //-------------- Random Number Generation --------------//
    // generateRandomIntegers
    vector<int> generateRandomIntegers(int n, int s, int e)
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(s, e);

        vector<int> vec(n);
        for (int &num : vec)
        {
            num = dis(gen);
        }

        return vec;
    }

    // shuffleArray
    void shuffleArray(vector<int> &vec)
    {
        random_device rd;
        mt19937 gen(rd());
        shuffle(vec.begin(), vec.end(), gen);
    }

    //-------------- Utility Functions --------------//
    // replaceIfGreaterThan
    vector<int> replaceIfGreaterThan(vector<int> &vec, int s, int num)
    {
        for (int &elem : vec)
        {
            if (elem > s)
            {
                elem = num;
            }
        }
        return vec;
    }

    // findUniqueElements
    vector<int> findUniqueElements(const vector<int> &vec)
    {
        set<int> uniqueSet(vec.begin(), vec.end());
        return vector<int>(uniqueSet.begin(), uniqueSet.end());
    }

    // concatenateArrays
    vector<int> concatenateArrays(const vector<int> &array1, const vector<int> &array2)
    {
        vector<int> concatenatedArray = array1;
        concatenatedArray.insert(concatenatedArray.end(), array2.begin(), array2.end());
        return concatenatedArray;
    }
};
