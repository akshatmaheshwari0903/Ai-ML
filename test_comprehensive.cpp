#include <bits/stdc++.h>
using namespace std;

long optimizeReservedConcurrency(vector<int> conc, vector<int> price) {
    int n = conc.size();
    
    vector<pair<long long, long long>> functions(n);
    for (int i = 0; i < n; i++) {
        functions[i] = {conc[i], price[i]};
    }
    sort(functions.begin(), functions.end());
    
    vector<long long> targets(n);
    targets[0] = functions[0].first;
    for (int i = 1; i < n; i++) {
        targets[i] = max(functions[i].first, targets[i-1] + 1);
    }
    
    priority_queue<pair<long long, long long>> pq;
    int funcIdx = 0;
    long long totalCost = 0;
    
    for (int i = 0; i < n; i++) {
        long long target = targets[i];
        
        while (funcIdx < n && functions[funcIdx].first <= target) {
            pq.push({functions[funcIdx].second, functions[funcIdx].first});
            funcIdx++;
        }
        
        auto top = pq.top();
        pq.pop();
        long long p = top.first;
        long long c = top.second;
        totalCost += (target - c) * p;
    }
    
    return (long)totalCost;
}

int main() {
    cout << "=== Basic Tests ===" << endl;
    
    // Single element
    cout << "Single element: " << optimizeReservedConcurrency({5}, {10}) << " (expected: 0)" << endl;
    
    // All unique
    cout << "All unique [1,2,3]: " << optimizeReservedConcurrency({1,2,3}, {5,5,5}) << " (expected: 0)" << endl;
    
    // All same
    cout << "All same [1,1,1,1]: " << optimizeReservedConcurrency({1,1,1,1}, {1,2,3,4}) << " (expected: 6)" << endl;
    // 1→4, 2→3(cost 3), 3→2(cost 4), 4→1(cost 3) = 10? No wait...
    // targets: [1,2,3,4]
    // Process 1: add all, pick price=4, assign to 1, cost=0
    // Process 2: pick price=3, assign to 2, cost=3
    // Process 3: pick price=2, assign to 3, cost=4
    // Process 4: pick price=1, assign to 4, cost=3
    // Total = 0 + 3 + 4 + 3 = 10? Hmm let me recalculate
    // (2-1)*3 = 3, (3-1)*2 = 4, (4-1)*1 = 3 => 10
    
    cout << "All same [1,1,1,1] v2: " << optimizeReservedConcurrency({1,1,1,1}, {1,2,3,4}) << " (expected: 10)" << endl;
    
    // Large values
    cout << "Large conc [1000000000, 1000000000]: " << optimizeReservedConcurrency({1000000000, 1000000000}, {100000, 1}) << " (expected: 1)" << endl;
    
    // Gap in values - function with higher conc should claim its value
    cout << "Gap [1,1,5]: " << optimizeReservedConcurrency({1,1,5}, {10,20,30}) << " (expected: 10)" << endl;
    // targets: [1,2,5]
    // Process 1: pick 20, cost=0
    // Process 2: pick 10, cost=10
    // Process 5: pick 30, cost=0
    // Total = 10
    
    // Complex case with multiple clusters
    cout << "Complex [1,1,2,2,3]: " << optimizeReservedConcurrency({1,1,2,2,3}, {5,10,15,20,25}) << " (expected: 25)" << endl;
    // targets: [1,2,3,4,5]
    // Process 1: add (1,5),(1,10), pick 10, cost=0
    // Process 2: add (2,15),(2,20), pick 20, cost=0
    // Process 3: add (3,25), pick 25, cost=0
    // Process 4: pick 15, cost=(4-2)*15=30
    // Process 5: pick 5, cost=(5-1)*5=20
    // Total = 50? Let me recalc
    
    vector<int> c6 = {1,1,2,2,3};
    vector<int> p6 = {5,10,15,20,25};
    cout << "Complex [1,1,2,2,3] result: " << optimizeReservedConcurrency(c6, p6) << endl;
    
    // Test the problematic 3-same pattern mentioned by user
    cout << "Three same [5,5,5,6,6]: " << optimizeReservedConcurrency({5,5,5,6,6}, {1,2,3,4,5}) << endl;
    // targets: [5,6,7,8,9]
    // Process 5: add (5,1),(5,2),(5,3), pick 3, cost=0
    // Process 6: add (6,4),(6,5), pick 5, cost=0
    // Process 7: pick 4, cost=(7-6)*4=4
    // Process 8: pick 2, cost=(8-5)*2=6
    // Process 9: pick 1, cost=(9-5)*1=4
    // Total = 14
    cout << "(expected: 14)" << endl;
    
    return 0;
}
