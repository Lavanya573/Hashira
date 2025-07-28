#include <iostream>
using namespace std;

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
int mul(int a, int b) { return a * b; }
int square(int x) { return x * x; }

int main() {
    int x_valid[5] = {1, 2, 3, 4, 5};
    int y_valid[5] = {97, 163, 253, 367, 505};

    int x_invalid[3] = {6, 7, 8};
    int y_invalid[3] = {500, 720, 1000};

    int x1 = x_valid[0], y1 = y_valid[0];
    int x2 = x_valid[1], y2 = y_valid[1];
    int x3 = x_valid[2], y3 = y_valid[2];

    int eq1 = sub(y2, y1); 
    int eq2 = sub(y3, y1); 

  

    int c = (eq2 - 2 * eq1) / 2;       
    int b = sub(eq1, mul(3, c));       
    int a = sub(y1, add(mul(c, square(x1)), mul(b, x1))); 

    cout << "Recovered polynomial coefficients:\n";
    cout << "a (secret) = " << a << "\n";
    cout << "b = " << b << "\n";
    cout << "c = " << c << "\n";

    cout << "\nVerifying VALID key-value shares:\n";
    for (int i = 0; i < 5; i++) {
        int xi = x_valid[i];
        int fx = add(a, add(mul(c, square(xi)), mul(b, xi)));

        cout << "Share (x = " << xi << ") => f(x) = add(a, add(mul(c," << xi << "^2), mul(b," << xi << "))) = "
             << fx << " | Expected y = " << y_valid[i];

        if (fx == y_valid[i]) cout << " Valid\n";
        else cout << "  Invalid\n";
    }

    cout << "\nTesting INVALID key-value shares:\n";
    for (int i = 0; i < 3; i++) {
        int xi = x_invalid[i];
        int fx = add(a, add(mul(c, square(xi)), mul(b, xi)));

        cout << "Share (x = " << xi << ") => f(x) = add(a, add(mul(c," << xi << "^2), mul(b," << xi << "))) = "
             << fx << " | Given y = " << y_invalid[i];

        if (fx == y_invalid[i]) cout << "  Valid (unexpected)\n";
        else cout << "  Invalid\n";
    }

    return 0;
}


// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <map>
// using namespace std;

// // Convert string number to base-10 integer
// int baseToDecimal(string val, int base) {
//     int res = 0;
//     for (char ch : val) {
//         res = res * base + (ch - '0');
//     }
//     return res;
// }

// // Lagrange interpolation to compute f(0)
// double lagrangeInterpolation(vector<pair<int, int>>& points) {
//     int k = points.size();
//     double result = 0;

//     for (int i = 0; i < k; ++i) {
//         double xi = points[i].first;
//         double yi = points[i].second;
//         double term = yi;

//         for (int j = 0; j < k; ++j) {
//             if (i != j) {
//                 double xj = points[j].first;
//                 term *= (0 - xj) / (xi - xj);  // Lagrange basis polynomial at 0
//             }
//         }

//         result += term;
//     }

//     return result;  // This will be the constant term c
// }

// int main() {
//     // Simulate parsed JSON input
//     int n = 4;
//     int k = 3;

//     // key => (base, value)
//     map<int, pair<int, string>> input = {
//         {1, {10, "4"}},
//         {2, {2, "111"}},
//         {3, {10, "12"}},
//         {6, {4, "213"}}
//     };

//     // Step 1: Decode values into (x, y)
//     vector<pair<int, int>> points;
//     for (auto& kv : input) {
//         int x = kv.first;
//         int base = kv.second.first;
//         string val = kv.second.second;
//         int y = baseToDecimal(val, base);
//         points.push_back({x, y});
//     }

//     // Step 2: Use first k points
//     vector<pair<int, int>> subset(points.begin(), points.begin() + k);

//     // Step 3: Lagrange interpolation to find f(0)
//     double constantTerm = lagrangeInterpolation(subset);

//     // Step 4: Output
//     cout << "Secret (constant term c): " << round(constantTerm) << endl;
//     return 0;
// }
