// Copyright 2022 byteihq <kotov038@gmail.com>

#ifndef GRAPHICENGINE_PRESETS_H
#define GRAPHICENGINE_PRESETS_H

#define POINT_SIZE 6
#define LINE_SIZE 3
#define FRAME_LIMIT 60

#ifdef _FLOAT_COORDINATES
using CoordinateType = float;
#define WINDOW_WIDTH 800.f
#define WINDOW_HEIGHT 600.f
#else
using CoordinateType = int;
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 800
#endif

#endif //GRAPHICENGINE_PRESETS_H
