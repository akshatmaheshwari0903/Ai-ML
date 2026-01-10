#include <bits/stdc++.h>
using namespace std;

/*
Problem (from screenshot):
- We have n Lambda functions.
- Function i has current reserved concurrency conc[i].
- In one operation, we may increase conc[i] by exactly 1, paying price[i].
- Goal: make all final conc values distinct (unique) with minimum total cost.

Key idea:
Assign each function to a unique integer "slot" x >= conc[i].
Cost for i assigned to x is price[i] * (x - conc[i]).

This is equivalent to scheduling unit-time jobs:
- release time r_i = conc[i]
- weight w_i = price[i]
- completion time C_i = assigned slot
Minimize sum w_i * C_i (minus constant sum w_i*r_i).
Optimal greedy for unit jobs with release times:
At each integer time x, among available jobs (r_i <= x), run the one with
largest weight w_i (to avoid paying its weight for extra delay).
*/

long optimizeReservedConcurrency(vector<int> conc, vector<int> price) {
    const int n = (int)conc.size();
    vector<pair<long long, long long>> items;
    items.reserve(n);
    for (int i = 0; i < n; i++) items.push_back({(long long)conc[i], (long long)price[i]});
    sort(items.begin(), items.end()); // by conc ascending

    // max-heap by price; store (price, conc)
    priority_queue<pair<long long, long long>> pq;

    long long total = 0;
    long long x = 0;
    int idx = 0;

    while (idx < n || !pq.empty()) {
        if (pq.empty()) {
            x = max(x, items[idx].first); // jump to next release time
        }

        while (idx < n && items[idx].first <= x) {
            pq.push({items[idx].second, items[idx].first});
            idx++;
        }

        auto [w, r] = pq.top();
        pq.pop();
        total += w * (x - r);
        x++;
    }

    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> conc(n);
    for (int i = 0; i < n; i++) cin >> conc[i];

    int m;
    cin >> m; // per screenshot input format repeats n
    vector<int> price(m);
    for (int i = 0; i < m; i++) cin >> price[i];

    // If input is malformed and m != n, still compute on min length.
    const int k = min((int)conc.size(), (int)price.size());
    conc.resize(k);
    price.resize(k);

    cout << optimizeReservedConcurrency(conc, price) << "\n";
    return 0;
}

