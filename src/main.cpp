#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <iomanip>

using namespace std;

// Colors
#define RESET   "\033[0m"
#define ERROR     "\033[31m"
#define SUCCESS   "\033[32m"
#define WARNING  "\033[33m"
#define INFO    "\033[34m"

// Backgroud Colors
#define BG_ERROR     "\033[41m"
#define BG_SUCCESS   "\033[42m"
#define BG_WARNING  "\033[43m"
#define BG_INFO    "\033[44m"

struct UserData {
  string username;
  string password;
  string fullName;
};

struct Wallet {
  string name;
  double balance;

  Wallet(const string& n, double b) : name(n), balance(b) {}
};

struct Transaction {
  string type; // "INCOME" or "EXPENSE"
  string walletName;
  double amount;
  string transactionName; // Nama transaksi

  Transaction(const string& t, const string& w, double a, const string& name)
    : type(t), walletName(w), amount(a), transactionName(name) {}
};

vector<Wallet> wallets;

vector<Transaction> transactions;

void addWallet();

void clearScreen() {
  cout << "\033[2J\033[H";  // ANSI escape code untuk membersihkan layar
}

void systempause() {
  cout << "Press Enter to continue...";
  cin.ignore();
  cin.get();
}

double getWalletBalance(const string& walletName) {
  for (const Wallet& wallet : wallets) {
    if (wallet.name == walletName) {
      return wallet.balance;
    }
  }
  return 0.0;  // Return 0 if wallet not found (you may choose a different default value)
}

void updateWalletBalance(const string& walletName, double amount) {
  for (Wallet& wallet : wallets) {
    if (wallet.name == walletName) {
      wallet.balance += amount;
      break;
    }
  }
}

void displayWallets() {
  cout << "\n###### WALLETS ######\n";

  if (wallets.empty()) {
    cout << "No wallet yet" << endl;

    cout << "\n[" << INFO << "1" << RESET << "] Add a new wallet" << endl;
    cout << "[" << INFO << "0" << RESET << "] Cancel" << endl;

    int choice;
    cout << "Your choice (1/0): "; cin >> choice;

    switch (choice) {
      case 1:
        addWallet();
        break;
      case 2:
        break;
      default:
        cout << "\n" << BG_WARNING << " WARNING " << RESET << " Invalid choice. Please try again." << endl;
        systempause();
    }
  } else {
    for (const Wallet& wallet : wallets) {
      cout << fixed << setprecision(2) << wallet.name << ": Rp " << INFO << wallet.balance << RESET << endl;
    }

    cout << "\n[" << INFO << "1" << RESET << "] Add a new wallet" << endl;
    cout << "[" << INFO << "0" << RESET << "] Cancel" << endl;

    int choice;
    cout << "Your choice (1/0): "; cin >> choice;

    switch (choice) {
      case 1:
        addWallet();
        break;
      case 2:
        break;
      default:
        cout << "\n" << BG_WARNING << " WARNING " << RESET << " Invalid choice. Please try again." << endl;
        systempause();
    }
  }
}

void addWallet() {
  string walletName;
  double initialBalance;

  cout << "\nEnter wallet name: ";
  cin >> walletName;

  cout << "Enter initial balance: ";
  cin >> initialBalance;

  Wallet newWallet(walletName, initialBalance);
  wallets.push_back(newWallet);

  cout << "\n" << BG_SUCCESS << " SUCCESS " << RESET << " Wallet added successfully!" << endl;
  systempause();
}

void signUp() {
  UserData user;

  cout << "Enter username: ";
  cin >> user.username;

  cout << "Enter password: ";
  cin >> user.password;

  cout << "Enter full name: ";
  cin.ignore();
  getline(cin, user.fullName);

  ofstream database("data/users.txt", ios::app);
  if (database.is_open()) {
    database << user.username << " " << user.password << " " << user.fullName << endl;
    cout << "\n" << BG_SUCCESS << " SUCCESS " << RESET << " Sign up successfull!" << endl;
    systempause();
    database.close();
  } else {
    cout << "\n" << BG_ERROR << " ERROR " << RESET << " Failed to open file." << endl;
    systempause();
  }
}

void saveLoginInfo(const UserData& user) {
  ofstream loginInfoFile("data/login_info.txt");
  if (loginInfoFile.is_open()) {
    loginInfoFile << user.username << " " << user.password << " " << user.fullName << endl;
    loginInfoFile.close();
  } else {
    cout << "\n" << BG_ERROR << " ERROR " << RESET << " Failed to save login information." << endl;
    systempause();
  }
}

bool readSavedLoginInfo(UserData& user) {
  ifstream loginInfoFile("data/login_info.txt");
  if (loginInfoFile.is_open()) {
    if (loginInfoFile >> user.username >> user.password >> user.fullName) {
      loginInfoFile.close();
      return true;
    }
    loginInfoFile.close();
  }
  return false;
}

bool signIn(UserData& loggedInUser) {
  UserData user;
  string db_username, db_password;

  cout << "Enter username: ";
  cin >> db_username;

  cout << "Enter password: ";
  cin >> db_password;

  ifstream database("data/users.txt");
  if (database.is_open()) {
    while (database >> user.username >> user.password >> user.fullName) {
      if (user.username == db_username && user.password == db_password) {
        cout << "\n" << BG_SUCCESS << " SUCCESS " << RESET << " Sign in successfull!\n" << endl;
        systempause();
        database.close();

        loggedInUser = user;

        return true;
      }
    }
    cout << "\n" << BG_WARNING << " WARNING " << RESET << " Incorrect username or password." << endl;
    systempause();
    database.close();
  } else {
    cout << "\n" << BG_ERROR << " ERROR " << RESET << " Failed to open file." << endl;
    systempause();
  }

  return false;
}

void performTransaction(const string& type) {
  string walletName;
  double amount;
  string transactionName;

  cout << endl;
  cout << "##### Your Wallet #####" << endl;
  for (const Wallet& wallet : wallets) {
    cout << fixed << setprecision(2) << wallet.name << ": Rp " << wallet.balance << endl;
  }
  cout << endl;

  cout << "Enter wallet name: ";
  cin >> walletName;

  cout << "Enter amount: ";
  cin >> amount;

  cout << "Enter transaction name: ";
  cin.ignore();
  getline(cin, transactionName);

  if (type == "EXPENSE" && amount > getWalletBalance(walletName)) {
    cout << BG_WARNING << " WARNING " << RESET << " Insufficient funds in the selected wallet." << endl;
    systempause();
    return;
  }

  Transaction newTransaction(type, walletName, amount, transactionName);
  transactions.push_back(newTransaction);

  if (type == "INCOME") {
    updateWalletBalance(walletName, amount);
  } else {
    updateWalletBalance(walletName, -amount);
  }
  cout << endl;
  cout << BG_SUCCESS << " SUCCESS " << RESET << " Transaction recorded successfully!" << endl;
  cout << endl;
  systempause();
}

void displayHistory() {
  cout << "\n###### TRANSACTION HISTORY ######\n";
  for (const Transaction& transaction : transactions) {
    string typeStr = (transaction.type == "INCOME") ? "INCOME" : "EXPENSE";
    cout << BG_INFO << typeStr << RESET << " | Wallet: " << transaction.walletName
         << " | Amount: " << fixed << setprecision(2) << transaction.amount
         << " | Transaction Name: " << transaction.transactionName << endl;
  }

  systempause();
}

void displayProfile(const UserData& user) {
  cout << "\n###### PROFILE ######\n";
  cout << "Username: " << user.username << endl;
  cout << "Full Name: " << user.fullName << endl;

  systempause();
}

double getTotalBalance() {
  double totalBalance = 0.0;
  for (const Wallet& wallet : wallets) {
    totalBalance += wallet.balance;
  }
  return totalBalance;
}

void menuTransaction() {
  int choice;

  cout << "\n###### TRANSACTION MENU ######\n";
  cout << "[" << INFO << "1" << RESET << "] Income" << endl;
  cout << "[" << INFO << "2" << RESET << "] Expense" << endl;
  cout << "[" << INFO << "0" << RESET << "] Back" << endl;
  cout << "Your choice (1/2/0): ";
  cin >> choice;

  switch (choice) {
    case 1:
      performTransaction("INCOME");
      break;
    case 2:
      performTransaction("EXPENSE");
      break;
    case 0:
      break;
    default:
      cout << endl;
      cout << BG_WARNING << " WARNING " << RESET << " Invalid selection. Please try again." << endl;
      systempause();
      break;
  }
}

int main() {
  int choice;
  UserData loggedInUser;

  do {
    if (readSavedLoginInfo(loggedInUser)) {
      clearScreen();
      cout << "Welcome back, " << INFO << loggedInUser.fullName << RESET << "!" << endl;
      cout << fixed << setprecision(2) << "\nTotal Balance: Rp " << INFO << getTotalBalance() << RESET << endl;

      cout << defaultfloat;
    }

    cout << "\n###### MENU ######\n";
    if (loggedInUser.username.empty()) {
      cout << "[" << INFO << "1" << RESET << "] Sign up" << endl;
      cout << "[" << INFO << "2" << RESET << "] Sign in" << endl;
    } else {
      cout << "[" << INFO << "1" << RESET << "] Transaction" << endl;
      cout << "[" << INFO << "2" << RESET << "] Wallets" << endl;
      cout << "[" << INFO << "3" << RESET << "] History" << endl;
      cout << "[" << INFO << "4" << RESET << "] Profile" << endl;
      cout << "[" << INFO << "5" << RESET << "] Logout" << endl;
    }
    cout << "[" << INFO << "0" << RESET << "] Exit" << endl;
    cout << "Your choice (1/2/3/0): ";
    cin >> choice;

    switch (choice) {
      case 1:
        if (loggedInUser.username.empty()) {
          signUp();
        } else {
          menuTransaction();
        }
        break;
      case 2:
        if (loggedInUser.username.empty()) {
          if (signIn(loggedInUser)) {
            cout << "Welcome, " << INFO << loggedInUser.fullName << RESET << "!" << endl;
            saveLoginInfo(loggedInUser);
          }
        } else {
          displayWallets();
        }
        break;
      case 3:
        displayHistory();
        break;
      case 4:
        displayProfile(loggedInUser);
        break;
      case 5:
        if (!loggedInUser.username.empty()) {
          cout << "\n" << BG_SUCCESS << " SUCCESS " << RESET << " Logout successful!" << endl;
          systempause();
          loggedInUser = UserData();
          saveLoginInfo(loggedInUser);
        }
        break;
      case 0:
        cout << "\n" << BG_INFO << " INFO " << RESET << " Thank you, see you again!" << endl;
        systempause();
        break;
      default:
        cout << "\n" << BG_WARNING << " WARNING " << RESET << " Invalid selection. Please try again." << endl;
        systempause();
    }
  } while (choice != 0);

  return 0;
}