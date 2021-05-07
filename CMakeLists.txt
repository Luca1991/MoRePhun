cmake_minimum_required(VERSION 3.18)

project(MoRePhun)

set(CMAKE_CXX_STANDARD 14)
set(SDL2_DIR "SDL2/")

find_package(SDL2 REQUIRED)
include_directories(MoRePhun ${SDL2_INCLUDE_DIRS})

# MoRePhun
file(GLOB_RECURSE MOREPHUN_SOURCES MoRePhun/*.cpp)
file(GLOB_RECURSE MOREPHUN_HEADERS MoRePhun/*.h)

set(SOURCES
    ${MOREPHUN_SOURCES}
)

SET(HEADERS
    ${MOREPHUN_HEADERS}
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})