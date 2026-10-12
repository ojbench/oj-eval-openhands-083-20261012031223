#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }
    
    // Build circular linked list
    Node* head = new Node(1);
    Node* current = head;
    
    for (int i = 2; i <= n; i++) {
        current->next = new Node(i);
        current = current->next;
    }
    current->next = head;  // Make it circular
    
    Node* prev = current;  // prev points to the last node initially
    
    // Start from head (node 1)
    current = head;
    int remaining = n;
    
    while (remaining > 0) {
        // Count m-1 steps to find the node before the one to remove
        for (int i = 1; i < m; i++) {
            prev = current;
            current = current->next;
        }
        
        // Remove current node
        cout << current->data << "\n";
        prev->next = current->next;
        
        Node* toDelete = current;
        current = current->next;  // Next starting point
        delete toDelete;
        remaining--;
    }
    
    return 0;
}