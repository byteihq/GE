// Copyright 2022 byteihq <kotov038@gmail.com>

#include <Object.h>
#include <random>
#include <cmath>

Object::Object(uint16_t Count, CoordinateType XMin, CoordinateType XMax, CoordinateType YMin, CoordinateType YMax) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> x_dist(XMin, XMax);
    std::uniform_int_distribution<std::mt19937::result_type> y_dist(YMin, YMax);
    for (size_t i = 0; i < Count; ++i) {
        ObjCoordinates.emplace_back(static_cast<CoordinateType>(x_dist(rng)), static_cast<CoordinateType>(y_dist(rng)));
    }
    std::uniform_int_distribution<std::mt19937::result_type> r_dist(0, 1);
    ObjRelations.resize(Count);
    for (size_t i = 0; i < Count; ++i) {
        ObjRelations[i].resize(Count);
    }

    for (size_t i = 0; i < Count; ++i) {
        for (size_t j = 0; j <= i; ++j) {
            if (i == j) {
                ObjRelations[i][j] = false;
                continue;
            }
            ObjRelations[i][j] = static_cast<bool>(r_dist(rng));
            ObjRelations[j][i] = ObjRelations[i][j];
        }
    }
    CalculateDrawable();
}

std::tuple<float, float, CoordinateType, CoordinateType>
Object::CalculateLine(CoordinateType X1, CoordinateType Y1, CoordinateType X2, CoordinateType Y2) {
    float size = std::sqrt(std::pow(X1 - X2, 2) + std::pow(Y1 - Y2, 2));
    float angle = std::asin((std::abs(Y1 - Y2)) / size) * 180 / M_PI;
    if ((X1 <= X2 && Y1 <= Y2) || (X1 >= X2 && Y1 >= Y2)) {
        return {size, angle, std::min(X1, X2), std::min(Y1, Y2)};
    }
    return {size, 180 - angle, std::max(X1, X2), std::min(Y1, Y2)};
}

void Object::CalculateDrawable() {
    ObjDrawable.clear();
    for (const auto &Coordinate: ObjCoordinates) {
        ObjDrawable.emplace_back(new sf::CircleShape(POINT_SIZE));
        ObjDrawable.back()->setPosition(Coordinate.X, Coordinate.Y);
        ObjDrawable.back()->setOrigin(reinterpret_cast<sf::CircleShape *>(ObjDrawable.back().get())->getRadius(),
                                      reinterpret_cast<sf::CircleShape *>(ObjDrawable.back().get())->getRadius());
        ObjDrawable.back()->setFillColor(sf::Color::White);
    }
    for (size_t i = 0; i < ObjRelations.size(); ++i) {
        for (size_t j = 0; j < i; ++j) {
            if (ObjRelations[i][j]) {
                auto[size, angle, X, Y] = CalculateLine(ObjCoordinates[i].X, ObjCoordinates[i].Y, ObjCoordinates[j].X,
                                                        ObjCoordinates[j].Y);
                ObjDrawable.emplace_back(new sf::RectangleShape(sf::Vector2f(size, LINE_SIZE)));
                ObjDrawable.back()->rotate(angle);
                ObjDrawable.back()->setPosition(X, Y);
                ObjCoordinates.emplace_back(X, Y);
                if (LineIndex == 0) {
                    LineIndex = ObjCoordinates.size() - 1;
                }
            }
        }
    }
}

void Object::Move(CoordinateType XShift, CoordinateType YShift) {
    for (size_t i = 0; i < ObjCoordinates.size(); ++i) {
#ifdef _FLOAT_COORDINATES
        ObjCoordinates[i].X = std::fmod(ObjCoordinates[i].X + XShift, WINDOW_WIDTH);
        ObjCoordinates[i].Y = std::fmod(ObjCoordinates[i].Y + YShift, WINDOW_HEIGHT);
#else
        ObjCoordinates[i].X = (ObjCoordinates[i].X + XShift) % WINDOW_WIDTH;
        ObjCoordinates[i].Y = (ObjCoordinates[i].Y + YShift) % WINDOW_HEIGHT;
#endif
        if (ObjCoordinates[i].X < 0) {
            ObjCoordinates[i].X = WINDOW_WIDTH + ObjCoordinates[i].X;
        }
        if (ObjCoordinates[i].Y < 0) {
            ObjCoordinates[i].Y = WINDOW_HEIGHT + ObjCoordinates[i].Y;
        }
        ObjDrawable[i]->setPosition(ObjCoordinates[i].X, ObjCoordinates[i].Y);
    }
}

void Object::RotateRPoint(CoordinateType X, CoordinateType Y, float Angle) {
    float rAngle = 0;
    float r = 0;
    CoordinateType xDist = 0;
    CoordinateType yDist = 0;
    for (size_t i = 0; i < LineIndex; ++i) {
        xDist = std::abs(ObjCoordinates[i].X - X);
        yDist = std::abs(ObjCoordinates[i].Y - Y);
        auto quarter = Coordinates::GetQuarter(ObjCoordinates[i].X, ObjCoordinates[i].Y);
        if (xDist == 0) {
            if (quarter == Coordinates::Quarter::RU) {
                rAngle = M_PI_2;
            } else {
                rAngle = 1.5 * M_PI;
            }
        } else {
            rAngle = std::atan(yDist / static_cast<float>(xDist));
            if (quarter == Coordinates::Quarter::LU) {
                rAngle = M_PI - rAngle;
            } else if (quarter == Coordinates::Quarter::LB) {
                rAngle += M_PI;
            } else if (quarter == Coordinates::Quarter::RB) {
                rAngle = 2 * M_PI - rAngle;
            }
        }
        rAngle += Angle * M_PI / 180;
        r = std::sqrt(std::pow(xDist, 2) + std::pow(yDist, 2));
        ObjCoordinates[i].X = r * std::cos(rAngle) + X;
        ObjCoordinates[i].Y = -1 * r * std::sin(rAngle) + Y;
    }
    ObjCoordinates.erase(ObjCoordinates.begin() + LineIndex, ObjCoordinates.end());
    LineIndex = 0;
    CalculateDrawable();
}

const Object::DrawableStorage &Object::GetDrawable() const {
    return ObjDrawable;
}
