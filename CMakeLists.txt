cmake_minimum_required(VERSION 3.10)
project(first)

set(CMAKE_CXX_STANDARD 23)

# 1) Сначала собираем список исходников из app/ и вложенных каталогов
file(GLOB_RECURSE CORE_SOURCES
        "${CMAKE_SOURCE_DIR}/app/*.cpp"
)

# 2) Создаём библиотеку 'core' из найденных исходников
add_library(core ${CORE_SOURCES})

# Укажем путь к заголовкам
include_directories(.)

# Укажем путь к библиотекам
link_directories(.)

# 3) Только после того, как 'core' добавлен, настраиваем его include-директории
#    (чтобы #include "App.h" и другие заголовки из app/ находились)
target_include_directories(core
        PUBLIC
        ${CMAKE_SOURCE_DIR}/app
)

# 4) Создаём исполняемый файл 'app'
add_executable(app
        main.cpp
        gl.c
)

# 5) Линкуем с библиотекой 'core' и системными (GLFW, OpenGL и т. д.)
target_link_libraries(app
        PRIVATE
        core
        glfw3dll
        opengl32
        gdi32
)
