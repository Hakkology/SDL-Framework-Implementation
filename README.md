# SDL-Game-Station

Following section explains the procedure on this repository step by step, used as a reminder for myself and other projects.
Main purpose was to create a C++ game engine and an application that works on that engine in 2D space with basic rendering functionality.
All classes and functions are also glued together with CMake.txt file on a very manual level.
Steps are basically divided for easy readability.

Application:
- Vector class created with basic mathematical functions.
- Class to draw a line is created using Bresenham's line drawing algorithm.
- Shape class created so that basic geometric shapes such as triangles, rectangles, circles are made possible in 2D space.
- Each shape has the fillpoly function to color all pixels by each column of pixels within the boundaries so that shapes can have colors.

Graphics and Controls:
- Color, Screen and Screenbuffer classes created. Using SDL Window properties, pixels are created and buffers are swapped.
- Some static colors are premade for future use. Screen draw functions added on shapes to be able to draw the basic shapes.
- A scene class is created to have scenes with different purposes, each scene representing a user interface or the game itself.
- Basic input functions using SDL is created with left&right (A-D), up&down (W-S), accept&cancel (Q-E), push&modify (F-R).
- Input functions for mouse movement and keys are also created but is not used much within the scope of this project.
- A file command loader is implemented to be able to read from data written in text files for level design or other features.
- Constants file is introduced to be able to access specific places on the app easily and manipulate specific parameters to test the application.
- Each game class to create the game scene inherits from a game class for basic inheritence.

Breakout Game:
- An excluder class to control collisions is implemented using intersect functions in shapes.
- The paddle, ball and blocks are written using basic rectangles and this excluder properties.
- Using excluder class, bounce mechanics with collision properties is implemented (Reverse bounce direction is not a bug, its a feature).
- Levels are loaded from a txt file using the file command loader and loaded with collision properties on boundaries with three levels.
- Gamestates and player lives are implemented.

Fonts and Sprites:
- BMPtext and sprite classes are written so that specific images from bmp images can be pulled and used for our games.
- Similarly, using a bmp image, a font is created for text display and UI features.
- These features are colored with overlays and textured. (Ehem... Not Implemented Scene also?)
- A class for button is implemented, this allowed me to have UI's with displayed text and the buttons could be chosen for further functionality.
- UI movement is with A-D (up and down) and E-Q (accept and exit), creating a menu with button options.
- This menu is used to access each game scene and the start scene for each game. Each game has highscore implementation (Not implemented yet, wtb time)
- The app is restructured in such a way that the button options menu present us the four game choices, and each game has the actual game scene and the highscore scene.

Tetris Game:
- Tetromino pieces are implemented using rectangle class and its properties. Each piece is given functions to rotation and input.
- A piece is created for the actual input and the next piece is shown on the right side for the player to evaluate.
- Tetris level is created to define boundaries. Similarly, bmpfont is used to display the score and other needed text.
- Gamestates and the score feature is implemented and the difficulty is set up.

Animation and AI features:
- An actor class is created to be used on cases where we have specific characters who are supposed to move on their own.
- Animation frames are read from bmp images and listed so that they can be displayed within a specific duration or time.
- Animated sprites for pacman, ghosts and the asteroids are created for future use.

Pacman Game:
- Similarly, game is drawn and loaded from file command loader. Pacman level with walls txt file is added and file command loader is configured in such a way that this level is loaded when the game begins.
- Each level part have access to excluder part if a wall exists. This excluder allowed me add collisions on walls.
- With the actor class, pacman animation spritesheet is used to create the pacmanplayer class and its animated sprite. The same is done for ghosts, inky, blinky, pinky, clyde.
- Pacmanghost class is also created using this actor class and can detect collisions on walls.
- Pellets, bonus items like cherries and the super power nodes are added to give different functionality to game. Score is kept based on these pickups.
- Ghost AI's and their states are implemented to make the game as challenging as possible for Pacman in pacmanghostai.
- Game states and player lives are implemented. Using these features, ghosts are released and a game over state is implemented.

Asteroids Game:
- Bmp image for all assets is provided under assets. Using these assets, animated sprites are created for asteroids and the spaceship.
- Excluder collisions are used to set explosion states and detect collision situations.
- The player controls a spaceship that can fire missiles at asteroids. Only three missiles can be fired at once. The spaceship can wrap around the screen as well.
- Asteroids spawn randomly for player to watch out for and has states such as small, medium, large etc.
- The spaceship's movement should be able to only move straight in the direction it is facing and be able to rotate around its centre to change its facing. (This is a bug and im currently working on it)
- Game states are added to show cooldowns and scores and wait for the player to be ready.

