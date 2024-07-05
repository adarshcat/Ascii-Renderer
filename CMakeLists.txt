cmake_minimum_required(VERSION 3.6.0)
project(AsciiRenderer VERSION 0.1.0 LANGUAGES C)

include_directories(
    src
)


# Enable sanitizers for Debug build type
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=undefined,address")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Wextra -pedantic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")


set(SOURCES
    # source files
    src/main.c

    # primitives
    src/primitives/cube.c

    #renderer
    src/renderer/camera.c
    src/renderer/image.c
    src/renderer/rasterizer.c

    # library files
    src/utils/mathc.c
)

add_executable(AsciiRenderer ${SOURCES})

target_link_libraries(AsciiRenderer m)




set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
