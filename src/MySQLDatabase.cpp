#include <iostream>
#include "MySQLDatabase.h"

MySQLDatabase::MySQLDatabase(
    const std::string& serverAdress_,
    const std::string& userName_,
    const std::string& password_,
    const std::string& databaseName_,
    const unsigned int & port_)
    :serverAdress(serverAdress_)
    , userName(userName_)
    , password(password_)
    , databaseName(databaseName_)
    , port(port_)
{
    mysql_init(&mysql);
}

void MySQLDatabase::connectToDatabase()
{
    if (!mysql_real_connect(&mysql, serverAdress.c_str(), userName.c_str(), password.c_str(), databaseName.c_str(), port, nullptr, 0))
        std::cout << "Failed to connect to the MySQL server: " << mysql_errno(&mysql) << " " << mysql_error(&mysql);
}

void MySQLDatabase::disconnectDatabase() 
{
    mysql_close(&mysql);
}

void MySQLDatabase::showDataFromDatabase(const std::string & query) noexcept
{
    connectToDatabase();
    mysql_select_db(&mysql, databaseName.c_str());
    mysql_query(&mysql, query.c_str());
    idQuestion = mysql_store_result(&mysql);
    while ((row = mysql_fetch_row(idQuestion)) != nullptr)
    {
        for (unsigned int i = 0; i < mysql_num_fields(idQuestion); i++)
            std::cout << row[i] << "\t\t";
        std::cout << "\n";
    }
    disconnectDatabase();
}

void MySQLDatabase::executeUpdateCommand(const std::string & query) noexcept
{
    connectToDatabase();
    mysql_select_db(&mysql, databaseName.c_str());
    mysql_query(&mysql, query.c_str());
    disconnectDatabase();
}

std::string MySQLDatabase::getServerStatus() 
{
    connectToDatabase();
    mysql_select_db(&mysql, databaseName.c_str());
    mysql_query(&mysql, "SELECT status FROM gadugadu.serwer");
    idQuestion = mysql_store_result(&mysql);
    row = mysql_fetch_row(idQuestion);
    disconnectDatabase();
    return row[0];
}

void MySQLDatabase::showHelpCommands()
{
    showDataFromDatabase("SELECT command, description FROM gadugadu.help"); 
}

void MySQLDatabase::showAllClients()
{
    showDataFromDatabase("SELECT id, nick, online FROM gadugadu.clients");
}

void MySQLDatabase::setServerStatus(unsigned int status)
{
    executeUpdateCommand("UPDATE gadugadu.serwer SET status =" + std::to_string(status) + " WHERE id = 1");
}

void MySQLDatabase::setClientConnectionStatus(unsigned int status, std::string& nick)
{
    executeUpdateCommand("UPDATE gadugadu.clients SET online =" + std::to_string(status) + " WHERE nick ='" + nick + "'");
}

void MySQLDatabase::setNewPassword(const std::string & nick, const std::string & newPassword)
{
    executeUpdateCommand("UPDATE gadugadu.clients SET password = md5('" + newPassword + "') WHERE nick = '" + nick + "'");
}

std::string MySQLDatabase::getClientAccountData(std::string& password)
{
    connectToDatabase();
    mysql_select_db(&mysql, databaseName.c_str());
    std::string query = "SELECT nick FROM gadugadu.clients WHERE password = md5('" + password + "')";
    if(mysql_query(&mysql, query.c_str()) == 0)
    {
        idQuestion = mysql_store_result(&mysql);
        row = mysql_fetch_row(idQuestion);
        disconnectDatabase();
        if (row == nullptr)    
            return "";
        else return row[0];
    }
}




