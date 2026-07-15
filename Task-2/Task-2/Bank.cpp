#include "Bank.h"
#include "SavingAccount.h"
#include "CheckingAccount.h"
#include <iostream>
#include <algorithm>

using namespace std;

bool Bank::isAccountNumberUnique(const string& accountNumber) const {
    for (const auto& acc : _accounts) {
        if (acc->getAccountNumber() == accountNumber) {
            return false;
        }
    }
    return true;
}

void Bank::createSavingAccount() {
    string accNum, name;
    double initialBalance, rate;

    cout << "\n========== Create Savings Account ==========\n";
    cout << "Enter Account Number: ";
    cin >> accNum;
    
    //TODO : ADD try again logic. add readAccountNumber function
    if (!isAccountNumberUnique(accNum)) {
        cout << "Error: Account number already exists! Registration failed.\n";
        return;
    }

    cout << "Enter Account Holder Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Initial Balance: $";
    cin >> initialBalance;
    cout << "Enter Interest Rate : ";
    cin >> rate;

    //TODO add read number function
    if (initialBalance < 0 || rate < 0) {
        cout << "Error: Balance and Interest Rate must be positive.\n";
        return;
    }

    _accounts.push_back(make_unique<SavingAccount>(accNum, name, initialBalance, rate));
    cout << "Savings Account created successfully!\n";
}

void Bank::createCheckingAccount() {
    string accNum, name;
    double initialBalance, limit;

    cout << "\n========== Create Checking Account ==========\n";
    cout << "Enter Account Number: ";
    cin >> accNum;

    if (!isAccountNumberUnique(accNum)) {
        cout << "Error: Account number already exists! Registration failed.\n";
        return;
    }

    cout << "Enter Account Holder Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Initial Balance: $";
    cin >> initialBalance;
    cout << "Enter Overdraft Limit: $";
    cin >> limit;

    if (initialBalance < 0 || limit < 0) {
        cout << "Error: Balance and Overdraft Limit must be positive.\n";
        return;
    }

    _accounts.push_back(make_unique<CheckingAccount>(accNum, name, initialBalance, limit));
    cout << "Checking Account created successfully!\n";
}

void Bank::deposit() {
    string accNum;
    double amount;
    cout << "\nEnter Account Number: ";
    cin >> accNum;

    Account* acc = searchByAccountNumber(accNum);
    if (acc != nullptr) {
        cout << "Enter Deposit Amount: $";
        cin >> amount;
        acc->deposit(amount);
    }
    else {
        cout << "Error: Account not found.\n";
    }
}

void Bank::withdraw() {
    string accNum;
    double amount;
    cout << "\nEnter Account Number: ";
    cin >> accNum;

    Account* acc = searchByAccountNumber(accNum);
    if (acc != nullptr) {
        cout << "Enter Withdrawal Amount: $";
        cin >> amount;
        acc->withdraw(amount);
    }
    else {
        cout << "Error: Account not found.\n";
    }
}

Account* Bank::searchByAccountNumber(const string& accountNumber) const {
    for (const auto& acc : _accounts) {
        if (acc->getAccountNumber() == accountNumber) {
            return acc.get(); //return pointer
        }
    }
    return nullptr;
}

void Bank::displayOneAccount() const {
    string accNum;
    cout << "\nEnter Account Number to Display: ";
    cin >> accNum;

    Account* acc = searchByAccountNumber(accNum);
    if (acc != nullptr) {
        acc->displayAccountInfo();
    }
    else {
        cout << "Error: Account not found.\n";
    }
}

void Bank::displayAllAccounts() const {
    if (_accounts.empty()) {
        cout << "\nNo accounts found in the bank database.\n";
        return;
    }
    cout << "\n================ ALL ACCOUNTS ================\n";
    for (const auto& acc : _accounts) {
        acc->displayAccountInfo();
    }
}

void Bank::deleteAccount() {
    string accNum;
    cout << "\nEnter Account Number to Delete: ";
    cin >> accNum;

    auto it = remove_if(_accounts.begin(), _accounts.end(),
        [&accNum](const unique_ptr<Account>& acc) {
            return acc->getAccountNumber() == accNum;
        });

    if (it != _accounts.end()) {
        _accounts.erase(it, _accounts.end());
        cout << "Account " << accNum << " deleted successfully.\n";
    }
    else {
        cout << "Error: Account not found.\n";
    }
}

void Bank::displayMenu() {
    int choice = 0;
    do {
        cout << "\n========== BANK MANAGEMENT ==========\n";
        cout << "1. Create Savings Account\n";
        cout << "2. Create Checking Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Search Account\n";
        cout << "6. Display Account\n";
        cout << "7. Display All Accounts\n";
        cout << "8. Delete Account\n";
        cout << "9. Exit\n";
        cout << "=====================================\n";
        cout << "Enter your choice (1-9): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a valid number.\n";
            continue;
        }

        switch (choice) {
        case 1: createSavingAccount(); break;
        case 2: createCheckingAccount(); break;
        case 3: deposit(); break;
        case 4: withdraw(); break;
        case 5: {
            string accNum;
            cout << "\nEnter Account Number to Search: ";
            cin >> accNum;
            Account* acc = searchByAccountNumber(accNum);
            if (acc) {
                cout << "Success: Account found!\n";
                cout << "Holder Name: " << acc->getAccountHolderName() << " | Balance: $" << acc->getBalance() << "\n";
            }
            else {
                cout << "Error: Account not found.\n";
            }
            break;
        }
        case 6: displayOneAccount(); break;
        case 7: displayAllAccounts(); break;
        case 8: deleteAccount(); break;
        case 9: cout << "Exiting Bank Management System. Goodbye!\n"; break;
        default: cout << "Invalid choice! Please select an option between 1 and 9.\n";
        }
    } while (choice != 9);
}
