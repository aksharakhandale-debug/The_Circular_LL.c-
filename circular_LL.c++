#include <iostream>

struct Node {
    int data;
    Node* next;
    
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class CircularLinkedList {
private:
    Node* head;

public:
    CircularLinkedList() {
        head = nullptr;
    }

    // Insert a new node at the end of the circular list
    void insertAtEnd(int val) {
        Node* newNode = new Node(val);
        
        if (head == nullptr) {
            head = newNode;
            newNode->next = head; // Point to itself to maintain circular structure
            return;
        }
        
        Node* temp = head;
        while (temp->next != head) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = head;
    }

    // Delete a node by value
    void deleteValue(int val) {
        if (head == nullptr) {
            std::cout << "List is empty\n";
            return;
        }

        Node *curr = head, *prev = nullptr;

        // If head node itself needs to be deleted
        if (head->data == val) {
            // If it is the only node in the list
            if (head->next == head) {
                delete head;
                head = nullptr;
                return;
            }
            
            // Find the last node to update its next pointer
            Node* last = head;
            while (last->next != head) {
                last = last->next;
            }
            
            Node* temp = head;
            head = head->next;
            last->next = head;
            delete temp;
            return;
        }

        // Traverse the list to find the node to delete
        do {
            prev = curr;
            curr = curr->next;
        } while (curr != head && curr->data != val);

        // If element was found
        if (curr->data == val) {
            prev->next = curr->next;
            delete curr;
        } else {
            std::cout << "Value not found in the list\n";
        }
    }

    // Display all elements in the circular list
    void display() {
        if (head == nullptr) {
            std::cout << "List is empty\n";
            return;
        }
        
        Node* temp = head;
        do {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        } while (temp != head);
        std::cout << "(head)\n";
    }

    // Destructor to properly free memory
    ~CircularLinkedList() {
        if (head == nullptr) return;
        
        Node* curr = head;
        Node* nextNode = nullptr;
        
        // Break the loop to avoid an infinite destruction sequence
        Node* last = head;
        while (last->next != head) {
            last = last->next;
        }
        last->next = nullptr; 

        while (curr != nullptr) {
            nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }
};

int main() {
    CircularLinkedList list;

    list.insertAtEnd(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtEnd(40);
    
    std::cout << "Circular Linked List: ";
    list.display();

    list.deleteValue(20);
    std::cout << "After deleting 20: ";
    list.display();

    return 0;
}
