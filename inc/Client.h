#pragma once
#include <SFML\Network.hpp>
#include <SFML\Audio.hpp>
#include <string>
#include <memory>
#include "MySQLDatabase.h"
#include "MyClock.h"
#include "MessageSound.h"
#include "PasswordValidator.h"

class Client
{
private:
    sf::Packet messageFromServer;
    sf::Packet messageToServer;
    sf::TcpSocket socket;
    sf::IpAddress ipAddress;
    MyClock clock;
    MessageSound messageSound;
    PasswordValidator passwordValidator;
    std::unique_ptr<MySQLDatabase> database;
    unsigned int port;
    bool runFlag { true };
    void connectToServer(const sf::Time& time);
    bool checkCorrectnessOfSentData() noexcept;
    bool checkClientCommand(std::string& message) noexcept;
    void sendAutomaticMessage(const std::string& message) noexcept;
    bool check_clear_command(const std::string& message)const noexcept;
    bool check_all_command(const std::string& message)const noexcept;
    bool check_sound_command(const std::string& message)noexcept;
    bool check_help_command(const std::string& message)const noexcept;
    bool check_time_command(const std::string& message)noexcept;
    bool check_kill_command(const std::string& message)noexcept;
    bool check_passwd_command(const std::string& message)noexcept;
public:
    Client() = default;
    Client(const sf::IpAddress& ipAdress_, const unsigned int& port_) noexcept;
    ~Client() = default;
    Client(const Client&) = default;
    Client& operator=(const Client&) = default;
    Client(Client&&) = default;
    Client& operator=(Client&&) = default;
    void receiveMessageFromServer() noexcept;
    void sendMessageToServer() noexcept;
    sf::IpAddress getIpAdress() const noexcept;
    unsigned int getPort() const noexcept;   
    std::string getClientName() const noexcept;
};


