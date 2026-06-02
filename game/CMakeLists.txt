cmake_minimum_required(VERSION 3.15)
project(My3DGame)

add_executable(My3DGame
    src/Cube.cpp
    src/Level.cpp
    src/Player.cpp
    src/main.cpp
    # Add your game source files here
)

target_include_directories(My3DGame
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../engine/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include          #Game Headers   
)

target_link_libraries(My3DGame PRIVATE Engine)

### cmake -DCMAKE_BUILD_TYPE=Debug .

### export My3DGame_ROOT=/home/cameron/My3DGame

### export My3DGame_ROOT="/Users/cameronprzybylski/Documents/C++/C++ Projects/My3DGame"
### echo $My3DGame_ROOT