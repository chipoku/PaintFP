cmake_minimum_required(VERSION 3.16)
project(PaintFP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${PROJECT_SOURCE_DIR}/bin)
set(PROJECT_SRC_FILES
        ${PROJECT_SOURCE_DIR}/src/main.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SRC_FILES})

target_link_libraries(${PROJECT_NAME}
                        ncurses)