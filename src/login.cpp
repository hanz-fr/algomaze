#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "../include/welcome_press_any_key.h" 

using namespace std;


//Format username minimal 8 karakter dan tidak kosong
bool validationUsername(const string& username)
{
    if (username.length() < 4 || username.length() > 20)
    {
        cout << "Username harus memiliki minimal 4 karakter dan maksimal 40 " << endl;
        return false;
    } else if (username.empty())
    {
        cout << "Username tidak boleh kosong." << endl;
        return false;
    }

    const regex pattern("^[a-zA-Z0-9_]+$"); //pattern yang isinya cuma huruf, angka dan underscore
    if (!regex_match(username, pattern))
    {
        cout << "Username hanya boleh berisi huruf, angka, dan underscore" << endl;
        return false;
    }

    return true;

}

//Format password minimal 8 karakter, tidak kosong dan minimal mengandung 1 huruf besar, 1 huruf kecil dan simbol

bool validationPassword(const string & password)
{
    if (password.length() < 8)
    {
        cout << "Password harus memiliki minimal 8 karakter. " << endl;
        return false;
    } else if (password.empty()) 
    {
        cout << "Password tidak boleh kosong." << endl;
        return false;
    }

    regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\W).+$"); //pattern yang isinya minimal 1 huruf besar, 1 huruf kecil dan simbol
    if (!regex_match(password, pattern))
    {
        cout << "Password harus mengandung minimal 1 huruf besar, 1 huruf kecil, dan 1 simbol." << endl;
        return false;
    }

    return true;

}

//nyimpen data username dan password ke file sekaligus login

bool login(const string& username, const string& password)
{
    ifstream file("src/database.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka file database";
        return false;
    }

    string baris;
    while (getline(file, baris)) {
        size_t pos = baris.find('|');
        if (pos == string::npos) continue; // format salah, skip

        string user = baris.substr(0, pos);
        string pass = baris.substr(pos + 1);

        if (user == username && pass == password) {
            return true; // login berhasil
        }
    }

    return false; // login gagal
}

//fungsi untuk regsiter 

void registerUser(const string& username, const string& password)
{
    ofstream file("src/database.txt", ios::app);
    if (!file.is_open()) 
    {
        cout << "Gagal membuka file database";
        return;
    }

    file << username << "|" << password << endl;
    cout << "Register Success! " << endl;
};


void menuLoginorRegister()
{
    cout << "Sebelum bermain, silahkan login atau register terlebih dahulu:  " << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
}

int main()
{
    string messages1 = "Welcome to the Algorithm Maze Game!";
    string author = "Made by group 4";
    string messages3 = "Press any key to continue...";

    //animasi 
    animateText(messages1, 75);
    animateText(author, 75);
    blinkTextUntilKeyPress(messages3, 400);

    string username, password, input;
    while (true)
    {
        menuLoginorRegister();
        cout << "Masukkan pilihan (1 atau 2): ";
        cin >> input;

        if (input == "2")
        {
            while (true)
            {
                cout << "=== Register ===" << endl;
                cout << "Masukkan username: ";
                cin >> username;
            
                cout << "Masukkan password (dengan ketentuan minimal 8 karakter, 1 Huruf besar, 1 huruf kecil, 1 angka, dan 1 simbol): ";
                cin >> password;

                if (validationUsername(username) && validationPassword(password))
                {
                    registerUser(username, password);
                    cout << "Registrasi berhasil! Silahkan login." << endl;

                    break;
                } 
            }
        } else if (input == "1")
        {
            while (true)
            {
                cout << "=== Login ===" << endl;
                cout << "Masukkan username: ";
                cin >> username;

                cout << "Masukkan password: ";
                cin >> password;

                if (login(username, password))
                {
                    cout << "Login berhasil! Selamat datang, " << username << "!" << endl;
                    return 0;
                } else 
                {
                    cout << "Login gagal! Username atau password salah. Silahkan coba lagi." << endl;
                }
            }
        
        } else {
            cout << "Pilihan tidak valid. Silakan masukkan 1 atau 2." << endl;
            continue; 
        }

    }
    
}