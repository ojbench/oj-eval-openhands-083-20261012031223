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
        
        // Find the (m-1)-th node (node before the one to be removed)
        Node* prev = nullptr;
        Node* current = head;
        
        // Move (m-1) steps from current position
        for (int i = 1; i < m; i++) {
            prev = current;
            current = current->next;
        }
        
        // Remove current node
        int value = current->data;
        prev->next = current->next;
        
        // Update head if we removed the head
        if (current == head) {
            head = current->next;
        }
        
        delete current;
        size--;
        
        // Return the next node as the new starting point
        head = prev->next;
        
        return value;
    }
    
    int getSize() const { return size; }
    bool isEmpty() const { return size == 0; }
    
    // Destructor to clean up memory
    ~CircularLinkedList() {
        if (head == nullptr) return;
        
        Node* current = head;
        Node* nextNode = nullptr;
        
        // Break the circular link to avoid infinite loop
        do {
            nextNode = current->next;
            delete current;
            current = nextNode;
        } while (current != head);
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    
    CircularLinkedList list;
    list.buildList(n);
    
    // Simulate Josephus ring elimination
    while (!list.isEmpty()) {
        int removed = list.removeMthNode(m);
        cout << removed << endl;
    }
    
    return 0;
}