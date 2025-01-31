#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm> // для std::remove
#include "User.h"
#include "Message.h"
#include "Chat.h"
using namespace std;

int main() {
    Chat chat;
    cout << "Hi!" << endl << "We are glad to welcome you to our 'Whatschat'!" << endl;
    int f = 0;
    int count = 0;
    do {
        cout << "To register, press - 1" << endl;
        if (count > 0) {
            cout << "To log in, press - 2" << endl;
        }
        cout << "If you want to exit and close the application, press - 0" << endl;
        int n;
        cin >> n;
        switch (n) {
        case 1: {
            cout << "Great! Let's get acquainted)" << endl;
            string name;
            string login;
            string password;
            cout << "Enter your name: "; cin >> name;
            cout << "Enter your login: "; cin >> login;
            cout << "Enter your password: "; cin >> password;
            chat.registerUser(login, password, name);
            count++;
            break; // Добавлено break
        }
        case 2: {
            string login, password;
            cout << "Enter your login: "; cin >> login;
            cout << "Enter your password: "; cin >> password;
            if (chat.loginUser(login, password)) {
                int option;
                do {
                    cout << endl;
                    cout << "1. Send a message" << endl
                        << "2. View chat messages" << endl
                        << "3. Log out" << endl
                        << "Enter your choice: ";
                    cin >> option;

                    switch (option) {
                    case 1: {
                        string message, recipient;
                        cout << "Enter your message: ";
                        cin.ignore(); // Игнорируем оставшийся символ новой строки
                        getline(cin, message);
                        int n = 2;
                        if (count > 1) {
                            cout << "Enter who you want to send the message to: " << endl;
                            cout << "Private message - 1, All - 2" << endl;
                            cin >> n;
                        }
                        
                        if (n == 2) {
                            chat.sendMessage(login, message); // Sending message to everyone
                        }
                        else if (n == 1) {
                            chat.listUsers(login, count);
                            cout << "Enter the login of the person you want to send the message to: ";
                            string recipient; cin >> recipient;
                            chat.sendMessage(login, message, recipient);
                        }
                        else {
                            cout << "Error, try again!" << endl;
                        }
                        cout << endl;
                        break;
                    }
                    case 2: {
                        cout << endl;
                        chat.viewMessages(login); // Просмотр всех сообщений
                        cout << endl;
                        break;
                    }
                    case 3: {
                        cout << endl;
                        chat.logoutUser(login); // Выход из системы
                        break;
                    }
                    default:
                        cout << "Invalid option. Please try again." << endl;
                    }
                } while (option != 3);
            }
            break; // Добавлено break
        }
        case 0: {
            f = 1; // Завершение программы
            break;
        }
        default:
            cout << "Invalid option. Please try again." << endl;
        }
    } while (f == 0);

    cout << "Goodbye!" << endl;
    return 0;
}