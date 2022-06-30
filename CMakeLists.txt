cmake_minimum_required(VERSION 3.21)
project(main)

set(CMAKE_CXX_STANDARD 20)
set(SFML_STATIC_LIBRARIES TRUE)






add_executable(main main.cpp Object.cpp Object.h Entity.cpp Entity.h Item.cpp Item.h Obstacle.cpp Obstacle.h Skills.cpp Skills.h Boss.cpp Boss.h Mario.cpp Mario.h World.cpp World.h Tile.cpp Tile.h Dungeonarea.cpp Dungeonarea.h  Iceslide.cpp Iceslide.h Fireball.cpp Fireball.h Littlelight.cpp Littlelight.h Dice.cpp Dice.h  Template.h Hud.cpp Hud.h Animation.cpp Animation.h Teleport.h Teleport.cpp GameFileException.cpp GameFileException.h Spawner.cpp Spawner.h Textviewer.cpp Textviewer.h Loader.cpp Loader.h)

include_directories( c:/SFML/include)

set(SFML_ROOT c:/SFML)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_module")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(main sfml-graphics sfml-system sfml-window)
endif()
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()