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
                double distance = std::sqrt(
                        std::pow(ObjCoordinates[i].X - ObjCoordinates[j].X, 2) +
                        std::pow(ObjCoordinates[i].Y - ObjCoordinates[j].Y, 2)
                );
                ObjDrawable.emplace_back(new sf::RectangleShape(sf::Vector2f(distance, LINE_SIZE)));
                double sin_angle =
                        static_cast<double>(std::abs(ObjCoordinates[i].Y - ObjCoordinates[j].Y)) / distance;
                double angle = std::asin(sin_angle) * 180 / M_PI;
                if ((ObjCoordinates[i].X <= ObjCoordinates[j].X &&
                     ObjCoordinates[i].Y <= ObjCoordinates[j].Y) ||
                    (ObjCoordinates[i].X >= ObjCoordinates[j].X &&
                     ObjCoordinates[i].Y >= ObjCoordinates[j].Y)) {
                    ObjDrawable.back()->setPosition(std::min(ObjCoordinates[i].X, ObjCoordinates[j].X),
                                                    std::min(ObjCoordinates[i].Y, ObjCoordinates[j].Y));
                    ObjDrawable.back()->rotate(angle);
                } else {
                    ObjDrawable.back()->setPosition(std::max(ObjCoordinates[i].X, ObjCoordinates[j].X),
                                                    std::min(ObjCoordinates[i].Y, ObjCoordinates[j].Y));
                    ObjDrawable.back()->rotate(180 - angle);
                }
                ObjCoordinates.emplace_back(static_cast<CoordinateType>(ObjDrawable.back()->getPosition().x),
                                            static_cast<CoordinateType>(ObjDrawable.back()->getPosition().y));
            }
        }
    }
}

void Object::Move(CoordinateType XShift, CoordinateType YShift) {
    for (size_t i = 0; i < ObjCoordinates.size(); ++i) {
#ifdef _FLOAT_COORDINATES
        ObjCoordinates[i].X = std::fmod(ObjCoordinates[i].X + XShift, WINDOW_WIDTH);
        ObjCoordinates[i].Y = std::fmod(ObjCoordinates[i].X + YShift, WINDOW_HEIGHT);
#else
        ObjCoordinates[i].X = (ObjCoordinates[i].X + XShift) % WINDOW_WIDTH;
        ObjCoordinates[i].Y = (ObjCoordinates[i].Y + YShift) % WINDOW_HEIGHT;
#endif
        ObjDrawable[i]->setPosition(ObjCoordinates[i].X, ObjCoordinates[i].Y);
    }
}

const Object::DrawableStorage &Object::GetDrawable() const {
    return ObjDrawable;
}
