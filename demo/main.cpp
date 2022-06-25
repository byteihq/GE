// Copyright 2022 byteihq <kotov038@gmail.com>

#include <WindowHandler.h>
#include <Presets.h>

int main() {
    WindowHandler w1(WINDOW_WIDTH, WINDOW_HEIGHT, FRAME_LIMIT, "MainWindow");
    w1.Run();
    return 0;
}
