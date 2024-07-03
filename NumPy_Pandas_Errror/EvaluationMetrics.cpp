#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Evaluation
{
public:
    //--------mean absoulte  error --------//
    float MAE(vector<int> &Y, vector<int> Ypred)
    {

        float sum = 0;
        for (int i = 0; i < Y.size(); i++)
        {
            sum += abs(Y[i] - Ypred[i]);
        }

        sum /= Y.size();

        return sum;
    }

    //---------------- Mean Squared Error MSE---------------------
    float MSE(vector<int> &Y, vector<int> Ypred)
    {

        float sum = 0;
        for (int i = 0; i < Y.size(); i++)
        {
            sum += (Y[i] - Ypred[i]) * (Y[i] - Ypred[i]);
        }

        sum /= Y.size();

        return sum;
    }

    //---------------------Root Mean Squared Error RMSE---------------------
    float RMSE(vector<int> &Y, vector<int> Ypred)
    {

        float sum = 0;
        for (int i = 0; i < Y.size(); i++)
        {
            sum += (Y[i] - Ypred[i]) * (Y[i] - Ypred[i]);
        }

        sum /= Y.size();
        sum = sqrt(sum);

        return sum;
    }
    //---------------------------------R-sqared--------------------------------

    float Rsqr(vector<int> &y, vector<int> &ypred)
    {
        float SSt = 0;
        float SSr = 0;

        float Ymeans = 0;
        for (int i : y)
        {
            Ymeans += i;
        }
        Ymeans /= y.size();

        for (int i = 0; i < y.size(); i++)
        {
            SSr += (ypred[i] - y[i]) * (ypred[i] - y[i]);
            SSt += (ypred[i] - Ymeans) * (ypred[i] - Ymeans);
        }

        float RSQR = 1 - (SSr / SSt);

        return RSQR;
    }

    //--------------------------Adjusted R-squared-------------------------------

    float Adjusted_R_squared(vector<int> &y, vector<int> &ypred, int k , int n )
    {
        float RSQR=Rsqr(y,ypred);

        float ADjR=1-((1-RSQR)*(n-1)/(n-k-1));

        return ADjR;

    }
};