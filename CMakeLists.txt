cmake_minimum_required(VERSION 3.12)
project(SDL_Framework)

# Find the SDL2 package
find_package(SDL2 REQUIRED)

# Add source files
set(SOURCES
    src/main.cpp
    src/vector2D.cpp
    src/utilities.cpp src/timer.cpp
    src/graphics/color.cpp src/graphics/screenbuffer.cpp src/graphics/screen.cpp
    src/shapes/line2D.cpp src/shapes/shape.cpp src/shapes/triangle.cpp src/shapes/rectangle.cpp
    src/shapes/circle.cpp
)

# Add header files
set(HEADERS
    header/vector2D.h
    header/utilities.h header/timer.h
    header/graphics/color.h header/graphics/screenbuffer.h header/graphics/screen.h
    header/constants.h
    header/shapes/line2D.h header/shapes/shape.h header/shapes/triangle.h header/shapes/rectangle.h
    header/shapes/circle.h
)

# Include directories
include_directories(header)
include_directories(header/graphics)
include_directories(header/shapes)

# Create an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

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
