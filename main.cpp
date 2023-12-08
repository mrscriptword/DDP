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
    struct Profile *next;
};
bool signup(const User &pengguna) {
    ofstream database("Data akun.txt", ios::app);
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
            return true;
        }
    }
    database.close();
    return false;
}

void tambahprf(Profile **head){
    Profile *tambah = new Profile();
    cout << "Tambahkan Nama :"; cin.ignore(); getline(cin,tambah->nama);
    cout << "Tambahkan Status (Pekerja/Pelajar)"; getline(cin,tambah->status);
    cout << "Tambahkan Usia :"; getline(cin,tambah->usia);
    tambah->next = NULL;
    if(*head == NULL){
        (*head) = tambah;
        return;
    } Profile *temp = (*head);
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = tambah;
}
void profil(Profile *head){
    Profile *temp = head;
    if (temp==NULL){
        cout << "Tidak ada Profile,silahkan tambahkan terlebih dahulu....." << endl;
        return;
    }while(temp != NULL){
    cout << "Nama: " << temp->nama << endl;
    cout << "Usia: " << temp->usia << endl;
    cout << "Status: " << temp->status << endl;
    break;
    }
    cout << endl;
}
void daftar() {
    User pengguna;
    cout << "Masuan Username: ";
    cin >> pengguna.username;
    cout << "Masukan Password: ";
    cin >> pengguna.password;
    signup(pengguna);
}
void masuk() {
    User pengguna;
    cout << "Username: ";
    cin >> pengguna.username;
    cout << "Password: ";
    cin >> pengguna.password;
    login(pengguna);
}

int main() {
    int menu;
    struct Profile *HEAD = NULL;
    do {
        cout << "1. Daftar Akun" << endl;
        cout << "2. Login" << endl;
        cout << "3. Profil" << endl;
        cout << "Pilih Menu: ";
        cin >> menu;
        if (menu == 1) {
            daftar();
            cout << "Silahkan Login" << endl;
            cout << endl;
        } else if (menu == 2) {
            masuk();
        } else if (menu == 3) {
            tambahprf(&HEAD);
        } else if (menu == 4){
            profil(HEAD);
        }
    } while (menu != 7);

    return 0;
}
