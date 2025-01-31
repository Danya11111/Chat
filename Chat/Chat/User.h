#pragma once
#include <iostream>
#include <string>
using namespace std;

class User {
public:
    string login;
    string password;
    string name;

    // Конструктор по умолчанию
    User() : login(""), password(""), name("") {}

    // Конструктор с параметрами
    User(string login, string password, string name) : login(login), password(password), name(name) {}

    // Метод для отправки сообщения
    void sendMessage(const string& message, const string& recipient = "") const {
        if (recipient.empty()) {
            cout << name << " (to everyone): " << message << endl;
        }
        else {
            cout << name << " (to " << recipient << "): " << message << endl;
        }
    }
};