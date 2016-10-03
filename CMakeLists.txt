cmake_minimum_required(VERSION 2.6)
project(projet_ia_moteur)

add_executable(projet_ia_moteur main.cpp)
add_definitions(-std=c++11)

install(TARGETS projet_ia_moteur RUNTIME DESTINATION bin)
