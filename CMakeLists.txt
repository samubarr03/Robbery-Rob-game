cmake_minimum_required(VERSION 3.10)
project(RobberyRob)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# File sorgenti
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE GAME_SRC src/Game/*.cpp)
file(GLOB_RECURSE MATRIX_SRC src/Matrix/*.cpp)
file(GLOB_RECURSE PLAYER_SRC src/Player/*.cpp)

# Cartella eseguibile
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Creo l' eseguibile
add_executable(robbery-rob
    ${SOURCES}
    ${GAME_SRC}
    ${MATRIX_SRC}
    ${PLAYER_SRC}
)

# Link a SFML
target_link_libraries(robbery-rob sfml-graphics sfml-window sfml-system)

# Aggiungo gli header
target_include_directories(robbery-rob
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src/Game
    ${CMAKE_SOURCE_DIR}/src/Matrix
    ${CMAKE_SOURCE_DIR}/src/Player
)
