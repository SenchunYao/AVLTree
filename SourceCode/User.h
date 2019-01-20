#include<iostream>
#include<string>

#pragma once

using namespace std;

class User {
private:
    string username;
    string password;
public:
    User(string _username = "", string _password = "");
    User(const User& rhs);
    User& operator=(const User& rhs);

    // Do nothing.
    ~User();

    // As the names of the methods represent.
    void setUsername(string& _username);
    void setPassword(string& _password);
    string getUsername();
    string getPassword();

    // Compare their names.
    bool operator>(const User& rhs) const;
    bool operator<(const User& rhs) const;

    // Check usernames and passwords.
    bool operator==(const User& rhs) const;

    // Only display username.
    void displayUsername(ostream& out);

    // Display username + " " + passowrd.
    void displayAll(ostream& out);

    // in >> username >> password;
    void read(istream& in);
};

// Only display username.
ostream& operator<<(ostream& out, User& rhs);

// in >> username >> password;
istream& operator>>(istream& in, User& rhs);