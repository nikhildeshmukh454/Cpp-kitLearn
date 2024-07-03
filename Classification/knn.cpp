#include<iostream>
#include<unordered_map>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

/*
Procedure:
1. Calculate the Euclidean distance from the test case to all training data points.
2. Sort the distances in ascending order.
3. For classification, use the labels of the k nearest neighbors to determine the most frequent label (majority voting).
*/

// Function to perform KNN classification
int knn(vector<vector<int>>& data, int m, int k, vector<int>& testCase) {
    int n = data.size();
    vector<pair<float, int>> distance;

    // Calculate distances from the testCase to all training data points
    for (int i = 0; i < n; i++) {
        float dis = 0;
        for (int j = 0; j < m; j++) {
            dis += (data[i][j] - testCase[j]) * (data[i][j] - testCase[j]);
        }
        dis = sqrt(dis);
        distance.push_back({dis, i});
    }

    // Sort distances
    sort(distance.begin(), distance.end());

    unordered_map<int, int> vote;
    int maxVote = 0;
    int ans = 0;

    // KNN classification: majority voting
    for (int i = 0; i < k; i++) {
        int label = data[distance[i].second][m];
        vote[label]++;
        if (vote[label] > maxVote) {
            maxVote = vote[label];
            ans = label;
        }
    }

    return ans;
}

int main() {
    // Sample data: n rows and m+1 columns (last column is the result/label)
    vector<vector<int>> data = {
        {1, 2, 0},
        {2, 3, 0},
        {3, 3, 1},
        {6, 5, 1},
        {7, 8, 1}
    };

    int m = 2;  // Number of features
    int k = 3;  // Number of nearest neighbors
    vector<int> testCase = {4, 4};  // Test case

    // Perform KNN
    int result = knn(data, m, k, testCase);

    cout << "The predicted class for the test case is: " << result << endl;

    return 0;
}
