cmake_minimum_required(VERSION 3.30)
project(Test)

set(CMAKE_CXX_STANDARD 20)
find_package(raylib REQUIRED)
include_directories(${RAYLIB_INCLUDE_DIRS})

add_executable(Test src/main.cpp
        include/Structures.h
        src/Structures.cpp
        src/EntityManager.cpp
        include/EntityManager.h
        src/Entity.cpp
        include/Entity.h
        src/Astronaut.cpp
        include/Astronaut.h
        src/DynamicCamera.cpp
        include/DynamicCamera.h
        src/Gun.cpp
        include/Gun.h
        src/Wall.cpp
        include/Wall.h
        src/Bullet.cpp
        include/Bullet.h
        src/SpatialGrid.cpp
        include/SpatialGrid.h)

target_link_libraries(Test raylib)