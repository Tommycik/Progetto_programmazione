project(Google_Tests_run)
add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run  AbsoluteTest.cpp ../Object.cpp ../Object.h ../Entity.cpp ../Entity.h ../Item.cpp ../Item.h ../Obstacle.cpp ../Obstacle.h ../Skills.cpp ../Skills.h ../Boss.cpp ../Boss.h ../Mario.cpp ../Mario.h ../World.cpp ../World.h ../Tile.cpp ../Tile.h ../Dungeonarea.cpp ../Dungeonarea.h  ../Iceslide.cpp ../Iceslide.h ../Fireball.cpp ../Fireball.h ../Littlelight.cpp ../Littlelight.h ../Dice.cpp ../Dice.h ../Utilities.h ../Hud.cpp ../Hud.h ../Animation.cpp ../Animation.h ../Teleport.h ../Teleport.cpp ../GameFileException.cpp ../GameFileException.h ../Spawner.cpp ../Spawner.h ../Textviewer.cpp ../Textviewer.h ../Loader.cpp ../Loader.h ../Menu.cpp ../Menu.h ../Safezone.cpp ../Safezone.h ../Events.cpp ../Events.h TestSetting.cpp TestSetting.h)

if(WIN32)
    set(SFML_STATIC_LIBRARIES TRUE)
    file(COPY "c:/mingw32/bin/libgcc_s_dw2-1.dll " DESTINATION "${CMAKE_BINARY_DIR}/Google_tests/")#richiesta per le eccezioni
    file(GLOB MINGW_DEP_DLLS "C:/mingw32/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION "${CMAKE_BINARY_DIR}/Google_tests/")
    set(SFML_DIR c:/SFML/lib/cmake/SFML)
    file(COPY "${SFML_DIR}/../../../bin/openal32.dll " DESTINATION "${CMAKE_BINARY_DIR}/Google_tests/")
    find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
    if (SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIRS})
        target_link_libraries(Google_Tests_run sfml-system sfml-window  sfml-audio sfml-graphics sfml-network )
        file(GLOB BINARY_DEP_DLLS "${SFML_DIR}/../../../bin/*.dll ")
        file(COPY ${BINARY_DEP_DLLS} DESTINATION "${CMAKE_BINARY_DIR}/Google_tests/")
    endif()

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX TRUE)
    if(false)#mettere true solo se cmake non trova sfml in autonomia
        set(SFML_DIR /usr/local/Cellar/sfml)#assicurarsi che sia il percorso dove è presente il file config
    endif()
    find_package(SFML  2.5 COMPONENTS system window graphics network audio REQUIRED)
    if (SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIRS})
        target_link_libraries(Google_Tests_run sfml-system sfml-window  sfml-audio sfml-graphics sfml-network)
    endif()
endif()


file(COPY "../../assets" DESTINATION "${CMAKE_BINARY_DIR}/Google_tests/")
file(COPY "../../playerSave" DESTINATION "${CMAKE_BINARY_DIR}/Google_tests/")
file(COPY "../../map" DESTINATION "${CMAKE_BINARY_DIR}/Google_tests/")
file(COPY "../../vectors" DESTINATION "${CMAKE_BINARY_DIR}/Google_tests/")
target_link_libraries(Google_Tests_run gtest gtest_main)