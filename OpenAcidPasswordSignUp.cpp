#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

unordered_map<string, string> loadUsers(const string& filename) {
    unordered_map<string, string> users;
    ifstream file(filename);
    string username, password;

    while (file >> username >> password) {
        users[username] = password;
    }

    return users;
}

void saveUser(const string& filename, const string& username, const string& password) {
    ofstream file(filename, ios::app);
    file << username << " " << password << endl;
}

bool authenticateUser(const unordered_map<string, string>& users, const string& username, const string& password) {
    auto it = users.find(username);
    return it != users.end() && it->second == password;
}

int main() {
    const string filename = "users.txt";
    unordered_map<string, string> users = loadUsers(filename);

    int option;
    string username, password;

    cout << "=== Username & Password Manager ===\n";
    cout << "1. Login\n2. Sign up\nEnter choice: ";
    cin >> option;

    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (option == 1) {
        if (authenticateUser(users, username, password)) {
            cout << "\nLogin successful!\n";
        } else {
            cout << "\nAuthentication failed. Incorrect username or password.\n";
        }
    } else if (option == 2) {
        if (users.find(username) != users.end()) {
            cout << "\nUsername already exists. Please choose another.\n";
        } else {
            saveUser(filename, username, password);
            cout << "\nUser registered successfully.\n";
        }
    } else {
        cout << "\nInvalid option.\n";
    }

    return 0;
}
