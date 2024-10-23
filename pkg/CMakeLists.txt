#! Put this file in the "pkg" file

# set the cmake min version (current - 3.29.3)
cmake_minimum_required(VERSION 3.29.3)

# set the project/app name
project(app)

# specify the C standard version
set(CMAKE_C_STANDARD 99)

# Add the main window source files
set(SOURCES
  ../project/src/main.c
  ../project/src/lib.c
)

# Add the main window header files
set(HEADERS
  ../project/inc/inc.h
)

# Add the executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# add compiler definitions
add_definitions(-D_DEFAULT_SOURCE)

# add compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

# link libraries
target_link_libraries(${PROJECT_NAME} m SDL SDL_image)