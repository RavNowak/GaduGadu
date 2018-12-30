#pragma once
#include <iostream>
#include <conio.h>
#include "Server.h"
#include "Exceptions.h"

void Server::startListenThePort()
{
    if (listener.listen(port) != sf::Socket::Done)
    {
        throw ListenError(port);
    }
    else std::cout << "Waiting for the client...\n";
}

void Server::addNewClient() noexcept
{
    auto client = std::make_shared<sf::TcpSocket>();
    if (listener.accept(*client) == sf::Socket::Done)
    {
        clients.push_back(client);
        selector.add(*client);
    }
}

void Server::reveiveMessageFromClients() noexcept
{
    for (const auto& client : clients)
    {
        if (selector.isReady(*client))
        {
            user = client;
            if ((*client).receive(messageFromClient) == sf::Socket::Done)
            {
                messageFromClient >> txtMessage;
                std::cout << txtMessage << "\n";
                sendMessageToAllClients();
            }
        }
    }
}

void Server::sendMessageToAllClients() noexcept
{
    for (const auto& client : clients)
    {
        if (client != user)
        {
            messageToAllClients.clear();
            messageToAllClients << txtMessage;
            (*client).send(messageToAllClients);
        }
    }
}

Server::Server(const unsigned int & port_) noexcept
    :port(port_)
{
    database = std::make_unique<MySQLDatabase>(MySQLDatabase("127.0.0.1", "root", "", "gadugadu", 3307));
    database->setServerStatus(1);
    startListenThePort();
    selector.add(listener);
}

void Server::runServer() noexcept
{
    while (runFlag)
    {
        if (selector.wait())
        {
            if (selector.isReady(listener))
                addNewClient();
            else
                reveiveMessageFromClients();
        }
        sf::sleep(sf::milliseconds(300));
    }
}

void Server::closeServer() noexcept
{
        while (runFlag)
        {
            if (_getch() == 27)
            {
                database->setServerStatus(0);
                runFlag = false;
                listener.close();
                selector.clear();
            }
        }
    }

