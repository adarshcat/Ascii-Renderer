cmake_minimum_required(VERSION 3.6.0)
project(AsciiRenderer VERSION 0.1.0 LANGUAGES C)

include_directories(
    src
)

set(SOURCES
    # source files
    src/main.c
    src/primitives/cube.c

    # library files
    src/utils/mathc.c
)


add_executable(AsciiRenderer ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
