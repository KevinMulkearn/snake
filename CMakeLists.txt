cmake_minimum_required (VERSION 3.0.0)

project(snake)

find_package(Threads REQUIRED)

include_directories(include)

file(GLOB SRCS "src/*.cpp")

add_executable(snake ${SRCS})

target_link_libraries(snake
    PUBLIC
    Threads::Threads)
