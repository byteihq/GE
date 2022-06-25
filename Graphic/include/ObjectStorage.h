// Copyright 2022 byteihq <kotov038@gmail.com>

#ifndef GRAPHICENGINE_OBJECTSTORAGE_H
#define GRAPHICENGINE_OBJECTSTORAGE_H

#include <Object.h>
#include <vector>
#include <memory>

class ObjectStorage {
private:
    std::vector<std::unique_ptr<Object>> Storage;

private:
    ObjectStorage() = default;

public:
    ObjectStorage(const ObjectStorage &) = delete;

    ObjectStorage &operator=(const ObjectStorage &) = delete;

    int
    CreateNewObject(uint16_t Count, CoordinateType XMin, CoordinateType XMax, CoordinateType YMin, CoordinateType YMax);

    int MoveObj(int Handle, CoordinateType XShift, CoordinateType YShift);

    std::pair<bool, Object *const> GetObject(int Handle);

    static ObjectStorage *GetInstance();
};

#endif //GRAPHICENGINE_OBJECTSTORAGE_H
