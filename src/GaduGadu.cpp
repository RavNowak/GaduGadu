#include <iostream>
#include <conio.h>
#include "GaduGadu.h"
#include "Exceptions.h"

GaduGadu::GaduGadu(sf::WindowHandle& hwnd) : sf::RenderWindow(hwnd)
{
    database = std::make_unique<MySQLDatabase>(MySQLDatabase("127.0.0.1", "root", "", "gadugadu", 3307));
    setWindowProperties();
}

GaduGadu::~GaduGadu()
{
    if (server != nullptr)
        delete server;
    else
        delete client;
}

void GaduGadu::run()
{
    setWindowTitle();
    if (database->getServerStatus() == "0")
        runServerApplication();
    else
        runClientApplication();
}

void GaduGadu::setWindowTitle()
{
    if(database->getServerStatus() == "0")
        setTitle("Server");
    else
        setTitle("GaduGadu");
}

void GaduGadu::runClientApplication()
{
    try
    {
        client = new Client("127.0.0.1", 10000);
        sf::Thread receiveMessageFromServerThread(&Client::receiveMessageFromServer, client);
        receiveMessageFromServerThread.launch();
        sf::Thread sendMessageToServerThread(&Client::sendMessageToServer, client);
        sendMessageToServerThread.launch();
    }
    catch (ConnectionError& error)
    {
        std::cout << error.message() << std::endl;
    }
}

void GaduGadu::setWindowProperties()
{
    setPosition(sf::Vector2i(200, 100));
    setActive(true);
    setSize(sf::Vector2u(400, 400));
}

void GaduGadu::runServerApplication()
{
    try
    {
        server = new Server(10000);
        sf::Thread runServerThread(&Server::runServer, server);
        runServerThread.launch();
        sf::Thread closeServerThread(&Server::closeServer, server);
        closeServerThread.launch();
    }
    catch (ListenError& error)
    {
        std::cout << error.message() << std::endl;
    }
}
