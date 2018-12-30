#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Client.h"
#include "Server.h"
#include "MySQLDatabase.h"

class GaduGadu : public sf::RenderWindow
{
private:
    std::unique_ptr<MySQLDatabase> database;
    Server* server{ nullptr };
    Client* client{ nullptr };
    void setWindowTitle();
    void runServerApplication();
    void runClientApplication();
    void setWindowProperties();
public:
    explicit GaduGadu(sf::WindowHandle& hwnd);
    ~GaduGadu();
    void run();
};