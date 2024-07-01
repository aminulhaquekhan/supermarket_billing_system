#include <bits/stdc++.h>
#include <iostream>
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

