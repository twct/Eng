cmake_minimum_required (VERSION 3.17)

project (eng)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DENABLE_DEBUG_MACRO")

file (COPY "${CMAKE_CURRENT_SOURCE_DIR}/resources" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

include_directories (${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Application.cpp
    src/AssetLoader.cpp
    src/AtlasReader.cpp
    src/Camera.cpp
    src/Character.cpp
    src/Clock.cpp
    src/Collider.cpp
    src/Drawable.cpp
    src/GameWorld.cpp
    src/Log.cpp
    src/Player.cpp
    src/Renderer.cpp
    src/RNG.cpp
    src/Sprite.cpp
    src/TileMap.cpp
    src/Vector2f.cpp
    src/Vector2i.cpp
    src/World.cpp
)

if (EMSCRIPTEN)
    message ("Building for emscripten...")
    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message ("Building emscripten debug build...")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g4 --source-map-base http://localhost:8080/")
    endif ()
    set (CMAKE_EXECUTABLE_SUFFIX ".html")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s TOTAL_MEMORY=512MB --shell-file ${CMAKE_SOURCE_DIR}/emscripten/shell.html -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 --use-preload-plugins --preload-file ./resources ")
else (EMSCRIPTEN)
    message ("Building for desktop...")

    set (LIBS
        SDL2main
        SDL2_image
        SDL2_ttf
        SDL2_mixer
        SDL2       
    )

    if (WIN32)
        set (LIBS
            mingw32
            ${LIBS}
        )
    endif (WIN32)
    target_link_libraries (${PROJECT_NAME}
        ${LIBS}
    )
endif (EMSCRIPTEN)