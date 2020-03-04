cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE FILES "*.cpp" "*.h" "*.hpp")
add_library(GameBoard SHARED ${FILES})
