cmake_minimum_required(VERSION 3.10...3.50)

project(Aaron)

include(FetchContent)

FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/6.0.zip
)

FetchContent_Declare(
    raylib_nuklear
    URL https://github.com/RobLoach/raylib-nuklear/archive/refs/tags/v6.0.1.zip
)

FetchContent_Declare(
    json
    URL https://github.com/nlohmann/json/archive/refs/tags/v3.12.0.zip
)

set(BUILD_EXAMPLES OFF CACHE INTERNAL "")

FetchContent_MakeAvailable(raylib raylib_nuklear json)

set(
SOURCE_FILES

    src/main.cpp
    src/app.cpp
    src/game.cpp
    src/entity_classes/sprite.cpp
    src/entity_classes/player.cpp
    src/entity_classes/tile.cpp
    src/manager_classes/world.cpp
    src/utility/utils.cpp
    src/utility/global_vars.cpp
    src/utility/assets.cpp
    src/utility/data.cpp
    src/ui/ui.cpp
)

add_executable(Aaron ${SOURCE_FILES})
target_link_libraries(Aaron raylib raylib_nuklear nlohmann_json::nlohmann_json)

if(WIN32)

    target_sources(Aaron PRIVATE windows/app.rc)
    target_link_options(Aaron PRIVATE $<$<CONFIG:Release>:-mwindows>)
elseif(APPLE)

    target_link_options(Aaron PRIVATE $<$<CONFIG:Release>:-MACOSX_BUNDLE>)
endif()

target_compile_definitions(Aaron PUBLIC $<$<CONFIG:Debug>:DEBUG_ENABLED>)

message("Operation Complete! Configured Correctly!")

if("${PLATFORM}" STREQUAL "Web")

    message(FATAL_ERROR "Do not build in this project in the Web as it doesn't work!")
endif()

if(APPLE)

    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()