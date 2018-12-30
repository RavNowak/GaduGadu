#include <iostream>
#include "Client.h"
#include "Exceptions.h"

void Client::connectToServer(const sf::Time & time)
{
    if (socket.connect(ipAddress, port, time) != sf::Socket::Done)
    {
        throw ConnectionError();
    }
}

bool Client::checkCorrectnessOfSentData() noexcept
{
    if (socket.send(messageToServer) != sf::Socket::Done)
    {
        std::cout << "Sending parameters error\n";
        return false;
    }
    else return true;
}

bool Client::checkClientCommand(std::string& message) noexcept 
{
    if (check_clear_command(message)  ||
        check_kill_command(message)   ||
        check_all_command(message)    ||
        check_time_command(message)   ||
        check_help_command(message)   ||
        check_passwd_command(message) ||
        check_sound_command(message))
        return true;
    else return false;
}

void Client::sendAutomaticMessage(const std::string & message) noexcept 
{
    messageToServer << passwordValidator.getLogin() + " is " + message;
    socket.send(messageToServer);
}

bool Client::check_clear_command(const std::string & message) const noexcept
{
    if (message == "/clear")
    {
        system("cls");
        return true;
    }
    else return false;
}

bool Client::check_all_command(const std::string & message) const noexcept
{
    if (message == "/all")
    {
        database->showAllClients();
        return true;
    }
    else return false;
}

bool Client::check_sound_command(const std::string & message)noexcept
{
    if (message == "/sound")
    {
        messageSound.changeMessageSoundStatus();
        return true;
    }
    else return false;
}

bool Client::check_help_command(const std::string & message) const noexcept
{
    if (message == "/help" || message == "/h")
    {
        database->showHelpCommands();
        return true;
    }
    else return false;
}

bool Client::check_time_command(const std::string & message)noexcept
{
    if (message == "/time")
    {
        std::cout << "Time elapsed since logging in: " << clock.getTimeElapsedSinceLoggingIn() << "\n";
        return true;
    }
    else return false;
}

bool Client::check_kill_command(const std::string & message)noexcept
{
    if (message == "/kill")
    {
        database->setClientConnectionStatus(0, getClientName());
        sendAutomaticMessage("offline");
        runFlag = false;
        return true;
    }
    else return false;
}

bool Client::check_passwd_command(const std::string & message) noexcept
{
    if (message == "/passwd")
    {
        passwordValidator.setNewPassword();
        return true;
    }
    else return false;
}

Client::Client(const sf::IpAddress & ipAdress_, const unsigned int & port_) noexcept
    :ipAddress(ipAdress_)
    , port(port_)
{
    database = std::make_unique<MySQLDatabase>(MySQLDatabase("127.0.0.1", "root", "", "gadugadu", 3307));
    if (passwordValidator.SignIn())
    {
        database->setClientConnectionStatus(1, passwordValidator.getLogin());
        connectToServer(sf::seconds(5.0f));
        socket.setBlocking(false);
        sendAutomaticMessage("online");
    }
}

void Client::receiveMessageFromServer() noexcept
{
    std::string txtMessage;
    while (runFlag)
    {
        if (socket.receive(messageFromServer) == sf::Socket::Done)
        {
            messageFromServer >> txtMessage;
            std::cout << txtMessage << "\n";
            if (messageSound.getMessageSoundStatus())
                messageSound.play();
        }
        sf::sleep(sf::milliseconds(500));
    }
}

void Client::sendMessageToServer() noexcept
{
    while (runFlag)
    {
        std::string newMessage;
        messageToServer.clear();
        std::getline(std::cin, newMessage);
        if (checkClientCommand(newMessage))
            continue;
        else messageToServer << passwordValidator.getLogin() + ": " + newMessage;
        if (!newMessage.empty())
            if (checkCorrectnessOfSentData() == false)
                break;
    }
}

sf::IpAddress Client::getIpAdress() const noexcept
{
    return ipAddress;
}

unsigned int Client::getPort() const noexcept
{
    return port;
}

std::string Client::getClientName() const noexcept
{
    return passwordValidator.getLogin();
}

