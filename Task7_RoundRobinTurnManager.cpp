#include <iostream>
#include <string>
using namespace std;

struct PlayerNode {
    string name;
    PlayerNode* next;
    PlayerNode(string n) : name(n), next(nullptr) {}
};

class RoundRobin {
    PlayerNode* head;
    PlayerNode* current;
public:
    RoundRobin() : head(nullptr), current(nullptr) {}

    void addPlayer(const string& name) {
        PlayerNode* n = new PlayerNode(name);

        if (!head) {
            head = n;
            n->next = head;
            current = head;
            return;
        }

        PlayerNode* last = head;
        while (last->next != head) last = last->next;
        last->next = n;
        n->next = head;
    }

    string nextTurn() {
        if (!current) return "No players";
        current = current->next;
        return current->name;
    }

    void removePlayer(const string& name) {
        if (!head) return;

        if (head->next == head && head->name == name) {
            delete head;
            head = current = nullptr;
            return;
        }

        PlayerNode* prev = head;
        PlayerNode* target = head;

        while (target->name != name && target->next != head) {
            prev = target;
            target = target->next;
        }

        if (target->name != name) {
            cout << name << " not found.\n";
            return;
        }

        if (target == head) {
            while (prev->next != head) prev = prev->next;
            head = head->next;
            prev->next = head;
            if (current == target) current = head;
            delete target;
            return;
        }

        prev->next = target->next;

        // If the active player leaves, continue from the next player.
        if (current == target) current = target->next;

        delete target;
    }

    void displayPlayers() {
        if (!head) { cout << "No players.\n"; return; }

        PlayerNode* p = head;
        do {
            cout << p->name;
            p = p->next;
            if (p != head) cout << " -> ";
        } while (p != head);
        cout << '\n';
    }
};

int main() {
    RoundRobin game;

    game.addPlayer("Ali");
    game.addPlayer("Beena");
    game.addPlayer("Cara");

    cout << "Players: ";
    game.displayPlayers();

    cout << "\nNext turns:\n";
    // Starting at Ali, these calls print Beena, Cara, Ali, Beena.
    cout << game.nextTurn() << '\n';
    cout << game.nextTurn() << '\n';
    cout << game.nextTurn() << '\n';
    cout << game.nextTurn() << '\n';

    game.removePlayer("Beena");

    cout << "\nAfter removing Beena:\n";
    game.displayPlayers();

    cout << "Next turn: " << game.nextTurn() << '\n';
    cout << "Next turn: " << game.nextTurn() << '\n';

    return 0;
}
