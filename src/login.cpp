#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>
#include "../include/welcome_press_any_key.h"
#include "../include/clear_screen.h"
#include "../include/login.h"

using namespace std;

string toLower(const string &str)
{
    string lowerStr = str;
    for (char &c : lowerStr)
    {
        c = tolower(c);
    }
    return lowerStr;
}

// Format username minimal 8 karakter dan tidak kosong
bool validationUsername(const string &username)
{
    if (username.length() < 4 || username.length() > 20)
    {
        cout << "Username harus memiliki minimal 4 karakter dan maksimal 40 " << endl;
        return false;
    }
    else if (username.empty())
    {
        cout << "Username tidak boleh kosong." << endl;
        return false;
    }

    const regex pattern("^[a-zA-Z0-9_]+$"); // pattern yang isinya cuma huruf, angka dan underscore
    if (!regex_match(username, pattern))
    {
        cout << "Username hanya boleh berisi huruf, angka, dan underscore" << endl;
        return false;
    }

    return true;
}

// Format password minimal 8 karakter, tidak kosong dan minimal mengandung 1 huruf besar, 1 huruf kecil dan simbol

bool validationPassword(const string &password)
{
    if (password.length() < 8)
    {
        cout << "Password harus memiliki minimal 8 karakter. " << endl;
        return false;
    }
    else if (password.empty())
    {
        cout << "Password tidak boleh kosong." << endl;
        return false;
    }

    regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\W).+$"); // pattern yang isinya minimal 1 huruf besar, 1 huruf kecil dan simbol
    if (!regex_match(password, pattern))
    {
        cout << "Password harus mengandung minimal 1 huruf besar, 1 huruf kecil, dan 1 simbol." << endl;
        return false;
    }

    return true;
}

// nyimpen data username dan password ke file sekaligus login

bool login(const string &username, const string &password)
{
    ifstream file("database/databaseUsers.txt");
    if (!file.is_open())
    {
        cout << "Gagal membuka file database";
        return false;
    }

    string baris;
    while (getline(file, baris))
    {
        size_t pos = baris.find('|');
        if (pos == string::npos)
            continue; // format salah, skip

        string user = baris.substr(0, pos);
        string pass = baris.substr(pos + 1);

        if (user == username && pass == password)
        {
            cout << "Login berhasil! Selamat datang, " << username << "!" << endl;
            return true;
        }
    }

    return false; // login gagal
}

// fungsi untuk ngecek apakah username sudah ada di database atau belum
bool checkingUsername(const string &usernameToCheck)
{
    ifstream file("database/databaseUsers.txt");
    if (!file.is_open())
    {
        cout << "Gagal membuka file database";
        return false;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string username, password;

        getline(ss, username, '|');
        getline(ss, password);

        if (username == usernameToCheck)
        {
            return true;
        }

        if (toLower(username) == toLower(usernameToCheck))
        {
            return true;
        }
    }

    return false;
}

// fungsi untuk regsiter

void registerUser(const string &username, const string &password)
{

    if (checkingUsername(username))
    {
        cout << "Username sudah ada, silahkan pilih username lain." << endl;
        return;
    }

    ofstream file("database/databaseUsers.txt", ios::app);
    if (!file.is_open())
    {
        cout << "Gagal membuka file database";
        return;
    }

    file << username << "|" << password << endl;
    cout << "Registrasi Sukses! Silahkan Login  " << endl;
};

// fungsi untuk membuat login session

void createLoginSession(const string &username)
{
    ofstream sessionFile("database/loginSession.txt");
    if (!sessionFile.is_open())
    {
        cout << "Database login session tidak dapat dibuka" << endl;
        return;
    }

    sessionFile << username << endl;
};

void menuLoginorRegister()
{
    string username, password, input;

    cout << "Sebelum bermain, silahkan login atau register terlebih dahulu:  " << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;

    while (true)
    {
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
                    break; 
                }
            }
        }
        else if (input == "1")
        {
            int attempts = 0;
            const int maxAttempts = 3;

            while (attempts < maxAttempts)
            {
                cout << "=== Login ===" << endl;
                cout << "Masukkan username: ";
                cin >> username;

                cout << "Masukkan password: ";
                cin >> password;

                if (login(username, password))
                {
                    createLoginSession(username);
                    return; 
                }
                else
                {
                    attempts++;
                    int remaining = maxAttempts - attempts;
                    cout << "Login gagal! username atau password salah." << endl;

                    if (remaining > 0)
                    {
                        cout << "Sisa percobaan login: " << remaining << endl;
                    }
                }
            }

            // batas kesempatan login
            cout << "Anda telah melebihi batas percobaan login.\n" << endl;
            continue; 
        }
        else
        {
            cout << "Pilihan tidak valid. Silakan masukkan 1 atau 2." << endl;
            continue;
        }
    }
}
