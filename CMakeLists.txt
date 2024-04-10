cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(CMakeSFMLProject
    src/main.cpp src/debug.hpp
    src/Game.hpp src/Game.cpp
    src/Board.hpp src/Board.cpp src/Piece.cpp
    src/Cell.hpp src/Move.hpp
    src/pieces/Pawn.hpp src/pieces/Pawn.cpp
    src/pieces/Tower.hpp src/pieces/Tower.cpp
    src/pieces/Knight.hpp src/pieces/Knight.cpp
    src/pieces/Bishop.hpp src/pieces/Bishop.cpp
    src/pieces/Queen.hpp src/pieces/Queen.cpp
    src/pieces/King.hpp src/pieces/King.cpp
)
target_link_libraries(CMakeSFMLProject PRIVATE sfml-graphics)
target_compile_features(CMakeSFMLProject PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET CMakeSFMLProject
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:CMakeSFMLProject>
        VERBATIM)
endif()

install(TARGETS CMakeSFMLProject)
