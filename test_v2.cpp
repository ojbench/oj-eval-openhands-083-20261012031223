#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Reference implementation using queue for verification
vector<int> josephusQueue(int n, int m) {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        q.push(i);
    }
    
    vector<int> result;
    while (!q.empty()) {
        for (int i = 1; i < m; i++) {
            q.push(q.front());
            q.pop();
        }
        result.push_back(q.front());
        q.pop();
    }
    return result;
}

// Node structure for singly circular linked list
struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* head;
    Node* tail;  // Keep track of tail for easier operations
    int size;
    
public:
    CircularLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    
    // Build circular linked list with n nodes (1 to n)
    void buildList(int n) {
        if (n <= 0) return;
        
        head = new Node(1);
        tail = head;
        
        for (int i = 2; i <= n; i++) {
            tail->next = new Node(i);
            tail = tail->next;
        }
        
        // Make it circular
        tail->next = head;
        size = n;
    }
    
    // Remove the m-th node starting from current position
    // Returns the value of the removed node
    int removeMthNode(int m) {
        if (head == nullptr || size == 0) return -1;
        
        // If only one node left
        if (size == 1) {
            int value = head->data;
            delete head;
            head = nullptr;
            tail = nullptr;
            size = 0;
            return value;
        }
        
        // Special case: m = 1, remove the current head
        if (m == 1) {
            Node* toRemove = head;
            int value = toRemove->data;
            
            // Update head and tail
            head = head->next;
            tail->next = head;
            
            delete toRemove;
            size--;
            
            return value;
        }
        
        // For m > 1, find the (m-1)-th node (node before the one to be removed)
        Node* prev = head;
        
        // Move (m-2) steps to find the node before the one to be removed
        for (int i = 1; i < m - 1; i++) {
            prev = prev->next;
        }
        
        // The node to be removed is prev->next
        Node* toRemove = prev->next;
        int value = toRemove->data;
        
        // Remove the node
        prev->next = toRemove->next;
        
        // Update head if we removed the head
        if (toRemove == head) {
            head = toRemove->next;
        }
        
        // Update tail if we removed the tail
        if (toRemove == tail) {
            tail = prev;
        }
        
        delete toRemove;
        size--;
        
        // The next starting point is the node after the removed one
        head = prev->next;
        
        return value;
    }
    
    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
    
    // Destructor to clean up memory
    ~CircularLinkedList() {
        if (head == nullptr || size == 0) return;
        
        Node* current = head;
        Node* nextNode = nullptr;
        
        // Use size to control the loop
        for (int i = 0; i < size; i++) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
        
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
};

vector<int> josephusCircularList(int n, int m) {
    CircularLinkedList list;
    list.buildList(n);
    
    vector<int> result;
    while (!list.isEmpty()) {
        result.push_back(list.removeMthNode(m));
    }
    return result;
}

int main() {
    // Test various cases
    vector<pair<int, int>> testCases = {
        {1, 1}, {2, 1}, {2, 2}, {3, 1}, {3, 2}, {3, 3},
        {4, 2}, {5, 3}, {6, 4}, {7, 3}, {10, 4}
    };
    
    for (auto testCase : testCases) {
        int n = testCase.first;
        int m = testCase.second;
        
        vector<int> expected = josephusQueue(n, m);
        vector<int> actual = josephusCircularList(n, m);
        
        cout << "n=" << n << ", m=" << m << endl;
        cout << "Expected: ";
        for (int x : expected) cout << x << " ";
        cout << endl;
        cout << "Actual:   ";
        for (int x : actual) cout << x << " ";
        cout << endl;
        
        if (expected == actual) {
            cout << "✓ PASS" << endl;
        } else {
            cout << "✗ FAIL" << endl;
        }
        cout << "---" << endl;
    }
    
    return 0;
}