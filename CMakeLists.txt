cmake_minimum_required(VERSION 3.25.0)

cmake_policy(SET CMP0048 NEW)

project(my_playback
        VERSION 0.1
        DESCRIPTION "My Playback"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/playback PLAYBACK_SRC)

add_executable(${PROJECT_NAME}
        main.cpp
        ${PLAYBACK_SRC}
        plugin/example_plugin.h
        platform/asd.h
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/playback
        ${CMAKE_CURRENT_SOURCE_DIR}/reaction/include
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/${CMAKE_BUILD_TYPE}/bin)