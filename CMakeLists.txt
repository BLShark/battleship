cmake_minimum_required(VERSION 2.8)
project(battleship)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(GameBoard)

add_executable(${PROJECT_NAME} main.cpp)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};/usr/share/SFML/cmake/Modules/")
find_package(SFML 2 COMPONENTS system window graphics audio REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE ${SFML_LIBRARIES} GameBoard)
target_include_directories(${PROJECT_NAME} PRIVATE ${SFML_INCLUDE_DIR})

