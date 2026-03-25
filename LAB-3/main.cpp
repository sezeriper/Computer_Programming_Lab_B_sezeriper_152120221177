#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// 1. Structure Definition
struct Page {
    string url;
    string title;
    int accessTime[3]; // {Hour, Minute, Second}
    Page *next;
    Page *prev;
};

class BrowserHistory {
private:
    Page* head;
    Page* tail;
    Page* current;

    // Helper to delete all forward history when a new page is visited from the middle of the list
    void clearForwardHistory() {
        if (!current || !current->next) return;
        
        Page* temp = current->next;
        while (temp != nullptr) {
            Page* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        current->next = nullptr;
        tail = current;
    }

public:
    BrowserHistory() {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    // Memory Management: Destructor to clean up all nodes
    ~BrowserHistory() {
        clearHistory();
    }

    void clearHistory() {
        Page* temp = head;
        while (temp != nullptr) {
            Page* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        head = tail = current = nullptr;
        cout << "Memory cleared successfully." << endl;
    }

    // 2. Required Functions

    // Visit (Append): Add a new page to the history.
    void visit(string u, string t, int h, int m, int s) {
        Page* newPage = new Page;
        newPage->url = u;
        newPage->title = t;
        newPage->accessTime[0] = h;
        newPage->accessTime[1] = m;
        newPage->accessTime[2] = s;
        newPage->next = nullptr;
        newPage->prev = nullptr;

        if (head == nullptr) {
            // Empty list
            head = tail = current = newPage;
        } else {
            // Standard browser behavior: visiting a new page clears forward history
            clearForwardHistory();
            
            current->next = newPage;
            newPage->prev = current;
            tail = newPage;
            current = newPage;
        }
        cout << "Visited: " << u << endl;
    }

    // Back: Move current pointer to previous page
    void back() {
        if (current != nullptr && current->prev != nullptr) {
            current = current->prev;
            cout << "Going back to: " << current->url << endl;
        } else {
            cout << "No previous history to go back to." << endl;
        }
    }

    // Forward: Move current pointer to next page
    void forward() {
        if (current != nullptr && current->next != nullptr) {
            current = current->next;
            cout << "Going forward to: " << current->url << endl;
        } else {
            cout << "No forward history available." << endl;
        }
    }

    // Delete Entry: Remove current page and reconnect nodes
    void deleteCurrentEntry() {
        if (current == nullptr) {
            cout << "History is empty." << endl;
            return;
        }

        Page* toDelete = current;
        cout << "Deleting entry: " << toDelete->url << endl;

        // Reconnect surrounding nodes
        if (toDelete->prev != nullptr) {
            toDelete->prev->next = toDelete->next;
        } else {
            head = toDelete->next; // We are deleting the head
        }

        if (toDelete->next != nullptr) {
            toDelete->next->prev = toDelete->prev;
        } else {
            tail = toDelete->prev; // We are deleting the tail
        }

        // Update current pointer
        if (toDelete->prev != nullptr) {
            current = toDelete->prev; // Default fallback to previous
        } else {
            current = toDelete->next; // If no previous, fall forward
        }

        delete toDelete;
    }

    // Display History: Print all pages, formatting time with a for loop
    void displayHistory() {
        if (head == nullptr) {
            cout << "Browser history is empty." << endl;
            return;
        }

        cout << "\n--- Browser History ---" << endl;
        Page* temp = head;
        while (temp != nullptr) {
            // Highlight the current page
            if (temp == current) {
                cout << " => ";
            } else {
                cout << "    ";
            }

            cout << temp->title << " (" << temp->url << ")";

            // Formatting time using the required for loop
            cout << " [Visited at: ";
            for (int i = 0; i < 3; ++i) {
                cout << setfill('0') << setw(2) << temp->accessTime[i];
                if (i < 2) cout << ":"; // Add colon between HH:MM:SS
            }
            cout << "]" << endl;

            temp = temp->next;
        }
        cout << "-----------------------\n" << endl;
    }
};

int main() {
    BrowserHistory browser;
    string command;

    cout << "Welcome to the DLL Browser History Manager!" << endl;
    cout << "Commands: VISIT, BACK, FORWARD, DELETE, DISPLAY, EXIT" << endl;

    // Simulating some initial visits so you don't have to type them all out immediately
    browser.visit("google.com", "Google Search", 10, 15, 30);
    browser.visit("github.com", "GitHub", 10, 17, 45);
    browser.visit("stackoverflow.com", "Stack Overflow", 10, 22, 10);

    while (true) {
        cout << "\nEnter command: ";
        cin >> command;

        // Convert command to uppercase for easier matching
        for (char &c : command) c = toupper(c);

        if (command == "VISIT") {
            string url, title;
            int h, m, s;
            cout << "Enter URL: "; cin >> url;
            cout << "Enter Title (single word for simplicity): "; cin >> title;
            cout << "Enter Hour, Minute, Second (separated by spaces): "; cin >> h >> m >> s;
            browser.visit(url, title, h, m, s);
        } 
        else if (command == "BACK") {
            browser.back();
        } 
        else if (command == "FORWARD") {
            browser.forward();
        } 
        else if (command == "DELETE") {
            browser.deleteCurrentEntry();
        } 
        else if (command == "DISPLAY") {
            browser.displayHistory();
        } 
        else if (command == "EXIT") {
            cout << "Exiting browser..." << endl;
            // The class destructor ~BrowserHistory() will automatically handle clearing memory here,
            // but we can call it explicitly if we want to confirm the message before the program halts.
            browser.clearHistory();
            break;
        } 
        else {
            cout << "Invalid command." << endl;
        }
    }

    return 0;
}
