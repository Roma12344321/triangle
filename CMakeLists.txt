cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME first)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE CORE_SOURCES
        "${CMAKE_SOURCE_DIR}/app/*.cpp"
)

add_library(core ${CORE_SOURCES})

include_directories(.)

link_directories(.)

target_include_directories(core
        PUBLIC
        ${CMAKE_SOURCE_DIR}/app
)

add_executable(${PROJECT_NAME}
        main.cpp
        glad/gl.c
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        core
        glfw3dll
        opengl32
        gdi32
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/res"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res"
)

add_custom_command(
        TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/glfw3.dll"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
)
