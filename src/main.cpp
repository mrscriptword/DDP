#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <sys/stat.h>
#include <filesystem>
#include "termcolor.hpp"

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

// Prototype Fungsi
void clearScreen();
void systempause();
void addWallet();
double getWalletBalance(const string& walletName);
void updateWalletBalance(const string& walletName, double amount);
void displayWallets();
void addWallet();
void signUp();
void saveLoginInfo(const UserData& user);
bool readSavedLoginInfo(UserData& user);
bool signIn(UserData& loggedInUser);
bool hasWallet();
void performTransaction(const string& type);
void displayHistory();
void displayProfile(const UserData& user);
double getTotalBalance();
void createDataFolder();
void menuTransaction();
void infoApps();

int main() {
  int choice;
  UserData loggedInUser;

  createDataFolder();

  do {
    if (readSavedLoginInfo(loggedInUser)) {
      clearScreen();
      cout << "Welcome back to Wangku, " << INFO << loggedInUser.fullName << RESET << "!" << endl;
      cout << fixed << setprecision(2) << "\nTotal Balance: Rp " << INFO << getTotalBalance() << RESET << endl;

      cout << defaultfloat;
    }

    if (loggedInUser.username.empty()) {
      clearScreen();

      cout << "\n####### LOGIN MENU #######\n";
      cout << "[" << INFO << "1" << RESET << "] Sign up" << endl;
      cout << "[" << INFO << "2" << RESET << "] Sign in" << endl;
    } else {
      cout << "\n######## MAIN MENU ########\n";
      cout << "[" << INFO << "1" << RESET << "] Transaction" << endl;
      cout << "[" << INFO << "2" << RESET << "] Wallets" << endl;
      cout << "[" << INFO << "3" << RESET << "] History" << endl;
      cout << "[" << INFO << "4" << RESET << "] Profile" << endl;
      cout << "[" << INFO << "5" << RESET << "] Info App" << endl;
      cout << "[" << INFO << "6" << RESET << "] Logout" << endl;
    }
    cout << "[" << INFO << "0" << RESET << "] Exit" << endl;
    cout << "Your choice: ";
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
            cout << "\nWelcome to Wangku, " << INFO << loggedInUser.fullName << RESET << "!" << endl;
            saveLoginInfo(loggedInUser);
            systempause();
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
        infoApps();
        break;
      case 6:
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

void clearScreen() {
  #ifdef _WIN32
    system("cls");  // Untuk Windows
  #else
    system("clear");  // Untuk Unix
  #endif

  cout << "\033[2J\033[H";
}

void systempause() {
  cout << "\nPress Enter to continue...";
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
    cout << "[" << INFO << "0" << RESET << "] Back" << endl;

    int choice;
    cout << "Your choice (1/0): "; cin >> choice;

    switch (choice) {
      case 1:
        addWallet();
        break;
      case 0:
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
    cout << "[" << INFO << "0" << RESET << "] Back" << endl;

    int choice;
    cout << "Your choice (1/0): "; cin >> choice;

    switch (choice) {
      case 1:
        addWallet();
        break;
      case 0:
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

  cout << "\nEnter username: ";
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

    cout << "\nPress Enter to continue...";
    cin.get();

    database.close();
  } else {
    cout << "\n" << BG_ERROR << " ERROR " << RESET << " Failed to open file." << endl;

    cout << "\nPress Enter to continue...";
    cin.get();
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

  cout << "\nEnter username: ";
  cin >> db_username;

  cout << "Enter password: ";
  cin >> db_password;

  ifstream database("data/users.txt");
  if (database.is_open()) {
    while (database >> user.username >> user.password >> user.fullName) {
      if (user.username == db_username && user.password == db_password) {
        cout << "\n" << BG_SUCCESS << " SUCCESS " << RESET << " Sign in successfull!\n" << endl;
        database.close();

        loggedInUser = user;

        return true;
      }
    }
    cout << "\n" << BG_WARNING << " WARNING " << RESET << " Incorrect username or password." << endl;

    cout << "\nPress Enter to continue...";
    cin.get();

    database.close();
  } else {
    cout << "\n" << BG_ERROR << " ERROR " << RESET << " Failed to open file." << endl;

    cout << "\nPress Enter to continue...";
    cin.get();
  }

  return false;
}

void performTransaction(const string& type) {
  if (!hasWallet()) {
    cout << endl;
    cout << BG_WARNING << " WARNING " << RESET << " No wallets available. Please create a wallet first." << endl;
    systempause();
    return;
  }

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
  cout << "\n######### USER PROFILE #########\n" << endl;
  cout << "Username: " << user.username << endl;
  cout << "Full Name: " << user.fullName << endl;
  cout << fixed << setprecision(2) << "\nTotal Balance: Rp " << INFO << getTotalBalance() << RESET << endl;
  cout << "\n################################\n" << endl;

  systempause();
}

double getTotalBalance() {
  double totalBalance = 0.0;
  for (const Wallet& wallet : wallets) {
    totalBalance += wallet.balance;
  }
  return totalBalance;
}

bool hasWallet() {
  return !wallets.empty();
}

void createDataFolder() {
  // Check if the "data" folder exists
  struct stat info;
  if (stat("data", &info) != 0) {
    // "data" folder does not exist, create it
    #ifdef _WIN32
      // For Windows
      if (mkdir("data") != 0) {
    #else
      // For Linux and macOS
      if (mkdir("data", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != 0) {
    #endif
      cout << BG_ERROR << " ERROR " << RESET << " Failed to create 'data' folder." << endl;
      systempause();
      exit(EXIT_FAILURE);
    } else {
      cout << BG_SUCCESS << " SUCCESS " << RESET << " 'data' folder created successfully." << endl;
    }
  }
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

void infoApps() {
  clearScreen();

  cout << BG_INFO << "            INFO APPS             " << RESET << endl;
  cout << INFO <<    "==================================" << RESET << endl;
  cout << INFO <<    "     Welcome to Wangku App        " << RESET << endl;
  cout << INFO <<    "==================================\n" << RESET << endl;
  cout <<            "Version: " << SUCCESS << "2.0.0" << RESET << endl;
  cout <<            "Release: " << SUCCESS << "22 Dec 2023" << RESET << endl;
  cout <<            "Team Members:" << endl;
  cout <<            "  1 | " << SUCCESS << "Rendy" << RESET << endl;
  cout <<            "  2 | " << SUCCESS << "Tirta" << RESET << endl;
  cout <<            "  3 | " << SUCCESS << "Hafidz" << RESET << endl;
  cout <<            "  4 | " << SUCCESS << "Shafira" << RESET << endl;
  cout <<            "  5 | " << SUCCESS << "Rifqi" << RESET << endl;
  cout <<            "  6 | " << SUCCESS << "Yola" << RESET << endl;
  cout << INFO <<    "\n=================================" << RESET << endl;

  systempause();
}