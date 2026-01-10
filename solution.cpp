#include <bits/stdc++.h>
using namespace std;

/*
 * Complete the 'medians' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY values
 *  2. INTEGER k
 */

/*
 * Key Insight:
 * - The median of a sorted subsequence of length k is at position ceil(k/2) (1-indexed)
 * - To maximize median: need at least (floor(k/2) + 1) elements >= median value
 *   => Maximum median = (floor(k/2) + 1)th largest element
 * - To minimize median: need at least ceil(k/2) elements <= median value
 *   => Minimum median = ceil(k/2)th smallest element
 *
 * After sorting the array:
 * - Minimum median = sorted[(k-1)/2]
 * - Maximum median = sorted[n - 1 - k/2]
 */

vector<int> medians(vector<int> values, int k) {
    int n = values.size();
    
    // Sort the array
    sort(values.begin(), values.end());
    
    // Minimum median: ceil(k/2)th smallest element
    // In 0-indexed: (k-1)/2
    int minMedian = values[(k - 1) / 2];
    
    // Maximum median: (floor(k/2) + 1)th largest element
    // In 0-indexed from sorted ascending: n - 1 - floor(k/2) = n - 1 - k/2
    int maxMedian = values[n - 1 - k / 2];
    
    return {maxMedian, minMedian};
}

int main() {
    // Test Case 0: values = [56, 21], k = 1
    // Expected output: 56, 21
    vector<int> test1 = {56, 21};
    vector<int> result1 = medians(test1, 1);
    cout << "Test 1: " << result1[0] << " " << result1[1] << endl;
    cout << "Expected: 56 21" << endl;
    
    // Test Case 1: values = [16, 21, 9, 2, 78], k = 5
    // Expected output: 16, 16
    vector<int> test2 = {16, 21, 9, 2, 78};
    vector<int> result2 = medians(test2, 5);
    cout << "Test 2: " << result2[0] << " " << result2[1] << endl;
    cout << "Expected: 16 16" << endl;
    
    // Example from problem: values = [1, 2, 3], k = 2
    // Expected output: 2, 1
    vector<int> test3 = {1, 2, 3};
    vector<int> result3 = medians(test3, 2);
    cout << "Test 3: " << result3[0] << " " << result3[1] << endl;
    cout << "Expected: 2 1" << endl;
    
    return 0;
}
