cmake_minimum_required(VERSION 3.15)
project(My3DGame)

add_executable(My3DGame
    src/main.cpp
    # Add your game source files here
)

target_include_directories(My3DGame
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../engine/include
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include          #Game Headers   
)

target_link_libraries(My3DGame PRIVATE Engine)

### cmake -DCMAKE_BUILD_TYPE=Debug .

### export MYRPG_ROOT=/home/cameron/My3DGame

### export MYRPG_ROOT="/Users/cameronprzybylski/Documents/C++/C++ Projects/My3DGame"
### echo $MYRPG_ROOT