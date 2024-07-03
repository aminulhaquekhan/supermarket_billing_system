#include <bits/stdc++.h>
#include <fstream>

using namespace std;

void showMenu();
void addItem();
void displayItems();
void generateBill();
bool adminLogin();

struct Item {
    int itemCode;
    string itemName;
    double itemPrice;
    int quantity;
};

void showMenu() {
    cout << "\n===== Supermarket Billing System =====\n";
    cout << "1. Add Item\n";
    cout << "2. Display Items\n";
    cout << "3. Generate Bill\n";
    cout << "4. Exit\n";
    cout << "======================================\n";
}

bool adminLogin() {
    string username, password;
    cout << "Enter admin username: ";
    cin >> username;
    cout << "Enter admin password: ";
    cin >> password;

    if (username == "aminul" && password == "55999") {
        cout << "Login successful.\n";
        return true;
    } else {
        cout << "Login failed. Invalid username or password.\n";
        return false;
    }
}

void addItem() {
    ofstream outFile("items.txt", ios::app);
    if (!outFile) {
        cout << "Error opening file." << endl;
        return;
    }

    Item newItem;
    cout << "\nEnter item code: ";
    cin >> newItem.itemCode;
    cin.ignore();
    cout << "Enter item name: ";
    getline(cin, newItem.itemName);
    cout << "Enter item price: ";
    cin >> newItem.itemPrice;
    cout << "Enter quantity: ";
    cin >> newItem.quantity;

    outFile << newItem.itemCode << "," << newItem.itemName << ","
            << newItem.itemPrice << "," << newItem.quantity << endl;

    cout << "\nItem added successfully!\n";
    outFile.close();
}

void displayItems() {
    cout << "\n===== List of Items =====\n";
    cout << "Code\tName\t\tPrice\tQuantity\n";
    cout << "--------------------------------\n";

    ifstream inFile("items.txt");
    if (!inFile) {
        cout << "Error opening file." << endl;
        return;
    }

    Item item;
    char comma;
    while (inFile >> item.itemCode >> comma >> ws &&
           getline(inFile, item.itemName, ',') &&
           inFile >> item.itemPrice >> comma >> item.quantity) {
        cout << item.itemCode << "\t" << setw(15) << left << item.itemName
             << "\t" << item.itemPrice << "\t" << item.quantity << endl;
    }

    cout << "===========================\n";
    inFile.close();
}

void generateBill() {
    cout << "\n===== Generated Bill =====\n";
    cout << "Code\tName\t\tPrice\tQuantity\tTotal\n";
    cout << "---------------------------------------------\n";

    ifstream inFile("items.txt");
    if (!inFile) {
        cout << "Error opening file." << endl;
        return;
    }

    double totalBill = 0.0;
    Item item;
    char comma;
    while (inFile >> item.itemCode >> comma >> ws &&
           getline(inFile, item.itemName, ',') &&
           inFile >> item.itemPrice >> comma >> item.quantity) {
        double itemTotal = item.itemPrice * item.quantity;
        cout << item.itemCode << "\t" << setw(15) << left << item.itemName
             << "\t" << item.itemPrice << "\t" << item.quantity
             << "\t" << itemTotal << endl;
        totalBill += itemTotal;
    }

    cout << "---------------------------------------------\n";
    cout << "\t\t\t\tTotal Bill: " << totalBill << endl;
    cout << "=============================================\n";
    inFile.close();
}

int main() {
    int choice;

    if (!adminLogin()) {
        cout << "Login failed. Exiting program...\n";
        return 0;
    }

    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addItem();
                break;
            case 2:
                displayItems();
                break;
            case 3:
                generateBill();
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}


