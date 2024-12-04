cmake_minimum_required(VERSION 3.27)
project(Projectsfml)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projectsfml main.cpp
        game.cpp
        ../Headers/game.h
        entity.cpp
        ../Headers/entity.h
        Regular_Zombie.cpp
        ../Headers/Regular_Zombie.h
        Textures.cpp
        ../Headers/Textures.h
        Animations.cpp
        ../Headers/Animations.h
        GameMap.cpp
        ../Headers/GameMap.h
        PeaShooter.cpp
        ../Headers/PeaShooter.h
        PeaShot.cpp
        ../Headers/PeaShot.h
        Sunflower.cpp
        ../Headers/Sunflower.h
        Wall.cpp
        ../Headers/Wall.h
        Mower.cpp
        ../Headers/Mower.h
        Bucket_Zombie.cpp
        ../Headers/Bucket_Zombie.h
)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)

find_package(SFML COMPONENTS system window graphics network audio REQUIRED)

include_directories(C:/SFML/include/SFML)

target_link_libraries(Projectsfml sfml-graphics sfml-window sfml-system)
