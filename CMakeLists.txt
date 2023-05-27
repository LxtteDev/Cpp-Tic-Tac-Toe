cmake_minimum_required(VERSION 3.0.0)
project(TicTacToe VERSION 0.1.0)

include(FetchContent)
set(BUILD_SHARED_LIBS  OFF)
FetchContent_Declare(
 SFML
 GIT_REPOSITORY https://github.com/SFML/SFML.git
 GIT_TAG 2.5.1
)
FetchContent_MakeAvailable(SFML)

include(CTest)
enable_testing()

file(GLOB source
    "src/**/*.h"
    "src/**/*.cpp"
)

add_executable(TicTacToe src/main.cpp ${source})

if(WIN32)
    set_target_properties(TicTacToe PROPERTIES WIN32_EXECUTABLE true)
endif()

target_link_libraries(TicTacToe sfml-graphics)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
