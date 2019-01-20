#include "User.h"

User::User(string _userName, string _password) : username(_userName), password(_password) {}

User::User(const User & rhs) {
    username = rhs.username;
    password = rhs.password;
}

User::~User() {}

void User::setUsername(string& _userName) {
    username = _userName;
}

void User::setPassword(string& _password) {
    password = _password;
}

string User::getUsername() {
    return username;
}

string User::getPassword() {
    return password;
}

bool User::operator>(const User & rhs) const {
    return username > rhs.username;
}

bool User::operator<(const User & rhs) const {
    return username < rhs.username;
}

bool User::operator==(const User & rhs) const {
    return (username == rhs.username && password == rhs.password);
}

User & User::operator=(const User & rhs) {
    username = rhs.username;
    password = rhs.password;
    return *this;
}

void User::displayUsername(ostream & out) {
    out << username;
}

void User::displayAll(ostream & out) {
    out << username << " " << password;
}

void User::read(istream & in) {
    in >> username >> password;
}

ostream & operator<<(ostream & out, User& rhs) {
    rhs.displayUsername(out);
    return out;
}

istream & operator>>(istream & in, User& rhs) {
    rhs.read(in);
    return in;
}