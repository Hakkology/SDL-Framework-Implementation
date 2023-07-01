cmake_minimum_required(VERSION 3.12)
project(SDL_Framework)

# Find the SDL2 package
find_package(SDL2 REQUIRED)

# Add source files
set(SOURCES
    src/main.cpp
    src/vector2D.cpp
    src/utilities.cpp
)

# Add header files
set(HEADERS
    header/constants.h
    header/utilities.h
    header/vector2D.h
)

# Include directories
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(header)

# Create an executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link SDL2 libraries
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Post-build task
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/Assets
        ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Assets
    COMMENT "Copying Assets folder to build directory"
)
