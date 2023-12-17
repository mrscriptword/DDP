#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct User {
    string username;
    string password;
};

struct Profile {
    string nama;
    string status;
    string bank;
    string catatan;
    string usia;
    string line;
    struct Profile *next;
};


bool login(const User &pengguna) {
    ifstream database("Data akun.txt");
    string db_username, db_password;

    if (!database.is_open()) {
        cerr << "Maaf Sepertinya ada yang salah" << endl;
        return false;
    }

    User db_login;
    while (database >> db_login.username >> db_login.password) {
        if (pengguna.username == db_login.username && pengguna.password == db_login.password) {
            database.close();
            cout << "Anda telah berhasil login" << endl;
            cout << db_login.username << endl;
            cout << "-------------------------" << endl;
            cout << endl;
            return true;
        }
    }

    database.close();
    cout << "Sepertinya anda memasukan sandi atau username yang salah" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << endl;
    return false;
}
bool signup(const User &pengguna) {
    ofstream database("Data akun.txt", ios::app);

    if (!database.is_open()) {
        cerr << "Maaf sepertinya ada operasi yang error" << endl;
        return false;
    }

    database << pengguna.username << " " << pengguna.password << endl;
    database.close();
    cout << "Selamat akun anda telah berhasil dibuat" << endl;
    cout << "---------------------------------------" << endl;
    cout << endl;
    cout << "Silahkan Tambahkan Profil........." << endl;
    return true;
}

void masuk() {
    User pengguna;
    cout << "Masukan Username: ";
    cin.ignore(); getline(cin, pengguna.username);
    cout << "Masukan Password: ";
    getline(cin, pengguna.password);
    if (login(pengguna)){
            int a, menu;
            a = 1;
            do {
            cout << "SELAMAT ANDA BERHASIL MASUK" << endl;
            cout << "SILAHKAN PILIH MENU YANG TERSEDIA" << endl;
            cout << "------------------------------------" << endl;
            cout << "1.MENU ADA" << endl;
            cout << "2.MENU ADA" << endl;
            cout << "1.MENU ADA" << endl;
            cout << "2.MENU ADA" << endl;
            } while (a > 0);
    }
}

void daftar(Profile &profil) {
    User pengguna;
    cout << "Masukan Username: ";
    cin.ignore(); getline(cin, pengguna.username);
    cout << "Masukan Password: ";
    getline(cin, pengguna.password);

    if (signup(pengguna)) {
            int a, menu;
            a = 1;
            do {
            cout << "SELAMAT ANDA BERHASIL MASUK" << endl;
            cout << "SILAHKAN PILIH MENU YANG TERSEDIA" << endl;
            cout << "------------------------------------" << endl;
            cout << "1.MENU ADA" << endl;
            cout << "2.MENU ADA" << endl;
            cout << "1.MENU ADA" << endl;
            cout << "2.MENU ADA" << endl;
            } while (a > 0);
    }
    
}





int main() {
    int menu;
    Profile profil;

    do {
        cout << "1. Daftar Akun" << endl;
        cout << "2. Login" << endl;
        cout << "3. Profil" << endl;
        cout << "Pilih Menu: ";
        cin >> menu;

        if (menu == 1) {
            daftar(profil);  // Pass the profil object
            cout << "Silahkan Login" << endl;
            cout << endl;
        } else if (menu == 2) {
            masuk();
        } else if (menu == 3) {
            cout << endl;
        }

    } while (menu != 7);

    return 0;
}
