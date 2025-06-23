cmake_minimum_required(VERSION 3.20)
project(MooPing)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/config_boost-asio.cmake)

add_executable(${PROJECT_NAME} src/main.cpp include/tools/drawAppIcon.hpp src/tools/drawAppIcon.cpp) 

config_boost_asio(${PROJECT_NAME})