#pragma once
#include <iostream>
using namespace std;
#include <string>

class User
{
    const std::string login_;
    std::string password_;
    std::string name_;

public:
    User(const std::string& login, const std::string& password, const std::string& name) :login_(login), password_(password), name_(name) {}
    const std::string& getUserLogin() const { return login_; }
    const std::string& getUserPassword() const { return password_; }
    void setUserPassword(const std::string& password) { password_ = password; }
    const std::string& getUserName() const { return name_; }
    void setUserName(const std::string& name) { name_ = name; }

};