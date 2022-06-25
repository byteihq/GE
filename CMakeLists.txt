# Copyright 2022 byteihq <kotov038@gmail.com>

cmake_minimum_required(VERSION 3.22)

include("cmake/HunterGate.cmake")

HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.314.tar.gz"
        SHA1 "95c47c92f68edb091b5d6d18924baabe02a6962a"
)

project(GraphicEngine)

set(CMAKE_CXX_STANDARD 17)
#add_definitions(-D_FLOAT_COORDINATES)

add_library(Graphic STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphic/sources/WindowHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphic/sources/Object.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Graphic/sources/ObjectStorage.cpp
        )

target_include_directories(Graphic PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Graphic/include>
        $<INSTALL_INTERFACE:include>
        )

target_link_libraries(Graphic PRIVATE sfml-system sfml-window sfml-graphics)

add_executable(${PROJECT_NAME} demo/main.cpp)
target_link_libraries(${PROJECT_NAME} Graphic)
