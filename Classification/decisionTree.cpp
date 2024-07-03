#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
#include <algorithm>
#include<queue>
#include<set>

using namespace std;

class Tree {
public:
    int featureIndex;
    double condition;
    double result;
    Tree* left;
    Tree* right;

    Tree(int featureIndex, double condition, double result) {
        this->featureIndex = featureIndex;
        this->condition = condition;
        this->result = result;
        left = nullptr;
        right = nullptr;
    }

   
};

double calculateEntropy(const vector<double>& labels) {
    unordered_map<double, int> labelCounts;
    for (double label : labels) {
        labelCounts[label]++;
    }
    double entropy = 0.0;
    for (const auto& pair : labelCounts) {
        double p = (double)pair.second / labels.size();
        entropy -= p * log2(p);
    }
    return entropy;
}

double calculateInformationGain(const vector<vector<double>>& data, int featureIndex, double threshold) {
    vector<double> labels;
    for (const auto& row : data) {
        labels.push_back(row.back());
    }
    double totalEntropy = calculateEntropy(labels);
    vector<vector<double>> leftData, rightData;
    for (const auto& row : data) {
        if (row[featureIndex] < threshold) {
            leftData.push_back(row);
        } else {
            rightData.push_back(row);
        }
    }
    double weightedSubsetEntropy = 0.0;
    if (!leftData.empty()) {
        vector<double> leftLabels;
        for (const auto& row : leftData) {
            leftLabels.push_back(row.back());
        }
        double leftEntropy = calculateEntropy(leftLabels);
        weightedSubsetEntropy += (double)leftLabels.size() / data.size() * leftEntropy;
    }
    if (!rightData.empty()) {
        vector<double> rightLabels;
        for (const auto& row : rightData) {
            rightLabels.push_back(row.back());
        }
        double rightEntropy = calculateEntropy(rightLabels);
        weightedSubsetEntropy += (double)rightLabels.size() / data.size() * rightEntropy;
    }
    return totalEntropy - weightedSubsetEntropy;
}

pair<int, double> chooseBestFeatureAndThreshold(const vector<vector<double>>& data) {
    double maxInformationGain = -1.0;
    int bestFeatureIndex = -1;
    double bestThreshold = 0.0;
    int numFeatures = data[0].size() - 1;
    for (int i = 0; i < numFeatures; ++i) {
       
        set<double>num;
        for (const auto& row : data) {
            num.insert(row[i]);
        }
        vector<double> thresholds(num.begin(),num.end());


        for (double threshold : thresholds) {
            double informationGain = calculateInformationGain(data, i, threshold);
            if (informationGain > maxInformationGain) {
                maxInformationGain = informationGain;
                bestFeatureIndex = i;
                bestThreshold = threshold;
            }
        }



    }
    return {bestFeatureIndex, bestThreshold};
}



double getMostCommonResult(const vector<vector<double>>& data) {
    unordered_map<double, int> labelCounts;
    for (const auto& row : data) {
        labelCounts[row.back()]++;
    }
    double mostCommonResult;
    int maxCount = -1;
    for (const auto& pair : labelCounts) {
        if (pair.second > maxCount) {
            maxCount = pair.second;
            mostCommonResult = pair.first;
        }
    }
    return mostCommonResult;
}

void splitData(const vector<vector<double>>& data, int featureIndex, double threshold, vector<vector<double>>& leftData, vector<vector<double>>& rightData) {
    for (const auto& row : data) {
        if (row[featureIndex] < threshold) {
            leftData.push_back(row);
        } else {
            rightData.push_back(row);
        }
    }
}



Tree* buildTreeRecursive(const vector<vector<double>>& data, int currentDepth, int maxDepth) {
    if (currentDepth >= maxDepth || data.size()==1) {
        double result = getMostCommonResult(data);
        return new Tree(-1, -1.0, result);
    }
    auto PAIR= chooseBestFeatureAndThreshold(data);
    int bestFeatureIndex =PAIR.first;
    double bestThreshold=PAIR.second;

    if (bestFeatureIndex == -1) {
        double result = getMostCommonResult(data);
        return new Tree(-1, -1.0, result);
    }

    vector<vector<double>> leftData, rightData;
    splitData(data, bestFeatureIndex, bestThreshold, leftData, rightData);

    Tree* node = new Tree(bestFeatureIndex, bestThreshold, -1.0);

    node->left = buildTreeRecursive(leftData, currentDepth + 1, maxDepth);
    node->right = buildTreeRecursive(rightData, currentDepth + 1, maxDepth);

    return node;
}

Tree* buildDecisionTree(const vector<vector<double>>& data, int maxDepth) {
    return buildTreeRecursive(data, 0, maxDepth);
}


double predict(Tree* root, const vector<double>& Test) {

    if(root && root->result!=-1)
    {
        return root->result;
    }

    if(Test[root->featureIndex]<=root->condition)
    {
        return predict(root->left,Test);
    }
    else{

        return predict(root->right,Test);
    }

    
}
void print(Tree* root) {
    if (!root) return; // Check for empty tree

    queue<Tree*> pq;
    pq.push(root);
    pq.push(NULL);

    while (!pq.empty()) {
        Tree* F = pq.front();
        pq.pop();

        if (!F) {
            cout << endl;
            if (!pq.empty()) {
                pq.push(NULL);
            }
        } else {
            cout << "F->condition" << " " << "F->featureIndex" << " " << "F->result" << " | ";
            cout << F->condition << " " << F->featureIndex << " " << F->result << " | ";
            if (F->left) {
                pq.push(F->left);
            }
            if (F->right) {
                pq.push(F->right);
            }
        }
    }
}


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


int main() {
    vector<vector<double>> data = {
        {1.0, 2.0, 0.0},
        {2.0, 3.0, 1.0},
        {3.0, 4.0, 0.0},
        {4.0, 5.0, 1.0},
        {5.0, 6.0, 0.0},
        {6.0, 7.0, 1.0},
        {7.0, 8.0, 0.0},
        {8.0, 9.0, 1.0},
        {9.0, 10.0, 0.0},
        {10.0, 11.0, 1.0},
        {11.0, 12.0, 0.0},
        {12.0, 13.0, 1.0},
        {13.0, 14.0, 0.0},
        {14.0, 15.0, 1.0},
        {15.0, 16.0, 0.0},
        {16.0, 17.0, 1.0},
        {17.0, 18.0, 0.0},
        {18.0, 19.0, 1.0},
        {19.0, 20.0, 0.0},
        {20.0, 21.0, 1.0}
    };


    vector<int>y,ypre;

    int maxDepth = 6;
 Tree* decisionTree = buildDecisionTree(data, maxDepth);
    for(int i=0;i<data.size();i++){
    vector<double> instanceToPredict = {data[i][0],data[i][1]};
    double prediction = predict(decisionTree, instanceToPredict);
    ypre.push_back(int(prediction));
    y.push_back(int(data[i][2]));
    cout << "Prediction: " << prediction << " Actual "<<data[i][2]<<endl;
    }

    cout<<RMSE(y,ypre)<<endl;

    return 0;
}
