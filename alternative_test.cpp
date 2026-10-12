#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Alternative interpretation: count m elements starting from the NEXT element
vector<int> josephusAlternative(int n, int m) {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        q.push(i);
    }
    
    vector<int> result;
    while (!q.empty()) {
        // Move m-1 elements from front to back
        for (int i = 1; i < m; i++) {
            q.push(q.front());
            q.pop();
        }
        // Remove the m-th element
        result.push_back(q.front());
        q.pop();
    }
    return result;
}

// Original interpretation: count m elements including the current one
vector<int> josephusOriginal(int n, int m) {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        q.push(i);
    }
    
    vector<int> result;
    while (!q.empty()) {
        // Move m-1 elements from front to back
        for (int i = 1; i < m; i++) {
            q.push(q.front());
            q.pop();
        }
        // Remove the m-th element
        result.push_back(q.front());
        q.pop();
    }
    return result;
}

int main() {
    // Test the sample case
    int n = 5, m = 3;
    
    vector<int> alt = josephusAlternative(n, m);
    vector<int> orig = josephusOriginal(n, m);
    
    cout << "Alternative interpretation: ";
    for (int x : alt) cout << x << " ";
    cout << endl;
    
    cout << "Original interpretation: ";
    for (int x : orig) cout << x << " ";
    cout << endl;
    
    cout << "Expected: 3 1 5 2 4" << endl;
    
    return 0;
}