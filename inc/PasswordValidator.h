#pragma once
#include <string>
#include <memory>
#include "MySQLDatabase.h"

class PasswordValidator
{
private:
    std::unique_ptr<MySQLDatabase> database;
    std::string login;
    std::string password;
    void setPassword(const char coding, std::string& encryptedWord) noexcept;
    void confirmNewPassword(const std::string& newPassword, const std::string& repeatedPassword) noexcept;
public:
    PasswordValidator();
    bool SignIn() noexcept;
    std::string getLogin()const noexcept;
    void setNewPassword()noexcept;
};