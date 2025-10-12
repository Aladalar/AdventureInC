cmake_minimum_required(VERSION 3.10)
project(AdventureInC)
set(RAYLIB_PATH_WIN ${CMAKE_SOURCE_DIR}/libs/win/raylib)
set(RAYLIB_PATH_LINUX ${CMAKE_SOURCE_DIR}/libs/linux/raylib)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/game.cpp

    src/managers/screenManager.cpp
    src/managers/inputManager.cpp
    src/managers/navigationManager.cpp

    src/utilities/logger.cpp

    src/world/testRegion/scenes/testScene.cpp
    src/world/testRegion/scenes/secondTestScene.cpp
    src/world/testRegion/testRegion.cpp
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets 
    $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
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
        msvcrt      
        ucrt
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