// Copyright 2022 byteihq <kotov038@gmail.com>

#ifndef GRAPHICENGINE_OBJECT_H
#define GRAPHICENGINE_OBJECT_H

#include <Presets.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdint>

class ObjectStorage;

struct Coordinates {
    CoordinateType X;
    CoordinateType Y;

    explicit Coordinates(CoordinateType NX, CoordinateType NY) : X(NX), Y(NY) {}
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

    void Move(CoordinateType XShift, CoordinateType YShift);

public:

    const DrawableStorage &GetDrawable() const;
};

#endif //GRAPHICENGINE_OBJECT_H
