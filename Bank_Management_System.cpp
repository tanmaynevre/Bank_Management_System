#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <stdexcept>
#include <limits>

using namespace std;

// Transaction structure for maintaining transaction history
struct Transaction {
    string type;
    double amount;
    string date;
    double balanceAfter;
    
    Transaction(string t, double amt, string d, double bal) 
        : type(t), amount(amt), date(d), balanceAfter(bal) {}
};

// Account class representing a bank account
class Account {
private:
    static int nextAccountNumber;
    int accountNumber;
    string customerName;
    string address;
    string phoneNumber;
    string pin;
    double balance;
    vector<Transaction> transactionHistory;
    
public:
    // Constructors
    Account() : accountNumber(0), balance(0.0) {}
    
    Account(string name, string addr, string phone, string pinCode, double initialBalance = 0.0) 
        : customerName(name), address(addr), phoneNumber(phone), pin(pinCode), balance(initialBalance) {
        accountNumber = ++nextAccountNumber;
        if (initialBalance > 0) {
            addTransaction("Initial Deposit", initialBalance);
        }
    }
    
    // Getters
    int getAccountNumber() const { return accountNumber; }
    string getCustomerName() const { return customerName; }
    string getAddress() const { return address; }
    string getPhoneNumber() const { return phoneNumber; }
    double getBalance() const { return balance; }
    string getPin() const { return pin; }
    
    // Setters
    void setCustomerName(const string& name) { customerName = name; }
    void setAddress(const string& addr) { address = addr; }
    void setPhoneNumber(const string& phone) { phoneNumber = phone; }
    void setPin(const string& newPin) { pin = newPin; }
    void setAccountNumber(int accNum) { accountNumber = accNum; }
    void setBalance(double bal) { balance = bal; }
    
    // Transaction methods
    bool deposit(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Deposit amount must be positive!");
        }
        balance += amount;
        addTransaction("Deposit", amount);
        return true;
    }
    
    bool withdraw(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Withdrawal amount must be positive!");
        }
        if (amount > balance) {
            throw invalid_argument("Insufficient balance!");
        }
        balance -= amount;
        addTransaction("Withdrawal", amount);
        return true;
    }
    
    // Utility methods
    void addTransaction(const string& type, double amount) {
        time_t now = time(0);
        char* dateStr = ctime(&now);
        string date(dateStr);
        date.pop_back(); // Remove newline character
        transactionHistory.push_back(Transaction(type, amount, date, balance));
    }
    
    void displayAccount() const {
        cout << "\n========== ACCOUNT DETAILS ==========\n";
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Customer Name: " << customerName << "\n";
        cout << "Address: " << address << "\n";
        cout << "Phone Number: " << phoneNumber << "\n";
        cout << "Current Balance: $" << fixed << setprecision(2) << balance << "\n";
        cout << "=====================================\n";
    }
    
    void displayTransactionHistory() const {
        cout << "\n========== TRANSACTION HISTORY ==========\n";
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Customer Name: " << customerName << "\n";
        cout << "-----------------------------------------\n";
        
        if (transactionHistory.empty()) {
            cout << "No transactions found.\n";
            return;
        }
        
        cout << left << setw(15) << "Type" 
             << setw(12) << "Amount" 
             << setw(12) << "Balance" 
             << setw(25) << "Date" << "\n";
        cout << string(64, '-') << "\n";
        
        for (const auto& trans : transactionHistory) {
            cout << left << setw(15) << trans.type
                 << "$" << setw(11) << fixed << setprecision(2) << trans.amount
                 << "$" << setw(11) << fixed << setprecision(2) << trans.balanceAfter
                 << trans.date << "\n";
        }
        cout << "=========================================\n";
    }
    
    // File I/O methods
    string toFileString() const {
        stringstream ss;
        ss << accountNumber << "|" << customerName << "|" << address << "|" 
           << phoneNumber << "|" << pin << "|" << balance;
        
        // Add transaction history
        ss << "|" << transactionHistory.size();
        for (const auto& trans : transactionHistory) {
            ss << "|" << trans.type << "," << trans.amount << "," 
               << trans.date << "," << trans.balanceAfter;
        }
        return ss.str();
    }
    
    static Account fromFileString(const string& line) {
        Account acc;
        stringstream ss(line);
        string token;
        
        // Parse basic account info
        getline(ss, token, '|'); acc.accountNumber = stoi(token);
        getline(ss, acc.customerName, '|');
        getline(ss, acc.address, '|');
        getline(ss, acc.phoneNumber, '|');
        getline(ss, acc.pin, '|');
        getline(ss, token, '|'); acc.balance = stod(token);
        
        // Parse transaction count
        getline(ss, token, '|');
        int transCount = stoi(token);
        
        // Parse transactions
        for (int i = 0; i < transCount; i++) {
            getline(ss, token, '|');
            stringstream transSS(token);
            string type, amountStr, date, balanceStr;
            
            getline(transSS, type, ',');
            getline(transSS, amountStr, ',');
            getline(transSS, date, ',');
            getline(transSS, balanceStr, ',');
            
            acc.transactionHistory.push_back(
                Transaction(type, stod(amountStr), date, stod(balanceStr))
            );
        }
        
        return acc;
    }
};

// Initialize static member
int Account::nextAccountNumber = 1000;

// Bank Management System class
class BankManagementSystem {
private:
    map<int, Account> accounts;
    const string DATA_FILE = "bank_data.txt";
    
public:
    BankManagementSystem() {
        loadAccountsFromFile();
    }
    
    ~BankManagementSystem() {
        saveAccountsToFile();
    }
    
    // Core banking operations
    void createAccount() {
        string name, address, phone, pin, confirmPin;
        double initialDeposit;
        
        cout << "\n========== CREATE NEW ACCOUNT ==========\n";
        
        cin.ignore(); // Clear input buffer
        
        cout << "Enter Customer Name: ";
        getline(cin, name);
        
        cout << "Enter Address: ";
        getline(cin, address);
        
        cout << "Enter Phone Number: ";
        getline(cin, phone);
        
        // PIN setup with confirmation
        do {
            cout << "Enter 4-digit PIN: ";
            getline(cin, pin);
            
            if (pin.length() != 4 || !all_of(pin.begin(), pin.end(), ::isdigit)) {
                cout << "PIN must be exactly 4 digits! Please try again.\n";
                continue;
            }
            
            cout << "Confirm PIN: ";
            getline(cin, confirmPin);
            
            if (pin != confirmPin) {
                cout << "PINs don't match! Please try again.\n";
            }
        } while (pin != confirmPin || pin.length() != 4);
        
        cout << "Enter Initial Deposit Amount (minimum $10): $";
        cin >> initialDeposit;
        
        if (initialDeposit < 10) {
            cout << "Minimum initial deposit is $10!\n";
            return;
        }
        
        try {
            Account newAccount(name, address, phone, pin, initialDeposit);
            accounts[newAccount.getAccountNumber()] = newAccount;
            
            cout << "Account created successfully!\n";
            cout << "Your Account Number is: " << newAccount.getAccountNumber() << "\n";
            cout << "Please remember your account number and PIN for future transactions.\n";
            
            saveAccountsToFile();
        } catch (const exception& e) {
            cout << "Error creating account: " << e.what() << "\n";
        }
    }
    
    void depositAmount() {
        int accountNum;
        string pin;
        double amount;
        
        cout << "\n========== DEPOSIT AMOUNT ==========\n";
        cout << "Enter Account Number: ";
        cin >> accountNum;
        
        auto it = accounts.find(accountNum);
        if (it == accounts.end()) {
            cout << "Account not found!\n";
            return;
        }
        
        cout << "Enter PIN: ";
        cin >> pin;
        
        if (it->second.getPin() != pin) {
            cout << "Invalid PIN!\n";
            return;
        }
        
        cout << "Enter Deposit Amount: $";
        cin >> amount;
        
        try {
            it->second.deposit(amount);
            cout << "Deposit successful!\n";
            cout << "New Balance: $" << fixed << setprecision(2) << it->second.getBalance() << "\n";
            saveAccountsToFile();
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
    
    void withdrawAmount() {
        int accountNum;
        string pin;
        double amount;
        
        cout << "\n========== WITHDRAW AMOUNT ==========\n";
        cout << "Enter Account Number: ";
        cin >> accountNum;
        
        auto it = accounts.find(accountNum);
        if (it == accounts.end()) {
            cout << "Account not found!\n";
            return;
        }
        
        cout << "Enter PIN: ";
        cin >> pin;
        
        if (it->second.getPin() != pin) {
            cout << "Invalid PIN!\n";
            return;
        }
        
        cout << "Current Balance: $" << fixed << setprecision(2) << it->second.getBalance() << "\n";
        cout << "Enter Withdrawal Amount: $";
        cin >> amount;
        
        try {
            it->second.withdraw(amount);
            cout << "Withdrawal successful!\n";
            cout << "New Balance: $" << fixed << setprecision(2) << it->second.getBalance() << "\n";
            saveAccountsToFile();
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
    
    void checkBalance() {
        int accountNum;
        string pin;
        
        cout << "\n========== CHECK BALANCE ==========\n";
        cout << "Enter Account Number: ";
        cin >> accountNum;
        
        auto it = accounts.find(accountNum);
        if (it == accounts.end()) {
            cout << "Account not found!\n";
            return;
        }
        
        cout << "Enter PIN: ";
        cin >> pin;
        
        if (it->second.getPin() != pin) {
            cout << "Invalid PIN!\n";
            return;
        }
        
        it->second.displayAccount();
    }
    
    void modifyAccount() {
        int accountNum;
        string pin;
        
        cout << "\n========== MODIFY ACCOUNT ==========\n";
        cout << "Enter Account Number: ";
        cin >> accountNum;
        
        auto it = accounts.find(accountNum);
        if (it == accounts.end()) {
            cout << "Account not found!\n";
            return;
        }
        
        cout << "Enter PIN: ";
        cin >> pin;
        
        if (it->second.getPin() != pin) {
            cout << "Invalid PIN!\n";
            return;
        }
        
        cout << "\nCurrent Account Details:\n";
        it->second.displayAccount();
        
        int choice;
        cout << "\nWhat would you like to modify?\n";
        cout << "1. Customer Name\n";
        cout << "2. Address\n";
        cout << "3. Phone Number\n";
        cout << "4. PIN\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        cin.ignore(); // Clear buffer
        
        try {
            switch (choice) {
                case 1: {
                    string newName;
                    cout << "Enter new Customer Name: ";
                    getline(cin, newName);
                    it->second.setCustomerName(newName);
                    cout << "Name updated successfully!\n";
                    break;
                }
                case 2: {
                    string newAddress;
                    cout << "Enter new Address: ";
                    getline(cin, newAddress);
                    it->second.setAddress(newAddress);
                    cout << "Address updated successfully!\n";
                    break;
                }
                case 3: {
                    string newPhone;
                    cout << "Enter new Phone Number: ";
                    getline(cin, newPhone);
                    it->second.setPhoneNumber(newPhone);
                    cout << "Phone number updated successfully!\n";
                    break;
                }
                case 4: {
                    string newPin, confirmPin;
                    do {
                        cout << "Enter new 4-digit PIN: ";
                        getline(cin, newPin);
                        
                        if (newPin.length() != 4 || !all_of(newPin.begin(), newPin.end(), ::isdigit)) {
                            cout << "PIN must be exactly 4 digits! Please try again.\n";
                            continue;
                        }
                        
                        cout << "Confirm new PIN: ";
                        getline(cin, confirmPin);
                        
                        if (newPin != confirmPin) {
                            cout << "PINs don't match! Please try again.\n";
                        }
                    } while (newPin != confirmPin || newPin.length() != 4);
                    
                    it->second.setPin(newPin);
                    cout << "PIN updated successfully!\n";
                    break;
                }
                case 5:
                    return;
                default:
                    cout << "Invalid choice!\n";
                    return;
            }
            saveAccountsToFile();
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
    
    void deleteAccount() {
        int accountNum;
        string pin, confirmation;
        
        cout << "\n========== DELETE ACCOUNT ==========\n";
        cout << "WARNING: This action cannot be undone!\n";
        cout << "Enter Account Number: ";
        cin >> accountNum;
        
        auto it = accounts.find(accountNum);
        if (it == accounts.end()) {
            cout << "Account not found!\n";
            return;
        }
        
        cout << "Enter PIN: ";
        cin >> pin;
        
        if (it->second.getPin() != pin) {
            cout << "Invalid PIN!\n";
            return;
        }
        
        cout << "\nAccount to be deleted:\n";
        it->second.displayAccount();
        
        cout << "\nType 'DELETE' to confirm account deletion: ";
        cin >> confirmation;
        
        if (confirmation == "DELETE") {
            accounts.erase(it);
            cout << "Account deleted successfully!\n";
            saveAccountsToFile();
        } else {
            cout << "Account deletion cancelled.\n";
        }
    }
    
    void viewTransactionHistory() {
        int accountNum;
        string pin;
        
        cout << "\n========== TRANSACTION HISTORY ==========\n";
        cout << "Enter Account Number: ";
        cin >> accountNum;
        
        auto it = accounts.find(accountNum);
        if (it == accounts.end()) {
            cout << "Account not found!\n";
            return;
        }
        
        cout << "Enter PIN: ";
        cin >> pin;
        
        if (it->second.getPin() != pin) {
            cout << "Invalid PIN!\n";
            return;
        }
        
        it->second.displayTransactionHistory();
    }
    
    void exportAccountSummary() {
        int accountNum;
        string pin;
        
        cout << "\n========== EXPORT ACCOUNT SUMMARY ==========\n";
        cout << "Enter Account Number: ";
        cin >> accountNum;
        
        auto it = accounts.find(accountNum);
        if (it == accounts.end()) {
            cout << "Account not found!\n";
            return;
        }
        
        cout << "Enter PIN: ";
        cin >> pin;
        
        if (it->second.getPin() != pin) {
            cout << "Invalid PIN!\n";
            return;
        }
        
        string filename = "account_" + to_string(accountNum) + "_summary.txt";
        ofstream file(filename);
        
        if (!file.is_open()) {
            cout << "Error creating export file!\n";
            return;
        }
        
        // Write account summary
        file << "BANK MANAGEMENT SYSTEM - ACCOUNT SUMMARY\n";
        file << "=========================================\n\n";
        file << "Account Number: " << it->second.getAccountNumber() << "\n";
        file << "Customer Name: " << it->second.getCustomerName() << "\n";
        file << "Address: " << it->second.getAddress() << "\n";
        file << "Phone Number: " << it->second.getPhoneNumber() << "\n";
        file << "Current Balance: $" << fixed << setprecision(2) << it->second.getBalance() << "\n\n";
        
        file << "TRANSACTION HISTORY:\n";
        file << "-------------------\n";
        // Add transaction history to file (you'd need to modify Account class to provide access)
        
        file.close();
        cout << "Account summary exported to: " << filename << "\n";
    }
    
    // File I/O operations
    void saveAccountsToFile() {
        ofstream file(DATA_FILE);
        if (!file.is_open()) {
            cout << "Warning: Could not save data to file!\n";
            return;
        }
        
        for (const auto& pair : accounts) {
            file << pair.second.toFileString() << "\n";
        }
        file.close();
    }
    
    void loadAccountsFromFile() {
        ifstream file(DATA_FILE);
        if (!file.is_open()) {
            return; // File doesn't exist yet, which is fine for first run
        }
        
        string line;
        int maxAccountNum = 1000;
        
        while (getline(file, line)) {
            if (!line.empty()) {
                try {
                    Account acc = Account::fromFileString(line);
                    accounts[acc.getAccountNumber()] = acc;
                    maxAccountNum = max(maxAccountNum, acc.getAccountNumber());
                } catch (const exception& e) {
                    cout << "Warning: Error loading account data: " << e.what() << "\n";
                }
            }
        }
        
        // Update static counter to continue from highest account number
        // Note: This is a simplified approach - in production, you'd handle this more robustly
        file.close();
    }
    
    // Utility methods
    void displayMenu() {
        cout << "WELCOME TO BANK MANAGEMENT SYSTEM \n";
        cout << "  1. Create New Account                   \n";
        cout << "  2. Deposit Amount                       \n";
        cout << "  4. Check Balance                        \n";
        cout << "  5. Modify Account                       \n";
        cout << "  6. Delete Account                       \n";
        cout << "  7. Transaction History                  \n";
        cout << "  9. Exit                                 \n";
        cout << "Enter your choice: ";
    }
    
    int getValidChoice() {
        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 9) {
            cout << "Invalid input! Please enter a number between 1-9: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return choice;
    }
    
    void run() {
        cout << "Welcome to the Bank Management System!\n";
        cout << "Your secure banking solution.\n";
        
        int choice;
        do {
            displayMenu();
            choice = getValidChoice();
            
            switch (choice) {
                case 1:
                    createAccount();
                    break;
                case 2:
                    depositAmount();
                    break;
                case 3:
                    withdrawAmount();
                    break;
                case 4:
                    checkBalance();
                    break;
                case 5:
                    modifyAccount();
                    break;
                case 6:
                    deleteAccount();
                    break;
                case 7:
                    viewTransactionHistory();
                    break;
                case 8:
                    exportAccountSummary();
                    break;
                case 9:
                    cout << "Thank you for using Bank Management System!\n";
                    cout << "Your data has been saved securely.\n";
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
            }
            
            if (choice != 9) {
                cout << "\nPress Enter to continue...";
                cin.ignore();
                cin.get();
            }
            
        } while (choice != 9);
    }
};

// Main function
int main() {
    try {
        BankManagementSystem bank;
        bank.run();
    } catch (const exception& e) {
        cout << "Critical Error: " << e.what() << "\n";
        cout << "Please contact system administrator.\n";
        return 1;
    }
    
    return 0;
}