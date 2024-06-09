cmake_minimum_required(VERSION 3.16)
project(chess-bit LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

include_directories(include)

add_executable(chess-bit
    src/main.cpp
    src/Game.cpp
    src/ResourceManager.cpp
    src/Board.cpp
    src/Piece.cpp
    src/Tile.cpp
    src/pieces/Pawn.cpp
    src/pieces/Tower.cpp
    src/pieces/Knight.cpp
    src/pieces/Bishop.cpp
    src/pieces/Queen.cpp
    src/pieces/King.cpp
)
target_link_libraries(chess-bit PRIVATE sfml-graphics)
target_compile_features(chess-bit PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET chess-bit
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:chess-bit>
        VERBATIM)
endif()

install(TARGETS chess-bit)
