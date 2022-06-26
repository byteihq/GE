// Copyright 2022 byteihq <kotov038@gmail.com>

#include <WindowHandler.h>
#include <ObjectStorage.h>
#include <Presets.h>

WindowHandler::WindowHandler(uint16_t Width, uint16_t Height, uint8_t FrameLimit, const std::string &Title) : Window(
        sf::VideoMode(Width, Height), Title) {
    Window.setFramerateLimit(FrameLimit);
}

void WindowHandler::Run() {
    while (Window.isOpen()) {
        while (Window.pollEvent(Event)) {
            if (Event.type == sf::Event::Closed) {
                Close();
            }
            if (Event.type == sf::Event::KeyPressed) {
                if (Event.key.code == sf::Keyboard::Escape) {
                    Close();
                } else if (Event.key.code == sf::Keyboard::N) {
                    Handles.push_back(
                            ObjectStorage::GetInstance()->CreateNewObject(4, 0.1f * WINDOW_WIDTH, 0.9f * WINDOW_WIDTH,
                                                                          0.1f * WINDOW_HEIGHT, 0.9f * WINDOW_HEIGHT));
                } else if (Event.key.code == sf::Keyboard::D) {
                    if (Handles.empty()) {
                        continue;
                    }
                    ObjectStorage::GetInstance()->DeleteObj(Handles.back());
                    Handles.pop_back();
                } else if (Event.key.code == sf::Keyboard::Up) {
                    ObjectStorage::GetInstance()->MoveCam(0, -1);
                } else if (Event.key.code == sf::Keyboard::Down) {
                    ObjectStorage::GetInstance()->MoveCam(0, 1);
                } else if (Event.key.code == sf::Keyboard::Left) {
                    ObjectStorage::GetInstance()->MoveCam(-1, 0);
                } else if (Event.key.code == sf::Keyboard::Right) {
                    ObjectStorage::GetInstance()->MoveCam(1, 0);
                }
            }
        }
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

void WindowHandler::Draw(size_t ObjHandle) {
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
