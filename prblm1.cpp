#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

// Convert string number to base-10 integer
int baseToDecimal(string val, int base) {
    int res = 0;
    for (char ch : val) {
        res = res * base + (ch - '0');
    }
    return res;
}

// Lagrange interpolation to compute f(0)
double lagrangeInterpolation(vector<pair<int, int>>& points) {
    int k = points.size();
    double result = 0;

    for (int i = 0; i < k; ++i) {
        double xi = points[i].first;
        double yi = points[i].second;
        double term = yi;

        for (int j = 0; j < k; ++j) {
            if (i != j) {
                double xj = points[j].first;
                term *= (0 - xj) / (xi - xj);  // Lagrange basis polynomial at 0
            }
        }

        result += term;
    }

    return result;  // This will be the constant term c
}

int main() {
    // Simulate parsed JSON input
    int n = 4;
    int k = 3;

    // key => (base, value)
    map<int, pair<int, string>> input = {
        {1, {10, "4"}},
        {2, {2, "111"}},
        {3, {10, "12"}},
        {6, {4, "213"}}
    };

    // Step 1: Decode values into (x, y)
    vector<pair<int, int>> points;
    for (auto& kv : input) {
        int x = kv.first;
        int base = kv.second.first;
        string val = kv.second.second;
        int y = baseToDecimal(val, base);
        points.push_back({x, y});
    }

    // Step 2: Use first k points
    vector<pair<int, int>> subset(points.begin(), points.begin() + k);

    // Step 3: Lagrange interpolation to find f(0)
    double constantTerm = lagrangeInterpolation(subset);

    // Step 4: Output
    cout << "Secret (constant term c): " << round(constantTerm) << endl;
    return 0;
}