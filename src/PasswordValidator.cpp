#include <iostream>
#include <conio.h>
#include "PasswordValidator.h"

PasswordValidator::PasswordValidator()
{
    database = std::make_unique<MySQLDatabase>(MySQLDatabase("127.0.0.1", "root", "Fabregas96", "gadugadu", 3307));
}

bool PasswordValidator::SignIn() noexcept
{
    while (true)
    {
        std::cout << "Login: ";
        std::cin >> login;
        std::cout << "Password: ";
        setPassword('*', password);
        if (database->getClientAccountData(password) != login)
            std::cout << "\nIncorrect login or password !\a\n";
        else
        {
            system("cls");
            std::cout << "~~Welcome in GaduGadu communicator~~\n";
            break;
        }
    }
    return true;
}

std::string PasswordValidator::getLogin() const noexcept
{
    return login;
}

void PasswordValidator::setNewPassword() noexcept
{
    std::string newPassword;
    std::string repeatedPassword;
    std::cout << "New password: ";
    setPassword('*', newPassword);
    std::cout << "Repeat new password: ";
    setPassword('*', repeatedPassword);
    confirmNewPassword(newPassword, repeatedPassword);
}

void PasswordValidator::setPassword(const char coding, std::string& encryptedWord) noexcept
{
    char sign;
    encryptedWord.clear();
    while (true)
    {
        sign = _getch();
        if (sign == 13)
        {
            std::cout << "\n";
            break;
        }
        encryptedWord += sign;
        std::cout << coding;
    }
}

void PasswordValidator::confirmNewPassword(const std::string & newPassword, const std::string & repeatedPassword) noexcept
{
    if (newPassword == repeatedPassword)
    {
        database->setNewPassword(login, newPassword);
        password = newPassword;
        std::cout << "Password changed correctly\n";
    }
    else
        std::cout << "Passwords are not the same!\n";
}
