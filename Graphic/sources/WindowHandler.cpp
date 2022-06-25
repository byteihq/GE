// Copyright 2022 byteihq <kotov038@gmail.com>

#include <WindowHandler.h>
#include <ObjectStorage.h>
#include <Presets.h>

WindowHandler::WindowHandler(uint16_t Width, uint16_t Height, uint8_t FrameLimit, const std::string &Title) : Window(
        sf::VideoMode(Width, Height), Title) {
    Window.setFramerateLimit(FrameLimit);
}

void WindowHandler::Run() {
    Handles.push_back(ObjectStorage::GetInstance()->CreateNewObject(4, 0.1 * WINDOW_WIDTH, 0.9 * WINDOW_WIDTH,
                                                                    0.1 * WINDOW_HEIGHT, 0.9 * WINDOW_HEIGHT));
    Handles.push_back(ObjectStorage::GetInstance()->CreateNewObject(4, 0.1 * WINDOW_WIDTH, 0.9 * WINDOW_WIDTH,
                                                                    0.1 * WINDOW_HEIGHT, 0.9 * WINDOW_HEIGHT));
    while (Window.isOpen()) {
        while (Window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                Close();
            }
            if (Event.type == sf::Event::KeyPressed) {
                if (Event.key.code == sf::Keyboard::Escape) {
                    Close();
                }
            }
        }
        ObjectStorage::GetInstance()->MoveObj(Handles.back(), 1, 3);
        Refresh();
    }
}

void WindowHandler::Refresh() {
    Window.clear();
    for (int handle: Handles) {
        Draw(handle);
    }
    Window.display();
}

void WindowHandler::Draw(int ObjHandle) {
    if (auto res = ObjectStorage::GetInstance()->GetObject(ObjHandle); res.first) {
        for (const auto &shape: res.second->GetDrawable()) {
            Window.draw(*shape);
        }
    }
}

void WindowHandler::Close() {
    Window.close();
}

WindowHandler::~WindowHandler() {
    Close();
}
