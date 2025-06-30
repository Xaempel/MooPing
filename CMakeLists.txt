cmake_minimum_required(VERSION 3.20)
project(MooPing)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/config_boost-asio.cmake)
include(cmake/path.cmake)

add_executable(${PROJECT_NAME} ${HPP_PATH} ${CPP_PATH}) 

config_boost_asio(${PROJECT_NAME})