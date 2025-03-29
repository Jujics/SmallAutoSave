cmake_minimum_required(VERSION 3.30)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp)

if (MINGW OR MSYS)
    add_custom_command(TARGET untitled POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${MINGW_PATH}/bin/libgcc_s_seh-1.dll"
            "${MINGW_PATH}/bin/libstdc++-6.dll"
            "${MINGW_PATH}/bin/libwinpthread-1.dll"
            $<TARGET_FILE_DIR:untitled>)
endif()

install(TARGETS untitled DESTINATION bin)
