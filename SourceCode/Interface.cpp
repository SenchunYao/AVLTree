#include "Interface.h"

void Interface::signUp() {
    string username, password;
    cout << "Username(email):  ";
    cin >> username;
    if (userTree.isExisted(username)) {// This username already exists!
        cerr << username << " already exits!" << endl;
        username = "";
    }
    while (!regex_match(username, pattern)) {
        cerr << "Illegal username! " << endl <<
            "Enter \"r\" to return " << endl <<
            "or re-Enter your email:  ";
        cin >> username;
        if (username == "r") {
            return;
        }
        if (userTree.isExisted(username)) {// This username already exists!
            cerr << username << " already exits!" << endl;
            username = "";
        }
    }
    cout << "Password:  ";
    cin >> password;
    userTree.pushBack(User(username, password));// New user added.
    writeUserInfo();// Update UserInfo.dat
    writeTreeGraph();
    eventLogToFile(username + " has signed up");// Record event to Log.log
}

void Interface::logIn(User& user) {
    cout << "Please enter username and password:  " << endl;
    cin >> user;
    while (!userTree.isExisted(user)) {// User not found.
        cerr << "User not found! Please re-enter or enter \"g b\" to go back:  " << endl;
        cin >> user;
        if (user.getUsername() == "g" && user.getPassword() == "b") {// Go back to the upper interface.
            return;
        }
    }
    eventLogToFile(user.getUsername() + " has loged in");
}

char Interface::userInterface(User & user) {
    cout << "Hi, " << user.getUsername() << "!" << endl <<
        "Please enter: " << endl <<
        "1:  Change password" << endl <<
        "2:  Delete account" << endl <<
        "r:  return" << endl;
    char ch;
    cin >> ch;
    while (ch != '1' && ch != '2' && ch != 'r') {// Out of the options.
        cerr << "Please re-enter:  ";
        cin >> ch;
    }
    return ch;
}

void Interface::changePassword(User & user) {
    string oldPassword = user.getPassword();
    cout << "Please enter NEW password:  ";
    string password;
    cin >> password;
    userTree.find(user).setPassword(password);// Update the password of this user in userTree.
    writeUserInfo();
    eventLogToFile(user.getUsername() + " has changed password from " + oldPassword + " to " + password);
}

bool Interface::deleteAccount(User & user) {
    cout << "Please enter \"DELETE\" to confirm or \"r\" to go back:  ";
    string cmd;
    cin >> cmd;
    while (cmd != "DELETE" && cmd != "r") {
        cin >> cmd;
        cerr << "Please enter \"DELETE\" to confirm or \"r\" to go back:  ";
    }
    if (cmd == "r") {
        return false;
    } else if (cmd == "DELETE") {
        userTree.pop(user);// User deleted.
        writeUserInfo();// Update UserInfo.dat
        writeTreeGraph();
        eventLogToFile(user.getUsername() + " has deleted the account");// Record event to Log.log
        return true;
    }
}

string Interface::getTime() {
    time_t now = time(nullptr);
    tm stdNow;
    localtime_s(&stdNow, &now);
    int tempInt;
    string returnStr, toStr;
    tempInt = stdNow.tm_year + 1900;// Get year.
    returnStr += to_string(tempInt) + "/";

    tempInt = stdNow.tm_mon + 1;// Get month.
    toStr = to_string(tempInt);
    if (toStr.length() == 1) {// Standardize.
        toStr = "0" + toStr;
    }
    returnStr += toStr + "/";

    tempInt = stdNow.tm_mday;// Get day.
    toStr = to_string(tempInt);
    if (toStr.length() == 1) {// Standardize.
        toStr = "0" + toStr;
    }
    returnStr += toStr + " ";

    tempInt = stdNow.tm_hour;// Get hour.
    toStr = to_string(tempInt);
    if (toStr.length() == 1) {// Standardize.
        toStr = "0" + toStr;
    }
    returnStr += toStr + ":";

    tempInt = stdNow.tm_min;// Get minute.
    toStr = to_string(tempInt);
    if (toStr.length() == 1) {// Standardize.
        toStr = "0" + toStr;
    }
    returnStr += toStr + ":";

    tempInt = stdNow.tm_sec;// Get second.
    toStr = to_string(tempInt);
    if (toStr.length() == 1) {// Standardize.
        toStr = "0" + toStr;
    }
    returnStr += toStr;
    return returnStr;
}

Interface::Interface() {
    pattern = "([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)";// Match email format.
}

Interface::~Interface() {
}

void Interface::emptyScreen() {
    system("cls");
}

void Interface::eventLogToFile(string eventName) {
    ofstream logOut("Log.log", ofstream::app);// Open file stream.
    if (logOut.is_open()) {// File's opened.
        logOut << eventName << " at " << getTime() << "." << endl << endl;
        logOut.close();// Close file.
    }
}

void Interface::writeUserInfo() {
    ofstream of("UserInfo.dat", fstream::out);// Open file stream.
    if (of.is_open()) {// File's opened.
        userTree.inorderOut(of);
        of.close();// Close file.
    }
}

void Interface::readUserInfo() {
    ifstream ifs("UserInfo.dat", fstream::in);// Open file stream.
    User tempUser;
    if (ifs.is_open()) {// File's opened.
        while (!ifs.eof()) {
            ifs >> tempUser;
            if (tempUser.getUsername() == "" && tempUser.getPassword() == "") {
                continue;
            }
            userTree.pushBack(tempUser);
        }
        ifs.close();// Close file.
    }
}

void Interface::writeTreeGraph() {
    ofstream of("TreeGraph.dat", ofstream::app);// Open file stream.
    if (of.is_open()) {// File's opened.
        userTree.setDataLengthForDisplay(12);
        userTree.graphOut(of);
        of << endl << "==========================================================================" << endl << endl;
        of.close();// Close file.
    }
}

char Interface::welcome() {
    cout << "Welcome, please enter: " << endl <<
        "1:  Log-in" << endl <<
        "2:  Sign-up" << endl <<
        "Q:  Quit" << endl;
    char ch;
    cin >> ch;
    while (ch != '1' && ch != '2' && ch != 'Q') {// Out of the options.
        cout << "Please re-enter:  ";
        cin >> ch;
    }
    return ch;
}
