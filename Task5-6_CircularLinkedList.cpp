#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class CircularLinkedList {
    Node* head;
public:
    CircularLinkedList() : head(nullptr) {}

    void display() {
        if (!head) { cout << "List is empty.\n"; return; }

        Node* cur = head;
        // Stop when cur reaches head again so the loop runs exactly once around.
        do {
            cout << cur->data;
            cur = cur->next;
            if (cur != head) cout << " -> ";
        } while (cur != head);
        cout << " -> HEAD\n";
    }

    void append(int val) {
        Node* n = new Node(val);
        if (!head) {
            head = n;
            n->next = head;
            return;
        }

        Node* last = head;
        while (last->next != head) last = last->next;
        last->next = n;
        n->next = head;
    }

    void insert(int pos, int val) {
        if (pos < 0) { cout << "Invalid position.\n"; return; }

        if (pos == 0) {
            Node* n = new Node(val);
            if (!head) { head = n; n->next = head; return; }

            Node* last = head;
            while (last->next != head) last = last->next;
            n->next = head;
            last->next = n;
            head = n;
            return;
        }

        if (!head) { cout << "Position out of range.\n"; return; }

        Node* cur = head;
        int i = 0;
        while (i < pos - 1 && cur->next != head) { cur = cur->next; ++i; }

        if (i != pos - 1) { cout << "Position out of range.\n"; return; }

        Node* n = new Node(val);
        n->next = cur->next;
        cur->next = n;
    }

    void deleteValue(int val) {
        if (!head) { cout << "List is empty.\n"; return; }

        if (head->data == val) {
            if (head->next == head) {
                delete head;
                head = nullptr;
                return;
            }

            Node* last = head;
            while (last->next != head) last = last->next;

            Node* temp = head;
            head = head->next;
            last->next = head;
            delete temp;
            return;
        }

        Node* prev = head;
        Node* cur = head->next;

        while (cur != head && cur->data != val) {
            prev = cur;
            cur = cur->next;
        }

        if (cur == head) { cout << "Value not found.\n"; return; }

        prev->next = cur->next;
        delete cur;
    }

    bool search(int key) {
        if (!head) return false;

        Node* cur = head;
        do {
            if (cur->data == key) return true;
            cur = cur->next;
        } while (cur != head);

        return false;
    }
};

int main() {
    CircularLinkedList list;

    list.append(10);
    list.append(20);
    list.append(30);
    cout << "Initial: "; list.display();

    list.insert(1, 15);
    cout << "After insert: "; list.display();

    cout << "Search 20: " << (list.search(20) ? "Found" : "Not Found") << '\n';
    cout << "Search 50: " << (list.search(50) ? "Found" : "Not Found") << '\n';

    list.deleteValue(10);
    cout << "After deleting 10: "; list.display();

    return 0;
}
