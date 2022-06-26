// Copyright 2022 byteihq <kotov038@gmail.com>

#ifndef GRAPHICENGINE_OBJECT_H
#define GRAPHICENGINE_OBJECT_H

#include <Presets.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdint>
#include <tuple>

class ObjectStorage;

struct Coordinates {
    CoordinateType X = 0;
    CoordinateType Y = 0;

    enum class Quarter {
        LU, // Left Upper
        RU, // Right Upper
        LB, // Left Bottom
        RB // Right Bottom
    };

    explicit Coordinates(CoordinateType NX, CoordinateType NY) : X(NX), Y(NY) {}

    static Quarter GetQuarter(CoordinateType NX, CoordinateType NY) {
        if (NX < WINDOW_WIDTH / 2) {
            if (NY < WINDOW_HEIGHT / 2) {
                return Quarter::LU;
            }
            return Quarter::LB;
        }
        // NX >= WINDOW_WIDTH / 2
        if (NY < WINDOW_HEIGHT / 2) {
            return Quarter::RU;
        }
        return Quarter::RB;
    }
};

class Object {
public:
    friend class ObjectStorage;

private:
    using CoordinatesStorage = std::vector<Coordinates>;
    using RelationsStorage = std::vector<std::vector<bool>>;
    using DrawableStorage = std::vector<std::unique_ptr<sf::Shape>>;
    CoordinatesStorage ObjCoordinates;
    RelationsStorage ObjRelations;
    DrawableStorage ObjDrawable;

private:
    explicit Object(uint16_t Count, CoordinateType XMin, CoordinateType XMax, CoordinateType YMin, CoordinateType YMax);

    void CalculateDrawable();

    std::tuple<float, float, CoordinateType, CoordinateType> CalculateLine(CoordinateType X1, CoordinateType Y1, CoordinateType X2, CoordinateType Y2); // size, angle, X, Y

    void Move(CoordinateType XShift, CoordinateType YShift);

public:
    const DrawableStorage &GetDrawable() const;
};

#endif //GRAPHICENGINE_OBJECT_H
