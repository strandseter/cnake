# CNAKE

#### Video Demo: https://www.youtube.com/watch?v=Xcgz50_l4oA

#### Description:

CNAKE is a modern implementation of the classic Snake game, developed in C using the Raylib graphics library. This project was created as my final submission for Harvard's CS50x course.

Note: This project was developed entirely by hand, without the assistance of AI tools, to strengthen and demonstrate my core programming skills.

## Project Overview

The core gameplay follows the traditional Snake game mechanics where players control a snake that grows longer as it consumes food. The challenge comes from avoiding collisions with the walls and the snake's own body while trying to achieve the highest possible score.

## Technical Implementation

### File Structure

The project consists of two key files:

1. `main.c`: The heart of the game, containing the core game logic and state management. This file implements:

   - Snake movement and collision detection
   - Food spawning mechanics
   - Score tracking and high score management
   - Game state handling (running, paused, game over)
   - Drawing functions for all game elements
     The code is structured using separate functions for each responsibility, making it maintainable and easy to understand.

2. `Makefile`: Handles the build process and provides various commands for:
   - Compiling the game executable
   - Running the game
   - Memory leak checking using the `leaks` command
   - Cleaning build artifacts
     I chose to use Make for its reliability and widespread use in C projects.

### Design Choices

#### Memory Management

One of the key design decisions was how to handle the snake's growth. I chose to use dynamic memory allocation with `malloc` and `realloc` for the snake's body, which:

- Allows the snake to grow indefinitely
- Efficiently manages memory usage
- Provides good practice with manual memory management
  While this approach is more complex than using a fixed-size array, it better demonstrates memory management principles.

#### State Management

The game uses an enum-based state system (RUNNING, PAUSED, GAME_OVER) to manage different game states. This design:

- Makes the code more maintainable and readable
- Allows for easy addition of new states
- Provides clear separation of concerns in the main game loop

#### High Score System

I implemented a persistent high score system using file I/O to:

- Add replay value to the game
- Demonstrate file handling in C
- Provide a sense of progression for players
  The scores are stored in a text file, making them persistent between game sessions.

#### Graphics and UI

Using Raylib for graphics was a deliberate choice because:

- It provides a simple yet powerful API for 2D graphics
- Has excellent documentation and community support
- Keeps the focus on programming logic rather than graphics implementation
  The UI elements are positioned dynamically based on window size, making the game adaptable to different screen configurations.

### Code Organization

The project follows a single-file architecture, which was chosen for its simplicity and clarity. All game logic, rendering functions, and state management are contained within `main.c`. This approach offers several advantages:

- Simplicity: Having everything in one file makes it easy to understand the complete game flow
- Maintainability: No need to navigate between multiple files to understand the codebase
- Self-contained: The entire game logic is visible at a glance, making debugging straightforward

While this works well for a project of this scope, larger applications would benefit from modular architecture with separate files for different concerns (e.g., game logic, rendering, input handling, and configuration management).

## Building and Running

The project uses a Makefile that handles all build scenarios. To run the game:

1. Ensure Raylib is installed (`brew install raylib` on macOS)
2. Run `make` to build the executable
3. Use `make run-snake` to start the game
4. Optional: Use `make leaks-snake` to check for memory leaks

## Future Improvements

While the current implementation is complete and functional, there are several potential improvements:

- Adding different difficulty levels
- Implementing power-ups
- Adding sound effects and background music
- Creating a multiplayer mode

This project demonstrates not only the technical skills learned in CS50 but also the importance of clean code organization, thoughtful design choices, and thorough documentation.
