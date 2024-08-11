#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Class to represent a single transaction
class Transaction {
private:
    string type;
    double amount;

public:
    Transaction(string t, double amt) : type(t), amount(amt) {}

    void display() const {
        cout << "Transaction: " << type << " | Amount: " << amount << endl;
    }
};

// Class to represent a user account
class Account {
private:
    string username;
    string password;
    int accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(string user, string pass, int accNum, double bal)
        : username(user), password(pass), accountNumber(accNum), balance(bal) {}

    bool authenticate(string enteredUsername, string enteredPassword) {
        return (enteredUsername == username && enteredPassword == password);
    }

    void deposit(double amount) {
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        cout << "Deposit successful. New balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
        } else {
            balance -= amount;
            transactions.emplace_back("Withdraw", amount);
            cout << "Withdrawal successful. New balance: " << balance << endl;
        }
    }

    void checkBalance() const {
        cout << "Current balance: " << balance << endl;
    }

    void displayTransactions() const {
        if (transactions.empty()) {
            cout << "No transactions available." << endl;
        } else {
            for (const auto& transaction : transactions) {
                transaction.display();
            }
        }
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    string getUsername() const {
        return username;
    }
};

// Class to manage multiple accounts and ATM operations
class ATM {
private:
    vector<Account> accounts;
    int nextAccountNumber;

    Account* findAccount(string username) {
        for (auto& account : accounts) {
            if (account.getUsername() == username) {
                return &account;
            }
        }
        return nullptr;
    }

public:
    ATM() : nextAccountNumber(1000) {}

    void signUp() {
        string username, password;
        double initialDeposit;

        cout << "Enter a username: ";
        cin >> username;
        cout << "Enter a password: ";
        cin >> password;
        cout << "Enter initial deposit amount: ";
        cin >> initialDeposit;

        Account newAccount(username, password, nextAccountNumber++, initialDeposit);
        accounts.push_back(newAccount);
        cout << "Account created successfully! Your account number is: " << newAccount.getAccountNumber() << endl;
    }

    void login() {
        string username, password;
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        Account* account = findAccount(username);
        if (account && account->authenticate(username, password)) {
            int choice;
            do {
                cout << "\n1. Check Balance\n2. Deposit\n3. Withdraw\n4. View Transactions\n5. Logout\n";
                cout << "Choose an option: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        account->checkBalance();
                        break;
                    case 2: {
                        double amount;
                        cout << "Enter deposit amount: ";
                        cin >> amount;
                        account->deposit(amount);
                        break;
                    }
                    case 3: {
                        double amount;
                        cout << "Enter withdrawal amount: ";
                        cin >> amount;
                        account->withdraw(amount);
                        break;
                    }
                    case 4:
                        account->displayTransactions();
                        break;
                    case 5:
                        cout << "Logged out successfully!" << endl;
                        break;
                    default:
                        cout << "Invalid option! Try again." << endl;
                }
            } while (choice != 5);
        } else {
            cout << "Authentication failed! Incorrect username or password." << endl;
        }
    }

    void run() {
        int choice;
        do {
            cout << "\n1. Sign Up\n2. Login\n3. Exit\n";
            cout << "Choose an option: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    signUp();
                    break;
                case 2:
                    login();
                    break;
                case 3:
                    cout << "Thank you for using the ATM!" << endl;
                    break;
                default:
                    cout << "Invalid option! Try again." << endl;
            }
        } while (choice != 3);
    }
};

int main() {
    ATM atm;
    atm.run();
    return 0;
}
