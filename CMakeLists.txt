cmake_minimum_required(VERSION 3.12)
project(SDL_Framework)

# Add your source files
set(SOURCES
    src/main.cpp
)

# Add your header files
set(HEADERS

)

# Include directories
include_directories(header) 

# Create an executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
