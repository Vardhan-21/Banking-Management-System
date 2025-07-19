#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class BankAccount {
    string name;
    int accountNumber;
    double balance;

public:
    BankAccount() {}
    BankAccount(string n, int accNo, double bal) {
        name = n;
        accountNumber = accNo;
        balance = bal;
    }

    void displayAccount() {
        cout << "\nName: " << name
             << "\nAccount Number: " << accountNumber
             << "\nBalance: " << balance << endl;
    }

    int getAccountNumber() { return accountNumber; }

    void deposit(double amount) { balance += amount; }
    bool withdraw(double amount) {
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }

    string toString() {
        return name + "," + to_string(accountNumber) + "," + to_string(balance);
    }

    static BankAccount fromString(string line) {
        string n; int accNo; double bal;
        size_t pos1 = line.find(',');
        size_t pos2 = line.rfind(',');
        n = line.substr(0, pos1);
        accNo = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1));
        bal = stod(line.substr(pos2 + 1));
        return BankAccount(n, accNo, bal);
    }
};

vector<BankAccount> accounts;
string filename = "accounts.txt";

// Save all accounts to file
void saveAccounts() {
    ofstream file(filename);
    for (auto &acc : accounts) {
        file << acc.toString() << endl;
    }
    file.close();
}

// Load accounts from file
void loadAccounts() {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        accounts.push_back(BankAccount::fromString(line));
    }
    file.close();
}

// Find account by account number
int findAccount(int accNo) {
    for (int i = 0; i < accounts.size(); i++) {
        if (accounts[i].getAccountNumber() == accNo) return i;
    }
    return -1;
}

void createAccount() {
    string name;
    int accNo;
    double bal;
    cout << "\nEnter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Account Number: ";
    cin >> accNo;
    cout << "Enter Initial Deposit: ";
    cin >> bal;

    accounts.push_back(BankAccount(name, accNo, bal));
    saveAccounts();
    cout << "✅ Account created successfully!\n";
}

void viewAccount() {
    int accNo;
    cout << "\nEnter Account Number: ";
    cin >> accNo;
    int idx = findAccount(accNo);
    if (idx == -1)
        cout << "❌ Account not found!\n";
    else
        accounts[idx].displayAccount();
}

void depositMoney() {
    int accNo;
    double amount;
    cout << "\nEnter Account Number: ";
    cin >> accNo;
    int idx = findAccount(accNo);
    if (idx == -1) {
        cout << "❌ Account not found!\n";
        return;
    }
    cout << "Enter deposit amount: ";
    cin >> amount;
    accounts[idx].deposit(amount);
    saveAccounts();
    cout << "✅ Deposit successful!\n";
}

void withdrawMoney() {
    int accNo;
    double amount;
    cout << "\nEnter Account Number: ";
    cin >> accNo;
    int idx = findAccount(accNo);
    if (idx == -1) {
        cout << "❌ Account not found!\n";
        return;
    }
    cout << "Enter withdraw amount: ";
    cin >> amount;
    if (accounts[idx].withdraw(amount)) {
        saveAccounts();
        cout << "✅ Withdrawal successful!\n";
    } else {
        cout << "❌ Insufficient balance!\n";
    }
}

int main() {
    loadAccounts();
    int choice;
    do {
        cout << "\n===== Banking Management System =====\n";
        cout << "1. Create Account\n2. View Account\n3. Deposit Money\n4. Withdraw Money\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: viewAccount(); break;
            case 3: depositMoney(); break;
            case 4: withdrawMoney(); break;
            case 5: cout << "\nThank you!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);
    return 0;
}
