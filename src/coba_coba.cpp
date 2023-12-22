#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

map<string, string> loadLanguages() {
    map<string, string> languages;
    ifstream langFile("data/languages.txt");

    if (langFile.is_open()) {
        string line;
        while (getline(langFile, line)) {
            size_t pos = line.find(':');
            if (pos != string::npos) {
                string langCode = line.substr(0, pos);
                string langName = line.substr(pos + 1);
                languages[langCode] = langName;
            }
        }

        langFile.close();
    }

    return languages;
}

void saveLanguage(const string& languageCode) {
    ofstream langFile("data/current_language.txt");

    if (langFile.is_open()) {
        langFile << languageCode;
        langFile.close();
    }
}

void changeLanguage() {
    map<string, string> languages = loadLanguages();

    cout << "Pilih bahasa:" << endl;
    int i = 1;
    for (const auto& lang : languages) {
        cout << "[" << i << "] " << lang.second << endl;
        i++;
    }

    int choice;
    cout << "Pilihan Anda: ";
    cin >> choice;

    if (choice > 0 && choice <= languages.size()) {
        auto it = languages.begin();
        advance(it, choice - 1);
        saveLanguage(it->first);
        cout << "\n" << BG_SUCCESS << " SUCCESS " << RESET << " Bahasa berhasil diubah!" << endl;
    } else {
        cout << ERROR << "ERROR " << RESET << " Pilihan bahasa tidak valid." << endl;
    }
}

string getCurrentLanguage() {
    ifstream langFile("data/current_language.txt");

    if (langFile.is_open()) {
        string languageCode;
        langFile >> languageCode;
        langFile.close();
        return languageCode;
    }

    return "default";
}



// Fungsi untuk memuat bahasa dari file
void loadLanguage(const string& filename, map<string, string>& translations) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            size_t delimiterPos = line.find(':');
            if (delimiterPos != string::npos) {
                string key = line.substr(0, delimiterPos);
                string value = line.substr(delimiterPos + 1);
                translations[key] = value;
            }
        }
        file.close();
    } else {
        cerr << "Error: Unable to open language file: " << filename << endl;
    }
}

// Fungsi untuk menerjemahkan teks
string translate(const string& key, const map<string, string>& translations) {
    auto it = translations.find(key);
    if (it != translations.end()) {
        return it->second;
    }
    return key; // Return key if translation not found
}

int main() {
    map<string, string> translations;

    // Pilih bahasa dengan integer
    int languageChoice;
    cout << "Choose language:\n";
    cout << "1. English\n";
    cout << "2. Indonesian\n";
    cout << "Enter the number corresponding to your choice: ";
    cin >> languageChoice;

    string languageFile;
    switch (languageChoice) {
        case 1:
            languageFile = "lang/english.txt";
            break;
        case 2:
            languageFile = "lang/indonesian.txt";
            break;
        default:
            cerr << "Invalid choice. Defaulting to English.\n";
            languageFile = "english.txt";
            break;
    }

    // Muat bahasa yang dipilih
    loadLanguage(languageFile, translations);

    // Contoh penggunaan terjemahan
    cout << translate("greeting", translations) << endl;
    cout << translate("menu", translations) << endl;
    cout << translate("exit", translations) << endl;

    return 0;
}
