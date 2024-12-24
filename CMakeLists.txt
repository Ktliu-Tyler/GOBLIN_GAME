cmake_minimum_required(VERSION 3.29)
project(Goblin_game)

set(CMAKE_CXX_STANDARD 20)

set(SDL2_PATH "SDL_lib/SDL2-2.30.7/x86_64-w64-mingw32")
set(SDL2_IMAGE_PATH "SDL_lib/SDL2_image-2.8.2/x86_64-w64-mingw32")
set(SDL2_TTF_PATH "SDL_lib/SDL2_ttf-2.22.0/x86_64-w64-mingw32")
set(SDL2_MIXER_PATH "SDL_lib/SDL2_mixer-2.8.0/x86_64-w64-mingw32")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)



include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_PATH}/include ${SDL2_TTF_PATH}/include ${SDL2_MIXER_PATH}/include )

add_executable(Goblin_game main.cpp
        SDL_lib/SDL_bgi.cpp
        src/engine.cpp
        src/tool.cpp
        src/menu.cpp
        src/playground.cpp
        src/Player.cpp
        src/Enemy.cpp
        )

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
if (WIN32)
        set(RESOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/icon.rc)
        target_sources(Goblin_game PRIVATE ${RESOURCE_FILE})
endif()
if (WIN32)
        set(RESOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/record/Gamerecoder.txt)
        target_sources(Goblin_game PRIVATE ${RESOURCE_FILE})
endif()