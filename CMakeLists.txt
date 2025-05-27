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


# TAPPA 02
add_executable(Tappa02
    Tappa02/main.cpp
    Tappa02/Game/game.cpp
    Tappa02/Matrix/matrix.cpp
    Tappa02/Player/player.cpp
    Tappa02/Utils/utils.cpp
)
target_link_libraries(Tappa02 PRIVATE SFML::Graphics)

target_include_directories(Tappa02 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa02/Game
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa02/Matrix
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa02/Player
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa02/Utils
)

add_custom_command(TARGET Tappa02 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Tappa02>/resources)

# TAPPA 03
add_executable(Tappa03
    Tappa03/main.cpp
    Tappa03/Game/game.cpp
    Tappa03/Matrix/matrix.cpp
    Tappa03/Player/player.cpp
    Tappa03/Utils/utils.cpp
    Tappa03/Guard/guard.cpp
)
target_link_libraries(Tappa03 PRIVATE SFML::Graphics)

target_include_directories(Tappa03 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa03/Game
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa03/Matrix
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa03/Player
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa03/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa03/Guard
)

add_custom_command(TARGET Tappa03 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Tappa03>/resources)

# TAPPA 04
add_executable(Tappa04
    Tappa04/main.cpp
    Tappa04/Game/game.cpp
    Tappa04/Matrix/matrix.cpp
    Tappa04/Player/player.cpp
    Tappa04/Utils/utils.cpp
    Tappa04/Guard/guard.cpp
)
target_link_libraries(Tappa04 PRIVATE SFML::Graphics)

target_include_directories(Tappa04 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa04/Game
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa04/Matrix
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa04/Player
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa04/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa04/Guard
)

add_custom_command(TARGET Tappa04 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Tappa04>/resources)




# TAPPA 05
add_executable(Tappa05
    Tappa05/main.cpp
    Tappa05/Game/game.cpp
    Tappa05/Matrix/matrix.cpp
    Tappa05/Player/player.cpp
    Tappa05/Utils/utils.cpp
    Tappa05/Guard/guard.cpp
)
target_link_libraries(Tappa05 PRIVATE SFML::Graphics)

target_include_directories(Tappa05 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa05/Game
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa05/Matrix
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa05/Player
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa05/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa05/Guard
)

add_custom_command(TARGET Tappa05 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Tappa05>/resources)




# TAPPA 06
add_executable(Tappa06
    Tappa06/main.cpp
    Tappa06/Game/game.cpp
    Tappa06/Matrix/matrix.cpp
    Tappa06/Player/player.cpp
    Tappa06/Utils/utils.cpp
    Tappa06/Guard/guard.cpp
)
target_link_libraries(Tappa06 PRIVATE SFML::Graphics)

target_include_directories(Tappa06 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa06/Game
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa06/Matrix
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa06/Player
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa06/Utils
    ${CMAKE_CURRENT_SOURCE_DIR}/Tappa06/Guard
)

add_custom_command(TARGET Tappa06 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:Tappa06>/resources)



