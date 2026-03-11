#include <iostream>
#include <string>

// Define the Node struct for the Singly Linked List
struct Node {
    std::string songTitle;
    Node* next;
};

// Function to add a new song to the beginning of the list (Prepend)
void addSong(Node*& head, const std::string& title) {
    // Create a new node
    Node* newNode = new Node();
    newNode->songTitle = title;
    
    // Point the new node's next to the current head
    newNode->next = head;
    
    // Update head to point to the new node
    head = newNode;
    
    std::cout << "\"" << title << "\" has been added to the top of the playlist.\n";
}

// Function to search for a specific song title in the list
void searchSong(Node* head, const std::string& title) {
    Node* current = head;
    int position = 1;
    bool found = false;

    while (current != nullptr) {
        if (current->songTitle == title) {
            std::cout << "Found: \"" << title << "\" is at position " << position << " in the playlist.\n";
            found = true;
            break;
        }
        current = current->next;
        position++;
    }

    if (!found) {
        std::cout << "Not Found: \"" << title << "\" is not in the playlist.\n";
    }
}

// Function to list all songs in the playlist with their order numbers
void listSongs(Node* head) {
    if (head == nullptr) {
        std::cout << "The playlist is currently empty.\n";
        return;
    }

    Node* current = head;
    int order = 1;
    
    std::cout << "\n--- Current Playlist ---\n";
    while (current != nullptr) {
        std::cout << order << ". " << current->songTitle << "\n";
        current = current->next;
        order++;
    }
    std::cout << "------------------------\n";
}

// Helper function to free allocated memory before exiting
void freePlaylist(Node*& head) {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
}

int main() {
    Node* playlistHead = nullptr; // Initialize an empty playlist
    int choice = 0;
    std::string inputTitle;

    std::cout << "Welcome to the Playlist Manager!\n";

    while (choice != 4) {
        // Display Main Menu
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Add Song\n";
        std::cout << "2. Search Song\n";
        std::cout << "3. List Songs\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice (1-4): ";
        
        std::cin >> choice;

        // Handle invalid non-integer inputs
        if (std::cin.fail()) {
            std::cin.clear(); // clear error flags
            std::cin.ignore(10000, '\n'); // discard bad input
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        std::cin.ignore(); // Clear the newline character from the input buffer

        switch (choice) {
            case 1:
                std::cout << "Enter the song title to add: ";
                std::getline(std::cin, inputTitle);
                addSong(playlistHead, inputTitle);
                break;
            case 2:
                std::cout << "Enter the song title to search for: ";
                std::getline(std::cin, inputTitle);
                searchSong(playlistHead, inputTitle);
                break;
            case 3:
                listSongs(playlistHead);
                break;
            case 4:
                std::cout << "Exiting program. Cleaning up memory...\n";
                freePlaylist(playlistHead);
                break;
            default:
                std::cout << "Invalid choice. Please select an option from 1 to 4.\n";
        }
    }

    return 0;
}
