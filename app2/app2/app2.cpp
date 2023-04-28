#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BankAccount {
private:
    int id;
    double balance;
public:
    BankAccount(int _id, double _balance) {
        id = _id;
        balance = _balance;
    }
    int getId() {
        return id;
    }
    double getBalance() {
        return balance;
    }
    void deposit(double amount) {
        balance += amount;
    }
    bool withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            return true;
        }
        return false;
    }
};

class Client {
private:
    string name;
    vector<BankAccount*> accounts;
public:
    Client(string _name) {
        name = _name;
    }
    string getName() {
        return name;
    }
    void addAccount(BankAccount* account) {
        accounts.push_back(account);
    }
    vector<BankAccount*> getAccounts() {
        return accounts;
    }
};

class Bank {
private:
    vector<Client*> clients;
    int findClientIndex(string name) {
        for (int i = 0; i < clients.size(); i++) {
            if (clients[i]->getName() == name) {
                return i;
            }
        }
        return -1;
    }
    int findAccountIndex(Client* client, int id) {
        vector<BankAccount*> accounts = client->getAccounts();
        for (int i = 0; i < accounts.size(); i++) {
            if (accounts[i]->getId() == id) {
                return i;
            }
        }
        return -1;
    }
public:
    Bank() {}
    void addClient(string name) {
        clients.push_back(new Client(name));
    }
    bool addAccount(string name, int id, double balance) {
        int clientIndex = findClientIndex(name);
        if (clientIndex != -1) {
            Client* client = clients[clientIndex];
            int accountIndex = findAccountIndex(client, id);
            if (accountIndex == -1) {
                client->addAccount(new BankAccount(id, balance));
                return true;
            }
        }
        return false;
    }
    bool deposit(string name, int id, double amount) {
        int clientIndex = findClientIndex(name);
        if (clientIndex != -1) {
            Client* client = clients[clientIndex];
            int accountIndex = findAccountIndex(client, id);
            if (accountIndex != -1) {
                BankAccount* account = client->getAccounts()[accountIndex];
                account->deposit(amount);
                return true;
            }
        }
        return false;
    }
    bool withdraw(string name, int id, double amount) {
        int clientIndex = findClientIndex(name);
        if (clientIndex != -1) {
            Client* client = clients[clientIndex];
            int accountIndex = findAccountIndex(client, id);
            if (accountIndex != -1) {
                BankAccount* account = client->getAccounts()[accountIndex];
                return account->withdraw(amount);
            }
        }
        return false;
    }
    void printInfo() {
        for (int i = 0; i < clients.size(); i++) {
            Client* client = clients[i];
            cout << client->getName() << endl;
            vector<BankAccount*> accounts = client->getAccounts();
            cout << accounts.size() << endl;
            for (int j = 0; j < accounts.size(); j++) {
                BankAccount* account;
                cout << "Account " << accounts[j]->getId() << ": " << accounts[j]->getBalance() << endl;
            }
        }
    }
};

int main() {
    Bank bank;
    bank.addClient("Liza");
    bank.addClient("Tanya");
    bank.addAccount("Liza", 1, 100);
    bank.addAccount("Liza", 2, 200);
    bank.addAccount("Tanya", 3, 300);
    bank.deposit("Liza", 1, 50);
    bank.withdraw("Liza", 2, 100);
    bank.printInfo();
    return 0;
}