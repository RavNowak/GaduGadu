#pragma once
#include <stdexcept>
#include <iostream>
#include <string>

class ConnectionError
{
public:
    explicit ConnectionError() {}
    std::string message() { return "Can not connect to server"; }
};

class ListenError
{
private:
    unsigned int port;
public:
    explicit ListenError(const unsigned int& port_)
        :port(port_)
    {}
    std::string message() { return "Error of listening on the port: " + port; }
};