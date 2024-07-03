#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Assume we have vector<vector<int>>(n, vector<int>(m+1)) data and last col is result and first m col are features

// Let there be a linear co-relation in our data set so w1x1+w2x2+w3x3.....wmxm +b=xm+1;

// We will use gradient descent for getting the closest line 
// We have loss for this sum of (y-ypre) * (y-ypre);
// l(w,b) = sum of (y - (w1x1+w2x2+w3x3.....wmxm +b)) * (y - (w1x1+w2x2+w3x3.....wmxm +b));

// After we take the derivative then
// dl/dwi = -2 * sum of x_i * (y - (w1x1+w2x2+w3x3.....wmxm +b))
// dl/db = -2 * sum of (y - (w1x1+w2x2+w3x3.....wmxm +b))


// -------------------------------------Batch Gradient Descent-------------------------------------------------------- 

pair<vector<float>, float> GD(int m , vector<vector<int>>& data, int epoch, float lr) {
    int n = data.size();
    vector<float> W(m, 1.0);
    float b = 0;

    while(epoch--) {
        float loss_int = 0;
        float SUM = 0;

        for(int i = 0; i < n; i++) {
            float y = data[i][m];
            float y_pred = b;
            for(int j = 0; j < m; j++) {
                y_pred += W[j] * data[i][j];
            }
            float error = y - y_pred;
            SUM += error;
        }

        SUM *= -2;
        loss_int = SUM;

        for(int i = 0; i < m; i++) {
            float sum_error = 0;
            for(int j = 0; j < n; j++) {
                float y = data[j][m];
                float y_pred = b;
                for(int k = 0; k < m; k++) {
                    y_pred += W[k] * data[j][k];
                }
                float error = y - y_pred;
                sum_error += error * data[j][i];
            }
            W[i] -= lr * sum_error * -2;
        }

        b -= lr * SUM;
        // Uncomment the following line if you want to print the loss for each epoch
        cout << "Epoch " << epoch << ", Loss: " << loss_int << endl;
    }

    return make_pair(W, b);
}

// -------------------------------------Stochastic Gradient Descent-------------------------------------------------------- 

pair<vector<float>, float> SGD(int m , vector<vector<int>>& data, int epoch, float lr) {
    int n = data.size();
    vector<float> W(m, 1.0);
    float b = 0;

    // Initialize random seed
    srand(time(0));

    while (epoch--) {
        for (int i = 0; i < n; i++) {
            // Randomly select an index
            int random_index = rand() % n;

            // Get the data point
            float y = data[random_index][m];
            float y_pred = b;
            for (int j = 0; j < m; j++) {
                y_pred += W[j] * data[random_index][j];
            }
            float error = y - y_pred;

            // Update weights and bias
            for (int j = 0; j < m; j++) {
                W[j] -= lr * (-2 * error * data[random_index][j]);
            }
            b -= lr * (-2 * error);

            // Uncomment the following line if you want to print the loss for each update
            // cout << "Epoch " << epoch << ", Loss: " << error << endl;
        } 
    }

    return make_pair(W, b);
}

// ------------------------------------------------------------------------------------------------------------------------

int main() {
    // Example usage
    vector<vector<int>> data = {{1, 2, 10}, {2, 3, 15}, {3, 4, 20}};
    int m = 2; 
    int epoch = 1000;
    float lr = 0.01; 

    pair<vector<float>, float> result_gd = GD(m, data, epoch, lr);

    cout << "Batch Gradient Descent:" << endl;
    cout << "Weights (W): ";
    for (float w : result_gd.first) {
        cout << w << " ";
    }
    cout << endl;
    cout << "Bias (b): " << result_gd.second << endl;

    pair<vector<float>, float> result_sgd = SGD(m, data, epoch, lr);

    cout << "Stochastic Gradient Descent:" << endl;
    cout << "Weights (W): ";
    for (float w : result_sgd.first) {
        cout << w << " ";
    }
    cout << endl;
    cout << "Bias (b): " << result_sgd.second << endl;

    return 0;
}
