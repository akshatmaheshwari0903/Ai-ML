#include <bits/stdc++.h>
using namespace std;

/*
 * Complete the 'optimizeReservedConcurrency' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY conc
 *  2. INTEGER_ARRAY price
 */

long optimizeReservedConcurrency(vector<int> conc, vector<int> price) {
    int n = conc.size();
    
    // Create (conc, price) pairs and sort by conc
    vector<pair<long long, long long>> functions(n);
    for (int i = 0; i < n; i++) {
        functions[i] = {conc[i], price[i]};
    }
    sort(functions.begin(), functions.end());
    
    // Compute target values (making conc values unique via sweep)
    vector<long long> targets(n);
    targets[0] = functions[0].first;
    for (int i = 1; i < n; i++) {
        targets[i] = max(functions[i].first, targets[i-1] + 1);
    }
    
    // Assign functions to targets using max-heap (by price)
    // This ensures high-priced functions get assigned to closer targets
    priority_queue<pair<long long, long long>> pq; // (price, conc)
    int funcIdx = 0;
    long long totalCost = 0;
    
    for (int i = 0; i < n; i++) {
        long long target = targets[i];
        
        // Add all functions with conc <= target to the heap
        while (funcIdx < n && functions[funcIdx].first <= target) {
            pq.push({functions[funcIdx].second, functions[funcIdx].first});
            funcIdx++;
        }
        
        // Assign the function with highest price to this target
        auto top = pq.top();
        pq.pop();
        long long p = top.first;  // price
        long long c = top.second; // conc
        totalCost += (target - c) * p;
    }
    
    return (long)totalCost;
}
