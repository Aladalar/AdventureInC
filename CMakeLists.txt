cmake_minimum_required(VERSION 3.10)
project(AdventureInC)
set(RAYLIB_PATH_WIN ${CMAKE_SOURCE_DIR}/libs/win/raylib)
set(RAYLIB_PATH_LINUX ${CMAKE_SOURCE_DIR}/libs/linux/raylib)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/core/logger.cpp
    src/player/mouseInput.cpp
    src/player/player.cpp
)

if(WIN32)
    target_include_directories(${PROJECT_NAME} PRIVATE 
        include
        ${RAYLIB_PATH_WIN}/include
    )
    target_link_libraries(${PROJECT_NAME} 
        ${RAYLIB_PATH_WIN}/lib/raylib.lib
        winmm
        gdi32
        opengl32
    )
elseif(UNIX)
    target_include_directories(${PROJECT_NAME} PRIVATE 
        include
        ${RAYLIB_PATH_LINUX}/include
    )
    target_link_libraries(${PROJECT_NAME}
        ${RAYLIB_PATH_LINUX}/lib/libraylib.a
        m
        dl
        pthread
    )
endif()