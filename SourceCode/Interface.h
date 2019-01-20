#include<iostream>
#include<fstream>
#include<string>
#include<regex>
#include"User.h"
#include"AVLTree.h"

#pragma once

using namespace std;

class Interface {
private:
    AVLTree userTree;
    regex pattern;
    string getTime();
public:
    Interface();
    ~Interface();

    void emptyScreen();

    // Record eventName and system time to Log.log.
    void eventLogToFile(string eventName);

    // Relative operations to file named UserInfo.dat.
    void writeUserInfo();
    void readUserInfo();

    // Record change of userTree in graph to TreeGraph.dat.
    void writeTreeGraph();

    // Below are all interfaces.
    char welcome();
        void signUp();
        void logIn(User& user);
            char userInterface(User& user);
                void changePassword(User& user);
                bool deleteAccount(User& user);
};

