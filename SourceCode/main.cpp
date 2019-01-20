#include<iostream>
#include"Interface.h"
#include"User.h"
using namespace std;

int main() {
    Interface interface;
    User user;
    interface.readUserInfo();

    char index;// For welcome interface return.
    char index_1;// For userInterface return.
    bool index_1_2;// To check if account is successfully deleted.

    while (1) {// welcome interface loop.
        interface.emptyScreen();
        index = interface.welcome();
        if (index == 'Q') {
            break;
        }
        switch (index) {
            case('1'):
                while (1) {// logIn interface loop.
                    index_1_2 = false;
                    interface.emptyScreen();
                    interface.logIn(user);// Enter logIn interface.
                    if (user.getUsername() == "g" && user.getPassword() == "b") {
                        break;
                    }
                    while (1) {// userInterface interface loop.
                        interface.emptyScreen();
                        index_1 = interface.userInterface(user);
                        if (index_1 == 'r') {
                            break;
                        }
                        switch (index_1) {
                            case('1'):// Enter changePassword interface.
                                interface.emptyScreen();
                                interface.changePassword(user);
                                break;
                            case('2'):// Enter deleteAccount interface.
                                interface.emptyScreen();
                                index_1_2 = interface.deleteAccount(user);
                                break;
                        }
                        if (index_1_2) {// If account's been deleted, then go back to logIn interface.
                            break;
                        }
                    }
                }
                break;
            case('2'):
                interface.emptyScreen();
                interface.signUp();// Enter signUp interface.
                break;
        }
    }
    
    interface.writeUserInfo();
    return 0;
}
