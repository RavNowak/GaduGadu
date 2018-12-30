#pragma once
#include <SFML\Network.hpp>
#include <string>
#include <memory>
#include <vector>
#include "MySQLDatabase.h"

class Server
{
private:
    sf::Packet messageFromClient;
    sf::Packet messageToAllClients;
    sf::Packet messageToClient;
    sf::TcpListener listener;
    std::shared_ptr<sf::TcpSocket> user;
    std::vector<std::shared_ptr<sf::TcpSocket>> clients;
    std::unique_ptr<MySQLDatabase> database;
    sf::SocketSelector selector;
    std::string txtMessage;
    bool runFlag{ true };
    unsigned int port;
    void startListenThePort();
    void addNewClient() noexcept;
    void reveiveMessageFromClients() noexcept;
    void sendMessageToAllClients() noexcept;
public:
    explicit Server(const unsigned int& port_) noexcept;
    Server() = default;
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    Server(Server&&) = default;
    Server& operator=(Server&&) = default;
    ~Server() = default;
    void runServer() noexcept;
    void closeServer() noexcept;
};