cmake_minimum_required(VERSION 3.10)

project(wanbeiyu)
set(CMAKE_C_STANDARD 99)

include_directories(include)
add_library(wanbeiyu STATIC
            src/wanbeiyu.c)

add_executable(test test/test.c)
target_link_libraries(test wanbeiyu)