#include<bits/stdc++.h>
#include<fstream>
#include<unordered_map>

using namespace std;

void showMenu();
void addItem();
void displayItems();
void generateBill();
void updateItem();
void deleteItem();
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
    cout << "4. Update Item\n";
    cout << "5. Delete Item\n";
    cout << "6. Exit\n";
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

unordered_map<string, string> readUserData(const string& filename) {
    unordered_map<string, string> um;
    fstream infile(filename, ios::in);
    string username, password;
    if (infile.is_open()) {
        while (infile >> username >> password) {
            um[username] = password;
        }
        infile.close();
    } else {
        cout << "Error opening file for reading!" << endl;
    }
    return um;
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

    cout << "\nChoose Payment Method:\n";
    cout << "1. Cash\n";
    cout << "2. Credit Card\n";
    cout << "3. Mobile Payment\n";
    int paymentChoice;
    cout << "Enter your choice: ";
    cin >> paymentChoice;

    switch (paymentChoice) {
        case 1:
            cout << "Payment successful. Thank you for paying by cash.\n";
            break;
        case 2: {
            string cardNumber, expiryDate, cvv;
            cout << "Enter Credit Card Number: ";
            cin >> cardNumber;
            cout << "Enter Expiry Date (MM/YY): ";
            cin >> expiryDate;
            cout << "Enter CVV: ";
            cin >> cvv;
            cout << "Payment successful. Thank you for paying by credit card.\n";
            break;
        }
        case 3: {
            string mobileNumber, otp;
            cout << "Enter Mobile Number: ";
            cin >> mobileNumber;
            cout << "Enter OTP: ";
            cin >> otp;
            cout << "Payment successful. Thank you for paying via mobile payment.\n";
            break;
        }
        default:
            cout << "Invalid payment method chosen. Transaction canceled.\n";
            break;
    }
}

void updateItem() {
    cout << "\nEnter item code to update: ";
    int code;
    cin >> code;

    ifstream inFile("items.txt");
    ofstream outFile("temp.txt");
    if (!inFile || !outFile) {
        cout << "Error opening file." << endl;
        return;
    }

    Item item;
    bool found = false;
    char comma;
    while (inFile >> item.itemCode >> comma >> ws &&
           getline(inFile, item.itemName, ',') &&
           inFile >> item.itemPrice >> comma >> item.quantity) {
        if (item.itemCode == code) {
            found = true;
            cout << "\nEnter new item name: ";
            cin.ignore();
            getline(cin, item.itemName);
            cout << "Enter new item price: ";
            cin >> item.itemPrice;
            cout << "Enter new quantity: ";
            cin >> item.quantity;
            cout << "\nItem updated successfully!\n";
        }
        outFile << item.itemCode << "," << item.itemName << ","
                << item.itemPrice << "," << item.quantity << endl;
    }

    inFile.close();
    outFile.close();

    if (!found) {
        cout << "Item not found.\n";
    } else {
        remove("items.txt");
        rename("temp.txt", "items.txt");
    }
}

void deleteItem() {
    cout << "\nEnter item code to delete: ";
    int code;
    cin >> code;

    ifstream inFile("items.txt");
    ofstream outFile("temp.txt");
    if (!inFile || !outFile) {
        cout << "Error opening file." << endl;
        return;
    }

    Item item;
    bool found = false;
    char comma;
    while (inFile >> item.itemCode >> comma >> ws &&
           getline(inFile, item.itemName, ',') &&
           inFile >> item.itemPrice >> comma >> item.quantity) {
        if (item.itemCode == code) {
            found = true;
            cout << "\nItem deleted successfully!\n";
            continue;
        }
        outFile << item.itemCode << "," << item.itemName << ","
                << item.itemPrice << "," << item.quantity << endl;
    }

    inFile.close();
    outFile.close();

    if (!found) {
        cout << "Item not found.\n";
    } else {
        remove("items.txt");
        rename("temp.txt", "items.txt");
    }
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
                updateItem();
                break;
            case 5:
                deleteItem();
                break;
            case 6:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }
    } while (choice != 6);

    return 0;
}


   
 

   


    
  
   
    
       
