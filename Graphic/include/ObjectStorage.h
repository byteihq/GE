// Copyright 2022 byteihq <kotov038@gmail.com>

#ifndef GRAPHICENGINE_OBJECTSTORAGE_H
#define GRAPHICENGINE_OBJECTSTORAGE_H

#include <Object.h>
#include <vector>
#include <memory>

class ObjectStorage {
private:
    std::vector<std::unique_ptr<Object>> Storage;
    std::vector<size_t> EmptyCells;
private:
    ObjectStorage() = default;

public:
    ObjectStorage(const ObjectStorage &) = delete;

    ObjectStorage &operator=(const ObjectStorage &) = delete;

    size_t CreateNewObject(uint16_t Count, CoordinateType XMin, CoordinateType XMax, CoordinateType YMin, CoordinateType YMax);

    int MoveObj(size_t Handle, CoordinateType XShift, CoordinateType YShift);

    void MoveCam(CoordinateType XShift, CoordinateType YShift);

    void RotateCam(float Angle);

    int DeleteObj(size_t Handle);

    std::pair<int, Object *const> GetObject(size_t Handle);

    static ObjectStorage *GetInstance();
};

#endif //GRAPHICENGINE_OBJECTSTORAGE_H
