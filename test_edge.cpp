#include <bits/stdc++.h>
using namespace std;

long optimizeReservedConcurrency(vector<int> conc, vector<int> price) {
    int n = conc.size();
    vector<pair<int, int>> functions(n);
    for (int i = 0; i < n; i++) {
        functions[i] = {conc[i], price[i]};
    }
    
    sort(functions.begin(), functions.end(), [](const auto& a, const auto& b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second > b.second;
    });
    
    long long totalCost = 0;
    long long lastAssigned = 0;
    
    for (const auto& func : functions) {
        long long c = func.first;
        long long p = func.second;
        
        if (c > lastAssigned) {
            lastAssigned = c;
        } else {
            long long newVal = lastAssigned + 1;
            totalCost += (newVal - c) * p;
            lastAssigned = newVal;
        }
    }
    
    return (long)totalCost;
}

int main() {
    // Edge case: single element
    cout << "Single element: " << optimizeReservedConcurrency({5}, {10}) << " (expected: 0)" << endl;
    
    // Edge case: all same values
    cout << "All same [1,1,1] prices [10,20,30]: " << optimizeReservedConcurrency({1,1,1}, {10,20,30}) << " (expected: 40)" << endl;
    // Explanation: assign 1 to price-30, 2 to price-20 (cost 20), 3 to price-10 (cost 20) = 40
    
    // Edge case: consecutive values
    cout << "Consecutive [1,2,3]: " << optimizeReservedConcurrency({1,2,3}, {5,5,5}) << " (expected: 0)" << endl;
    
    // Large values test
    cout << "Large values [1000000000, 1000000000]: " << optimizeReservedConcurrency({1000000000, 1000000000}, {100000, 1}) << " (expected: 1)" << endl;
    
    // Many duplicates
    vector<int> conc(5, 10);
    vector<int> price = {1, 2, 3, 4, 5};
    // Sorted by price desc: (10,5), (10,4), (10,3), (10,2), (10,1)
    // Assign: 10, 11 (cost 4), 12 (cost 2*3=6), 13 (cost 3*2=6), 14 (cost 4*1=4) = 20
    cout << "Many duplicates: " << optimizeReservedConcurrency(conc, price) << " (expected: 20)" << endl;
    
    return 0;
}
