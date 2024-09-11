#include <iostream>
#include <vector>  
using namespace std;

class Customer {
private:
    int id;
    string name;
    string address;
    string phone;
    string email;

public:
    Customer(int id, string name, string address, string phone, string email) {
        this->id = id;
        this->name = name;
        this->address = address;
        this->phone = phone;
        this->email = email;
    }

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    string getAddress() const { return address; }
    string getPhone() const { return phone; }
    string getEmail() const { return email; }
};

class Account {
private:
    int id;
    int customerID;
    string accountType;
    double balance;
    string accountStatus;
    Customer* customer;  

public:
    Account(int id, int customerID, string accountType, double balance, string accountStatus, Customer* customer) {
        this->id = id;
        this->customerID = customerID;
        this->accountType = accountType;
        this->balance = balance;
        this->accountStatus = accountStatus;
        this->customer = customer;
    }

    
    int getId() const { return id; }
    int getCustomerID() const { return customerID; }
    string getAccountType() const { return accountType; }
    double getBalance() const { return balance; }
    string getAccountStatus() const { return accountStatus; }
    Customer* getCustomer() const { return customer; }

    
    void setBalance(double newBalance) { balance = newBalance; }
    void setAccountStatus(string status) { accountStatus = status; }
};

class Transaction {
private:
    int id;
    int accountID;
    string transactionType;
    double amount;
    string transactionDate;
    Account* account;  

public:
    Transaction(int id, int accountID, string transactionType, double amount, string transactionDate, Account* account) {
        this->id = id;
        this->accountID = accountID;
        this->transactionType = transactionType;
        this->amount = amount;
        this->transactionDate = transactionDate;
        this->account = account;
    }

    
    int getId() const { return id; }
    int getAccountID() const { return accountID; }
    string getTransactionType() const { return transactionType; }
    double getAmount() const { return amount; }
    string getTransactionDate() const { return transactionDate; }
};

class BankingService {
private:
    vector<Transaction> transactionHistory;  

public:
    void performWithdrawal(Account* account, double amount);
    void performDeposit(Account* account, double amount);
    void performTransfer(Account* fromAccount, Account* toAccount, double amount);
    void viewAccountInfo(Account* account);
    void viewTransactionHistory(Account* account);
};

void BankingService::performWithdrawal(Account* account, double amount) {
    if (account == nullptr || account->getAccountStatus() != "Active") {
        cout << "Error: Invalid or inactive account." << endl;
        return;
    }
    if (account->getBalance() < amount) {
        cout << "Error: Insufficient balance." << endl;
        return;
    }

    account->setBalance(account->getBalance() - amount);
    cout << "Withdrawal of " << amount << " successful. New balance: " << account->getBalance() << endl;

    
    transactionHistory.push_back(Transaction(transactionHistory.size() + 1, account->getId(), "Withdrawal", amount, "2024-09-09", account));
}

void BankingService::performDeposit(Account* account, double amount) {
    if (account == nullptr || account->getAccountStatus() != "Active") {
        cout << "Error: Invalid or inactive account." << endl;
        return;
    }

    account->setBalance(account->getBalance() + amount);
    cout << "Deposit of " << amount << " successful. New balance: " << account->getBalance() << endl;

    
    transactionHistory.push_back(Transaction(transactionHistory.size() + 1, account->getId(), "Deposit", amount, "2024-09-09", account));
}

void BankingService::performTransfer(Account* fromAccount, Account* toAccount, double amount) {
    if (fromAccount == nullptr || toAccount == nullptr || fromAccount->getAccountStatus() != "Active" || toAccount->getAccountStatus() != "Active") {
        cout << "Error: Invalid or inactive account(s)." << endl;
        return;
    }
    if (fromAccount->getBalance() < amount) {
        cout << "Error: Insufficient balance in the source account." << endl;
        return;
    }

    fromAccount->setBalance(fromAccount->getBalance() - amount);
    toAccount->setBalance(toAccount->getBalance() + amount);
    cout << "Transfer of " << amount << " from account " << fromAccount->getId() << " to account " << toAccount->getId() << " successful." << endl;

    
    transactionHistory.push_back(Transaction(transactionHistory.size() + 1, fromAccount->getId(), "Transfer Out", amount, "2024-09-09", fromAccount));
    transactionHistory.push_back(Transaction(transactionHistory.size() + 1, toAccount->getId(), "Transfer In", amount, "2024-09-09", toAccount));
}

void BankingService::viewAccountInfo(Account* account) {
    if (account == nullptr) {
        cout << "Error: Invalid account." << endl;
        return;
    }

    cout << "Account ID: " << account->getId() << endl;
    cout << "Customer Name: " << account->getCustomer()->getName() << endl;
    cout << "Account Type: " << account->getAccountType() << endl;
    cout << "Balance: " << account->getBalance() << endl;
    cout << "Account Status: " << account->getAccountStatus() << endl;
}

void BankingService::viewTransactionHistory(Account* account) {
    if (account == nullptr) {
        cout << "Error: Invalid account." << endl;
        return;
    }

    cout << "Transaction History for Account ID: " << account->getId() << endl;
    for (const Transaction& txn : transactionHistory) {
        if (txn.getAccountID() == account->getId()) {
            cout << "Transaction ID: " << txn.getId() << ", Type: " << txn.getTransactionType() << ", Amount: " << txn.getAmount() << ", Date: " << txn.getTransactionDate() << endl;
        }
    }
}

int main() {
    int customerId;
    string customerName, customerAddress, customerPhone, customerEmail;

    
    cout << "Enter Customer ID: ";
    cin >> customerId;
    cin.ignore();  
    cout << "Enter Customer Name: ";
    getline(cin, customerName);
    cout << "Enter Customer Address: ";
    getline(cin, customerAddress);
    cout << "Enter Customer Phone: ";
    getline(cin, customerPhone);
    cout << "Enter Customer Email: ";
    getline(cin, customerEmail);

    
    Customer customer1(customerId, customerName, customerAddress, customerPhone, customerEmail);

    
    Account account1(1, customer1.getId(), "Savings", 1000.0, "Active", &customer1);
    BankingService service;
    int choice;
    double amount;

    while (true) {
        cout << "\n--- Banking System Menu ---\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. View Account Info\n";
        cout << "4. View Transaction History\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:  // Deposit
            cout << "Enter deposit amount: ";
            cin >> amount;
            service.performDeposit(&account1, amount);
            break;
        case 2:  // Withdraw
            cout << "Enter withdrawal amount: ";
            cin >> amount;
            service.performWithdrawal(&account1, amount);
            break;
        case 3:  // View Account Info
            service.viewAccountInfo(&account1);
            break;
        case 4:  // View Transaction History
            service.viewTransactionHistory(&account1);
            break;
        case 5:  // Exit
            cout << "Exiting... Thank you for using our banking system." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
