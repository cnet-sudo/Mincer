cmake_minimum_required(VERSION 3.21)
project(Mincer VERSION 0.0.1 LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)


add_executable(Mincer main.cpp GameEngine.cpp GameEngine.h AssetManager.cpp AssetManager.h GameSound.cpp GameSound.h
GameText.cpp GameText.h Levels.cpp Levels.h Bullet.cpp Bullet.h Animator.cpp Animator.h Monster.cpp Monster.h
MonsterPlanet.cpp MonsterPlanet.h Pickup.cpp Pickup.h Player.cpp Player.h )

add_custom_command(TARGET Mincer POST_BUILD                
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy_directory
                        ${PROJECT_SOURCE_DIR}/sound
                        $<TARGET_FILE_DIR:Mincer>/sound
                   VERBATIM)
add_custom_command(TARGET Mincer POST_BUILD                
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy_directory
                        ${PROJECT_SOURCE_DIR}/fonts
                        $<TARGET_FILE_DIR:Mincer>/fonts
                   VERBATIM)
add_custom_command(TARGET Mincer POST_BUILD                
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy_directory
                        ${PROJECT_SOURCE_DIR}/graphics
                        $<TARGET_FILE_DIR:Mincer>/graphics
                   VERBATIM)
add_custom_command(TARGET Mincer POST_BUILD                
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy_directory
                        ${PROJECT_SOURCE_DIR}/gamedata
                        $<TARGET_FILE_DIR:Mincer>/gamedata
                   VERBATIM)				   
add_custom_command(
  TARGET Mincer POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy 
    ${PROJECT_SOURCE_DIR}/openal32.dll
    $<TARGET_FILE_DIR:Mincer>/openal32.dll)

target_link_libraries(Mincer PRIVATE sfml-graphics sfml-system sfml-window sfml-audio )

target_compile_features(Mincer PRIVATE cxx_std_14)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Mincer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Mincer> $<TARGET_FILE_DIR:Mincer> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Mincer)

# Директория с СMakeLists.txt
# cmake -S . -B build
# cmake --build build --config Release
# cmake --build build --config Debug
# Для запуска проекта выбрать активный проект