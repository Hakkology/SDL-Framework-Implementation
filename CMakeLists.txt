cmake_minimum_required(VERSION 3.12)
project(SDL_Framework)

# Find the SDL2 package
find_package(SDL2 REQUIRED)

# Add source files
set(SOURCES

    src/main.cpp
    src/shapes/vector2D.cpp 

    # graphics and utility files
    src/utils/utilities.cpp 
    src/utils/filecommandloader.cpp
    src/graphics/color.cpp 
    src/graphics/screenbuffer.cpp 
    src/graphics/screen.cpp 
    src/graphics/bmpimage.cpp 
    src/graphics/spritesheet.cpp 
    src/graphics/bmpfont.cpp
    src/graphics/animation.cpp 
    src/graphics/animationplayer.cpp 
    src/graphics/animatedsprite.cpp

    # shapes files
    src/shapes/line2D.cpp 
    src/shapes/shape.cpp 
    src/shapes/triangle.cpp 
    src/shapes/rectangle.cpp 
    src/shapes/circle.cpp
    
    # app files
    src/app/app.cpp 
    src/app/button.cpp 
    
    # scene files
    src/scenes/buttonoptionsScene.cpp 
    src/scenes/notimplementedScene.cpp
    src/scenes/arcadeScene.cpp 
    src/scenes/gameScene.cpp
    src/scenes/pacmanstartScene.cpp

    # input files
    src/input/gamecontroller.cpp 
    src/input/inputcontroller.cpp

    # breakout files
    src/games/breakout/breakout.cpp 
    src/games//excluder.cpp 
    src/games/breakout/paddle.cpp 
    src/games/breakout/ball.cpp 
    src/games/breakout/levelboundary.cpp
    src/games/breakout/block.cpp 
    src/games/breakout/bgamelevel.cpp

    # pacman files
    src/games/pacman/pacmanlevel.cpp
    src/games/pacman/pacmangameutils.cpp
    src/games/pacman/pacmanactor.cpp 
    src/games/pacman/pacmanplayer.cpp 
    src/games/pacman/pacman.cpp
)

# Add header files
set(HEADERS

    header/shapes/vector2D.h

    # graphics and utility headers
    header/utils/utilities.h 
    header/utils/constants.h 
    header/utils/filecommandloader.h
    header/graphics/color.h 
    header/graphics/screenbuffer.h 
    header/graphics/screen.h 
    header/graphics/bmpimage.h 
    header/graphics/spritesheet.h 
    header/graphics/bmpfont.h
    header/graphics/animation.h 
    header/graphics/animationplayer.h 
    header/graphics/animatedsprite.h

    # shape headers
    header/shapes/line2D.h 
    header/shapes/shape.h 
    header/shapes/triangle.h 
    header/shapes/rectangle.h 
    header/shapes/circle.h

    # app headers
    header/app/app.h 
    header/app/button.h 
    
    # scene headers
    header/scenes/buttonoptionsScene.h 
    header/scenes/notimplementedScene.h 
    header/games/game.h 
    header/scenes/scene.h 
    header/scenes/arcadeScene.h 
    header/scenes/gameScene.h 
    header/scenes/pacmanstartScene.h 

    # input headers
    header/input/inputaction.h 
    header/input/gamecontroller.h 
    header/input/inputcontroller.h

    # breakout game headers
    header/games/breakout/breakout.h 
    header/games/excluder.h 
    header/games/breakout/boundaryedge.h 
    header/games/breakout/paddle.h 
    header/games/breakout/ball.h 
    header/games/breakout/levelboundary.h
    header/games/breakout/block.h 
    header/games/breakout/bgamelevel.h

    # pacman headers
    header/games/pacman/pacmanlevel.h
    header/games/pacman/pacmangameutils.h
    header/games/pacman/pacmanactor.h
    header/games/pacman/pacmanplayer.h
    header/games/pacman/pacman.h
)

# Create an executable target
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE 
    include_directories(header)
    include_directories(header/utils)
    include_directories(header/games)
    include_directories(header/games/breakout)
    include_directories(header/games/pacman)
    include_directories(header/graphics)
    include_directories(header/shapes)
    include_directories(header/scenes)
    include_directories(header/input)
    include_directories(header/app)
)

# Link SDL2 libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

# Post-build task
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/src/assets
        ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/Assets
    COMMENT "Copying Assets folder to build directory"
)
