#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm> // для std::remove
#include "User.h"
#include "Message.h"
using namespace std;

class Chat {
private:
    map<string, User> users;
    vector<string> onlineUsers;
    vector<Message> publicMessages;
    map<string, vector<Message>> privateMessages;

public:
    bool registerUser(const string& login, const string& password, const string& name) {
        if (users.count(login)) {
            cout << "Error: login is already taken." << endl;
            return false; // Логин уже занят
        }
        users[login] = User(login, password, name);
        cout << "User  " << name << " successfully registered!" << endl;
        return true;
    }

    bool loginUser(const string& login, const string& password) {
        if (!users.count(login) || users[login].password != password) {
            cout << "Error: incorrect login or password." << endl;
            return false; // Неверный логин или пароль
        }
        onlineUsers.push_back(login); // Добавляем пользователя в список онлайн
        cout << "User  " << login << " logged in." << endl;
        return true;
    }

    void logoutUser(const string& login) {
        onlineUsers.erase(remove(onlineUsers.begin(), onlineUsers.end(), login), onlineUsers.end());
        cout << "User  " << login << " logged out." << endl;
    }

    void sendMessage(const string& senderLogin, const string& message, const string& recipient = "") {

        if (!recipient.empty()) { // Личное сообщение
            if (!users.count(recipient)) {
                cout << "Error: user " << recipient << " not found." << endl;
                return;
            }
            privateMessages[senderLogin].emplace_back(senderLogin, message, recipient);
            privateMessages[recipient].emplace_back(senderLogin, message, recipient);
            cout << users[senderLogin].name << " (to " << recipient << "): " << message << endl;
        }

        else { // Сообщение всем
            publicMessages.emplace_back(senderLogin, message);
            cout << users[senderLogin].name << " (to everyone): " << message << endl;
        }
    }

    void listUsers(string login, int count) const {
        if (count > 1) {
            cout << "Registered users:" << endl;
            for (const auto& pair : users) {
                if (pair.first != login) {
                    cout << "- " << pair.second.name << " (login: " << pair.first << ")" << endl;
                }
            }
        }

    }

    void viewMessages(const string& login) const {
        cout << "Chat messages for " << users.at(login).name << ":" << endl;

        // Публичные сообщения
        for (const auto& msg : publicMessages) {
            cout << msg.sender << " (to everyone): " << msg.content << endl;
        }

        // Личные сообщения для данного пользователя
        if (privateMessages.count(login)) {
            for (const auto& msg : privateMessages.at(login)) {
                cout << msg.sender << " (to " << msg.recipient << "): " << msg.content << endl;
            }
        }
    }
};