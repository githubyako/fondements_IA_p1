cmake_minimum_required(VERSION 2.6)
project(projet_ia_moteur)

add_executable(projet_ia_moteur rule.cpp main.cpp)
add_definitions(-std=c++1y)

install(TARGETS projet_ia_moteur RUNTIME DESTINATION bin)
