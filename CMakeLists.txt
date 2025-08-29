cmake_minimum_required(VERSION 3.5)
project(Pathfinding CXX)

set(SDL2_PATH "C:/SDL/x86_64-w64-mingw32")
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake-modules)
set(CMAKE_CXX_STANDARD 20)

# 1. Look for a SDL3 package,
# 2. look for the SDL3-shared component, and
# 3. fail if the shared component cannot be found.
find_package(SDL2 REQUIRED SDL2)

include_directories(${SDL2_INCLUDE_DIR})
# SET(CMAKE_CXX_LINK_FLAGS "-lSDL2")
add_executable(Pathfinding WIN32 main.cpp
        game.cpp
        game.hpp
        Util/Logger.cpp
        Util/Logger.hpp
        Map/Grid.cpp
        Map/Grid.hpp
        Map/Tile.hpp
        Algo/PathfindAlgo.hpp
        Algo/Node.hpp
        Algo/Dijkstra.cpp
        Algo/Dijkstra.hpp
        Algo/Dfs.cpp
        Algo/Dfs.hpp
        Algo/AStar.cpp
        Algo/AStar.hpp
        Input/InputHandler.cpp
        Input/InputHandler.hpp
        Input/KeyMap.hpp
        Input/KeyAction.hpp
        Input/KeyMap.cpp
)
target_link_libraries(Pathfinding ${SDL2_LIBRARY})
set_target_properties(Pathfinding PROPERTIES WIN32_EXECUTABLE FALSE)
if(WIN32)
    add_custom_command(
            TARGET Pathfinding POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "${SDL2_PATH}/bin/SDL2.dll"
            "$<TARGET_FILE_DIR:Pathfinding>"
            VERBATIM
    )
endif()
