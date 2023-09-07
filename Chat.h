#pragma once
#include <iostream>
using namespace std;
#include <string>
#include "Message.h"
#include<exception>
#include<memory>
#include<vector>
#include "sha1.h"
#include "string.h"

#define SIZE 10
#define LOGINLENGTH 10

struct UserLoginExp :public std::exception
{
    const char* what() const noexcept override { return"error: user login is bysy"; }
};
struct UserNameExp :public std::exception
{
    const char* what() const noexcept override { return"error: user name is bysy"; }
};

class Chat
{
    bool isChatWork_ = false;
    std::vector<User> userList_;
    std::vector<Message> messageList_;
    std::shared_ptr<User> currentUser_ = nullptr;
    void login();
    void signUp();
    void ShowChat() ;
    void ShowAllUsersName() const;
    void addMessage();
    std::vector<User>& getAllUsers() { return userList_; }
    std::vector<Message>& getAllMessages() { return messageList_; }
    std::shared_ptr<User> getUserByLogin(const std::string& login) const;
    std::shared_ptr<User> getUserByName(const std::string& name) const;
public:
    Chat();




    enum class CellStatus  {
        free,
        engaged,
        deleted
    };

    void reg(char login_[LOGINLENGTH], char password_[], int pass_length);
    bool login(char login_[LOGINLENGTH], char password_[], int pass_length);
    void unreg(char login_[LOGINLENGTH]);

    //friend void test(Chat& chat);

    struct AuthData 
    {
        AuthData() :
            login(""),
            pass_sha1_hash(0),
            status(CellStatus::free) {
        }

        ~AuthData()
        {
            if (pass_sha1_hash != 0)
                delete[] pass_sha1_hash;
        }

        // копирует логин, забирает внутрь хеш
        AuthData(char login_[LOGINLENGTH], uint* sh1) {
            memcpy(login, login_, LOGINLENGTH);
            pass_sha1_hash = sh1;
            status = CellStatus::engaged;
        }

        // копирует всё
        AuthData& operator = (const AuthData& other) 
        {
            memcpy(login, other.login, LOGINLENGTH);
            if (pass_sha1_hash != 0)
                delete[] pass_sha1_hash;
            pass_sha1_hash = new uint[SHA1HASHLENGTHUINTS];
            memcpy(pass_sha1_hash, other.pass_sha1_hash, SHA1HASHLENGTHBYTES);
            status = other.status;
            return *this;
        }

        // как из класса User вытащить логин в форме login_, сделать из него login и уже этот стринговый логин преобразовать в char login[LOGINLENGTH]?]
        char login[LOGINLENGTH];
        uint* pass_sha1_hash;
        CellStatus status;
    };

    void resize();
    void allocNewMem(int newMemSize);
    int hash_func(char login[LOGINLENGTH], int step);
    int hf_multiply(int val);
    void addinner(char login[LOGINLENGTH], uint* digest);


    AuthData* data;
    int data_count;
    int mem_size;




    void start();
    bool isChatWork() const { return isChatWork_; }
    std::shared_ptr<User> getCurrentUser() const { return currentUser_; }
    void ShowLoginMenu();
    void ShowUserMenu();

};



