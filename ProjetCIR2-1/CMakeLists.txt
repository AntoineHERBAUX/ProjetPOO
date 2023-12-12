cmake_minimum_required(VERSION 3.26)
project(ProjetCIR2_1)

set(CMAKE_CXX_STANDARD 17)
include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG master  # Utilisez la version ou le tag souhaité
)

FetchContent_MakeAvailable(raylib)

add_executable(ProjetCIR2_1 main.cpp
        main.hpp
        station.cpp
        rame.cpp
        affichage.cpp
        vector.cpp
        supervisor.cpp)
target_link_libraries(ProjetCIR2_1 raylib)
