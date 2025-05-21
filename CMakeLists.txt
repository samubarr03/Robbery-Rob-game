cmake_minimum_required(VERSION 3.28)
project(RobberyRob LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
    GIT_SHALLOW ON
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

# TAPPA 01
add_executable(Tappa01
    Tappa01/main.cpp
    Tappa01/Game/game.cpp
    Tappa01/Matrix/matrix.cpp
    Tappa01/Player/player.cpp
    Tappa01/Utils/utils.cpp
)
target_link_libraries(Tappa01 PRIVATE SFML::Graphics)

target_include_directories(Tappa01 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa01/Game
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa01/Matrix
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa01/Player
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa01/Utils
)


add_custom_command(TARGET Tappa01 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Tappa01>/resources)
