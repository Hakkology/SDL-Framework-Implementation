cmake_minimum_required(VERSION 3.12)
project(SDL_Framework)

# Find the SDL2 package
find_package(SDL2 REQUIRED)

# Add source files
set(SOURCES
    src/main.cpp
    src/shapes/vector2D.cpp src/utils/utilities.cpp src/utils/filecommandloader.cpp
    src/graphics/color.cpp src/graphics/screenbuffer.cpp src/graphics/screen.cpp src/graphics/bmpimage.cpp src/graphics/spritesheet.cpp src/graphics/bmpfont.cpp
    src/graphics/animation.cpp src/graphics/animationplayer.cpp src/graphics/animatedsprite.cpp
    src/shapes/line2D.cpp src/shapes/shape.cpp src/shapes/triangle.cpp src/shapes/rectangle.cpp src/shapes/circle.cpp
    src/app/app.cpp src/app/button.cpp src/scenes/buttonoptionsScene.cpp src/scenes/notimplementedScene.cpp
    src/scenes/arcadeScene.cpp src/scenes/gameScene.cpp
    src/input/gamecontroller.cpp src/input/inputcontroller.cpp
    src/games/breakout/breakout.cpp src/games/breakout/excluder.cpp 
    src/games/breakout/paddle.cpp src/games/breakout/ball.cpp src/games/breakout/levelboundary.cpp
    src/games/breakout/block.cpp src/games/breakout/bgamelevel.cpp

)

# Add header files
set(HEADERS
    header/shapes/vector2D.h header/utils/utilities.h header/utils/constants.h header/utils/filecommandloader.h
    header/graphics/color.h header/graphics/screenbuffer.h header/graphics/screen.h header/graphics/bmpimage.h header/graphics/spritesheet.h header/graphics/bmpfont.h
    header/graphics/animation.h header/graphics/animationplayer.h header/graphics/animatedsprite.h
    header/shapes/line2D.h header/shapes/shape.h header/shapes/triangle.h header/shapes/rectangle.h header/shapes/circle.h
    header/app/app.h header/app/button.h header/scenes/buttonoptionsScene.h header/scenes/notimplementedScene.h header/games/game.h 
    header/scenes/scene.h header/scenes/arcadeScene.h header/games/game.h header/scenes/gameScene.h 
    header/input/inputaction.h header/input/gamecontroller.h header/input/inputcontroller.h
    header/games/breakout/breakout.h header/games/breakout/excluder.h header/games/breakout/boundaryedge.h 
    header/games/breakout/paddle.h header/games/breakout/ball.h header/games/breakout/levelboundary.h
    header/games/breakout/block.h header/games/breakout/bgamelevel.h
    )


# Include directories
include_directories(header)
include_directories(header/utils)
include_directories(header/games)
include_directories(header/games/breakout)
include_directories(header/graphics)
include_directories(header/shapes)
include_directories(header/scenes)
include_directories(header/input)
include_directories(header/app)

# Create an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link SDL2 libraries
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

# Post-build task
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/assets
        ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/assets
    COMMENT "Copying Assets folder to build directory"
)
