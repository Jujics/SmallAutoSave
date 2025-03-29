cmake_minimum_required(VERSION 3.30)
project(untitled)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
set(CMAKE_CXX_FLAGS "-static")
set(CMAKE_INSTALL_PREFIX "$ENV{USERPROFILE}/untitled_install" CACHE PATH "Installation prefix" FORCE)

add_executable(untitled main.cpp)

install(TARGETS untitled DESTINATION bin)
