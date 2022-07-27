cmake_minimum_required(VERSION 3.21)
project(main)

set(CMAKE_CXX_STANDARD 20)
add_executable(main main.cpp Object.cpp Object.h Entity.cpp Entity.h Item.cpp Item.h Obstacle.cpp Obstacle.h Skills.cpp Skills.h Boss.cpp Boss.h Mario.cpp Mario.h World.cpp World.h Tile.cpp Tile.h Dungeonarea.cpp Dungeonarea.h  Iceslide.cpp Iceslide.h Fireball.cpp Fireball.h Littlelight.cpp Littlelight.h Dice.cpp Dice.h Utilities.h Hud.cpp Hud.h Animation.cpp Animation.h Teleport.h Teleport.cpp GameFileException.cpp GameFileException.h Spawner.cpp Spawner.h Textviewer.cpp Textviewer.h Loader.cpp Loader.h Menu.cpp Menu.h Safezone.cpp Safezone.h Events.cpp Events.h)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    file(COPY "c:/mingw32/bin/libgcc_s_dw2-1.dll " DESTINATION ${CMAKE_BINARY_DIR})#richiesta per le eccezioni
    file(GLOB MINGW_DEP_DLLS "C:/mingw32/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    set(SFML_DIR c:/SFML/lib/cmake/SFML)
    file(COPY "${SFML_DIR}/../../../bin/openal32.dll " DESTINATION ${CMAKE_BINARY_DIR})
    find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
    if (SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIRS})
        target_link_libraries(main sfml-system sfml-window  sfml-audio sfml-graphics sfml-network )
        file(GLOB BINARY_DEP_DLLS "${SFML_DIR}/../../../bin/*.dll ")
        file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    endif()

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
    if(false)#mettere true solo se cmake non trova sfml in autonomia
        set(SFML_DIR /usr/local/Cellar/sfml)#assicurarsi che sia il percorso dove è presente il file config
    endif()
    find_package(SFML  2.5 COMPONENTS system window graphics network audio REQUIRED)
    if (SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIRS})
        target_link_libraries(main sfml-system sfml-window  sfml-audio sfml-graphics sfml-network)
    endif()
endif()

file(COPY "../assets" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "../playerSave" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "../map" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "../vectors" DESTINATION ${CMAKE_BINARY_DIR})
add_subdirectory(Google_tests)

