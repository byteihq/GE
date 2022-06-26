// Copyright 2022 byteihq <kotov038@gmail.com>

#include <ObjectStorage.h>

ObjectStorage *ObjectStorage::GetInstance() {
    static ObjectStorage objectStorage;
    return &objectStorage;
}

size_t ObjectStorage::CreateNewObject(uint16_t Count, CoordinateType XMin, CoordinateType XMax, CoordinateType YMin,
                                   CoordinateType YMax) {
    if (!EmptyCells.empty()) {
        size_t handle = EmptyCells.back();
        Storage[handle].reset(new Object(Count, XMin, XMax, YMin, YMax));
        EmptyCells.pop_back();
        return handle;
    }
    Storage.emplace_back(new Object(Count, XMin, XMax, YMin, YMax));
    return Storage.size() - 1;
}

int ObjectStorage::MoveObj(size_t Handle, CoordinateType XShift, CoordinateType YShift) {
    if (Storage.size() <= Handle || !Storage[Handle]) {
        return -1; // wrong Handle
    }
    Storage[Handle]->Move(XShift, YShift);
    return 0;
}

void ObjectStorage::MoveCam(CoordinateType XShift, CoordinateType YShift) {
    for (const auto &Obj: Storage) {
        if (Obj) {
            Obj->Move(-1 * XShift, -1 * YShift);
        }
    }
}

int ObjectStorage::DeleteObj(size_t Handle) {
    if (Storage.size() <= Handle || !Storage[Handle]) {
        return -1; // wrong Handle
    }
    Storage[Handle].reset();
    EmptyCells.push_back(Handle);
    return 0;
}

std::pair<int, Object *const> ObjectStorage::GetObject(size_t Handle) {
    if (Storage.size() <= Handle || !Storage[Handle]) {
        return {0, nullptr}; // wrong Handle
    }
    return {1, Storage[Handle].get()};
}
