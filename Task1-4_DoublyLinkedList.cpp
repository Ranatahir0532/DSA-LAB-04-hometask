#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
    Node* head, *tail;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void displayForward() {
        Node* p = head;
        while (p) {
            cout << p->data;
            if (p->next) cout << " <-> ";
            p = p->next;
        }
        cout << '\n';
    }

    void displayBackward() {
        Node* p = tail;
        while (p) {
            cout << p->data;
            if (p->prev) cout << " <-> ";
            p = p->prev;
        }
        cout << '\n';
    }

    void insertAtStart(int val) {
        Node* n = new Node(val);
        if (!head) head = tail = n;
        else { n->next = head; head->prev = n; head = n; }
    }

    void insertAtEnd(int val) {
        Node* n = new Node(val);
        if (!tail) head = tail = n;
        else { n->prev = tail; tail->next = n; tail = n; }
    }

    void insertAtPosition(int pos, int val) {
        if (pos < 0) { cout << "Invalid position.\n"; return; }
        if (pos == 0) { insertAtStart(val); return; }

        Node* cur = head;
        int i = 0;
        while (cur && i < pos) { cur = cur->next; ++i; }

        if (!cur) {
            if (i == pos) insertAtEnd(val);
            else cout << "Position out of range.\n";
            return;
        }

        Node* n = new Node(val);
        n->prev = cur->prev;
        n->next = cur;
        cur->prev->next = n;
        cur->prev = n;
    }

    void deleteFromStart() {
        if (!head) { cout << "List is empty.\n"; return; }
        Node* temp = head;
        if (head == tail) head = tail = nullptr;
        else { head = head->next; head->prev = nullptr; }
        delete temp;
    }

    void deleteFromEnd() {
        if (!tail) { cout << "List is empty.\n"; return; }
        Node* temp = tail;
        if (head == tail) head = tail = nullptr;
        else { tail = tail->prev; tail->next = nullptr; }
        delete temp;
    }

    void deleteValue(int val) {
        Node* cur = head;
        while (cur && cur->data != val) cur = cur->next;
        if (!cur) { cout << "Value not found.\n"; return; }

        if (cur == head) { deleteFromStart(); return; }
        if (cur == tail) { deleteFromEnd(); return; }

        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
        delete cur;
    }

    void reverse() {
        Node* cur = head;

        // Swap next/prev for every node; no new list is created.
        while (cur) {
            Node* next = cur->next;
            cur->next = cur->prev;
            cur->prev = next;
            cur = next;
        }

        // Old head becomes tail and old tail becomes head.
        Node* temp = head;
        head = tail;
        tail = temp;
    }
};

int main() {
    DoublyLinkedList list;

    list.insertAtEnd(10);
    list.insertAtEnd(30);
    list.insertAtPosition(1, 20);

    cout << "Forward:  "; list.displayForward();
    cout << "Backward: "; list.displayBackward();

    list.insertAtStart(5);
    list.insertAtEnd(40);
    list.deleteValue(20);
    list.deleteFromStart();
    list.deleteFromEnd();

    cout << "After deletions: "; list.displayForward();

    list.reverse();
    cout << "After reverse:   "; list.displayForward();
    cout << "Backward:        "; list.displayBackward();

    return 0;
}
