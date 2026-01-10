#include <bits/stdc++.h>
using namespace std;

/*
 * Complete the 'optimizeReservedConcurrency' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY conc
 *  2. INTEGER_ARRAY price
 * 
 * Algorithm:
 * 1. Pair each (conc[i], price[i]) and sort by concurrency ascending,
 *    then by price descending for ties.
 * 2. For same concurrency values, the one with highest price stays unchanged
 *    (since it costs more to bump), cheaper ones get bumped.
 * 3. Sweep through sorted list maintaining lastAssigned value.
 *    If current conc <= lastAssigned, bump to lastAssigned+1.
 * 
 * Time: O(n log n), Space: O(n)
 */

long optimizeReservedConcurrency(vector<int> conc, vector<int> price) {
    int n = conc.size();
    
    // Create pairs of (concurrency, price)
    vector<pair<int, int>> functions(n);
    for (int i = 0; i < n; i++) {
        functions[i] = {conc[i], price[i]};
    }
    
    // Sort by concurrency ascending, then by price descending
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
