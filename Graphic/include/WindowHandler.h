// Copyright 2022 byteihq <kotov038@gmail.com>

#ifndef GRAPHICENGINE_WINDOWHANDLER_H
#define GRAPHICENGINE_WINDOWHANDLER_H

#include <SFML/Graphics.hpp>
#include <Object.h>
#include <string>
#include <vector>

class WindowHandler {
private:
    sf::RenderWindow Window;
    sf::Event Event;
    std::vector<size_t> Handles;

private:
    void Close();

public:
    explicit WindowHandler(uint16_t Width, uint16_t Height, uint8_t FrameLimit, const std::string &Title);

    WindowHandler(const WindowHandler &) = delete;

    WindowHandler &operator=(const WindowHandler &) = delete;

    ~WindowHandler();

    void Draw(size_t ObjHandle);

    void Refresh();

    void Run();
};

#endif //GRAPHICENGINE_WINDOWHANDLER_H
