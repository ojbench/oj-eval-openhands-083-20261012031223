#include <iostream>
using namespace std;

// Node structure for singly circular linked list
struct Node {
    int data;
    Node* next;
    
    Node(int val) : data(val), next(nullptr) {}
};

class CircularLinkedList {
private:
    Node* head;
    int size;
    
public:
    CircularLinkedList() : head(nullptr), size(0) {}
    
    // Build circular linked list with n nodes (1 to n)
    void buildList(int n) {
        if (n <= 0) return;
        
        head = new Node(1);
        Node* current = head;
        
        for (int i = 2; i <= n; i++) {
            current->next = new Node(i);
            current = current->next;
        }
        
        // Make it circular
        current->next = head;
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
            size = 0;
            return value;
        }
        
        // Special case: m = 1, remove the current head
        if (m == 1) {
            Node* toRemove = head;
            int value = toRemove->data;
            
            // Find the last node to update its next pointer
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }
            
            // Update pointers
            last->next = head->next;
            head = head->next;
            
            delete toRemove;
            size--;
            
            return value;
        }
        
        // For m > 1, find the (m-1)-th node (node before the one to be removed)
        Node* prev = head;
        
        // Move (m-2) steps to find the node before the one to be removed
        // Since we start counting from head, we need to move m-2 steps
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
        
        // Break the circular link to avoid infinite loop
        // Use size to control the loop instead of comparing with head
        for (int i = 0; i < size; i++) {
            nextNode = current->next;
            delete current;
            current = nextNode;
        }
        
        head = nullptr;
        size = 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    if (!(cin >> n >> m)) {
        return 0;
    }
    
    CircularLinkedList list;
    list.buildList(n);
    
    // Simulate Josephus ring elimination
    while (!list.isEmpty()) {
        int removed = list.removeMthNode(m);
        cout << removed << "\n";
    }
    
    return 0;
}