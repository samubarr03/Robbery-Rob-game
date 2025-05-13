cmake_minimum_required(VERSION 3.10)
project(RobberyRob)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# File sorgente
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Output nella cartella bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Aggiungo eseguibile
add_executable(robbery-rob ${SOURCES})

# Link a SFML
target_link_libraries(robbery-rob sfml-graphics sfml-window sfml-system)
