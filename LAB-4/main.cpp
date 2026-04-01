#include <iostream>
#include <string>

using namespace std;

struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3];
    MoneyBundle* next;
};

class MoneyStack {
private:
    MoneyBundle* top;

public:
    MoneyStack() : top(nullptr) {}

    void push(string serial, string currency, int b100, int b50, int b20) {
        MoneyBundle* newNode = new MoneyBundle{serial, currency, {b100, b50, b20}, top};
        top = newNode;
    }

    bool pop(MoneyBundle& bundle) {
        if (top == nullptr) return false;
        
        bundle = *top;
        MoneyBundle* temp = top;
        top = top->next;
        delete temp;
        
        return true;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    void display() {
        cout << "--- Safe (Money Bundles) ---\n";
        if (top == nullptr) {
            cout << "Safe is empty.\n";
            return;
        }
        MoneyBundle* current = top;
        while (current != nullptr) {
            cout << "Bundle SN: " << current->serialNumber 
                 << " [" << current->currencyType << "] -> "
                 << "100s: " << current->billCounts[0] << ", "
                 << "50s: " << current->billCounts[1] << ", "
                 << "20s: " << current->billCounts[2] << "\n";
            current = current->next;
        }
    }
};

struct Customer {
    string customerName;
    string transactionType;
};

class CustomerQueue {
private:
    Customer queue[5];
    int front;
    int rear;
    int count;

public:
    CustomerQueue() : front(0), rear(0), count(0) {}

    void enqueue(string name, string type) {
        if (count == 5) {
            cout << "Queue is full. Cannot add customer.\n";
            return;
        }
        queue[rear] = {name, type};
        rear = (rear + 1) % 5;
        count++;
    }

    bool dequeue(Customer& customer) {
        if (count == 0) return false;
        
        customer = queue[front];
        front = (front + 1) % 5;
        count--;
        
        return true;
    }

    bool isEmpty() {
        return count == 0;
    }

    void display() {
        cout << "--- Customer Queue ---\n";
        if (count == 0) {
            cout << "No customers waiting.\n";
            return;
        }
        for (int i = 0; i < count; i++) {
            int index = (front + i) % 5;
            cout << "Customer: " << queue[index].customerName 
                 << " | Transaction: " << queue[index].transactionType << "\n";
        }
    }
};

void processTransaction(MoneyStack& safe, CustomerQueue& line) {
    if (safe.isEmpty() || line.isEmpty()) {
        cout << "Cannot process transaction. Either safe or line is empty.\n";
        return;
    }

    Customer currentCustomer;
    MoneyBundle currentBundle;

    line.dequeue(currentCustomer);
    safe.pop(currentBundle);

    cout << "Processed " << currentCustomer.transactionType 
         << " for " << currentCustomer.customerName 
         << " using Bundle " << currentBundle.serialNumber << "\n";
}

int main() {
    MoneyStack safe;
    CustomerQueue line;
    int choice = 0;

    while (choice != 5) {
        cout << "\n=== Bank Branch Management System ===\n";
        cout << "1. Receive Money Bundle (Push)\n";
        cout << "2. New Customer (Enqueue)\n";
        cout << "3. Process Transaction\n";
        cout << "4. Display Status\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string serial, currency;
            int b100, b50, b20;
            cout << "Enter Serial Number: ";
            cin >> serial;
            cout << "Enter Currency Type: ";
            cin >> currency;
            cout << "Enter count of 100s: ";
            cin >> b100;
            cout << "Enter count of 50s: ";
            cin >> b50;
            cout << "Enter count of 20s: ";
            cin >> b20;
            safe.push(serial, currency, b100, b50, b20);
        } else if (choice == 2) {
            string name, type;
            cout << "Enter Customer Name: ";
            cin >> name;
            cout << "Enter Transaction Type: ";
            cin >> type;
            line.enqueue(name, type);
        } else if (choice == 3) {
            processTransaction(safe, line);
        } else if (choice == 4) {
            safe.display();
            cout << "\n";
            line.display();
        } else if (choice == 5) {
            cout << "Exiting...\n";
        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
