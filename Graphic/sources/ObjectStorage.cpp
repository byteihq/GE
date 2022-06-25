// Copyright 2022 byteihq <kotov038@gmail.com>

#include <ObjectStorage.h>

ObjectStorage *ObjectStorage::GetInstance() {
    static ObjectStorage objectStorage;
    return &objectStorage;
}

int ObjectStorage::CreateNewObject(uint16_t Count, CoordinateType XMin, CoordinateType XMax, CoordinateType YMin,
                                   CoordinateType YMax) {
    Storage.emplace_back(new Object(Count, XMin, XMax, YMin, YMax));
    return Storage.size() - 1;
}

int ObjectStorage::MoveObj(int Handle, CoordinateType XShift, CoordinateType YShift) {
    if (Storage.size() <= Handle || !Storage[Handle]) {
        return -1; // wrong Handle
    }
    Storage[Handle]->Move(XShift, YShift);
    return 0;
}

std::pair<bool, Object *const> ObjectStorage::GetObject(int Handle) {
    if (Storage.size() <= Handle || !Storage[Handle]) {
        return {false, nullptr}; // wrong Handle
    }
    return {true, Storage[Handle].get()};
}
