#pragma once
#include <mysql.h>
#include <string>

class MySQLDatabase
{
private:
    MYSQL mysql;
    MYSQL_ROW  row;
    MYSQL_RES* idQuestion;
    std::string serverAdress;
    std::string userName;
    std::string password;
    std::string databaseName;
    const unsigned int port;
    void connectToDatabase();
    void disconnectDatabase();
    void showDataFromDatabase(const std::string& query) noexcept;
    void executeUpdateCommand(const std::string& query) noexcept;
public:
    MySQLDatabase(
        const std::string& serverAdress_,
        const std::string& userName_,
        const std::string& password_,
        const std::string& databaseName_,
        const unsigned int& port_);
    MySQLDatabase() = default;
    ~MySQLDatabase() = default;
    MySQLDatabase& operator=(const MySQLDatabase&) = default;
    MySQLDatabase(const MySQLDatabase&) = default;
    std::string getServerStatus();
    std::string getClientAccountData(std::string& password);
    void showHelpCommands();
    void showAllClients();
    void setServerStatus(unsigned int status);
    void setClientConnectionStatus(unsigned int status, std::string& nick);
    void setNewPassword(const std::string& nick, const std::string& newPassword);
};