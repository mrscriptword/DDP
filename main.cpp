#include <fstream>
#include <iostream>
#include <string>


using namespace std;

struct User {
  string username;
  string password;
};

struct profile {
  string nama;
  string status;
  string bank;
  string catatan;
};

struct code1 {
  long long int saldo;
  long long int jumlah_saldo;
};

bool signup(const User &pengguna) {
  ofstream database("data.txt", ios::app);  // ini file nya disimpen dimana rend?
  if (!database.is_open()) {
    cerr << "Maaf sepertinya ada operasi yang error" << endl;
    return false;
  }
  database << pengguna.username << " " << pengguna.password << endl;
  database.close();
  cout << "Selamat akun anda telah berhasil dibuat" << endl;
  return true;
}

bool login(const User &pengguna) {
  ifstream database("data.txt");
  string   db_username, db_password;
  if (!database.is_open()) {
    cerr << "Maaf Sepertinya ada yang salah" << endl;
    return false;
  }
  User db_login;
  while (database >> db_login.username >> db_login.password) {
    if (pengguna.username == db_login.username && pengguna.password == db_login.password) {
      database.close();
      cout << "Anda telah berhasil login" << endl;
      return true;
    }
  }
  database.close();
  return false;
}

void daftar() {
  User pengguna;
  cout << "Masukan Username :";
  cin >> pengguna.username;
  cout << "Masukan Password :";
  cin >> pengguna.password;
  signup((pengguna));
}

void masuk() {
  User pengguna;
  cout << "Username :";
  cin >> pengguna.username;
  cout << "Password :";
  cin >> pengguna.password;
  login((pengguna));
}

int main() {
  int menu;
  do {
    cout << "1.Daftar Akun" << endl;
    cout << "2.Login" << endl;
    cout << "Pilih Menu :";
    cin >> menu;
    if (menu == 1) {
      daftar();
      cout << "Silahkan Login" << endl;
      cout << endl;
    } else if (menu == 2) {
      masuk();
    }
  } while (menu != 7);
}
