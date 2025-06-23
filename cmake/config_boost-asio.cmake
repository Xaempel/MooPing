cmake_policy(SET CMP0167 OLD)

function(config_boost_asio PROJECT_NAME)
    find_package(Boost REQUIRED COMPONENTS system thread)

    target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES})
endfunction()