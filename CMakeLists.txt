CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(main)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main sfml-graphics sfml-graphics sfml-window sfml-system)