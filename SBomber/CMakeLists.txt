cmake_minimum_required(VERSION 3.5)

project(SBomber VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE)
set(HEADER)

list(APPEND HEADER)




list(APPEND SOURCE
        )



file(GLOB SOURCES "src/*.cpp")

include_directories(include)

set(all_code_files
        ${HEADER}
        ${SOURCE})

add_executable(${PROJECT_NAME} ${all_code_files} ${SOURCES})