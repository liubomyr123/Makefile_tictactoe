# Tic Tac Toe Game in C with GTK

This project is a simple implementation of the classic Tic Tac Toe game using the C programming language and GTK+3 for the graphical user interface. It allows two players to play on the same computer, with the option to restart the game once it ends.

## Features

- Play Tic Tac Toe with two players (Player 1: X, Player 2: O)
- Graphical user interface created using GTK+3
- Reset the game anytime by clicking the "Restart" button
- Displays the winner (Player 1 or Player 2) or "Game Over" when the game ends in a draw
- Simple and responsive interface

## Requirements

To build and run this project, you need to have the following installed:

- **GCC** (GNU Compiler Collection) for compiling the C code
- **GTK+3** library for creating the graphical user interface
  - On Ubuntu, you can install it with:
    ```bash
    sudo apt-get install libgtk-3-dev
    ```
- **pkg-config** for managing compilation flags for GTK+3 (usually comes with GTK installation)

## Installation

1. Clone the repository:
    ```bash
    git clone https://github.com/liubomyr123/Makefile_tictactoe.git
    ```

2. Build the project:
    ```bash
    make
    ```

3. Run the game:
    ```bash
    ./tic_tac_toe
    ```

## How to Play

- Player 1 uses `X` and Player 2 uses `O`.
- Click on any of the 9 grid cells to place your mark (`X` or `O`).
- The game will detect when a player wins or if the game ends in a draw.
- Once the game ends, click the **"Restart"** button to start a new game.

## Code Structure

- **tic_tac_toe.c**: Contains the main game logic and GUI implementation using GTK.
- **Makefile**: Used to build the project using `gcc` with necessary GTK flags.
- **README.md**: This file, providing documentation for the project.

## How It Works

1. The game initializes a 3x3 grid of buttons for the Tic Tac Toe board.
2. Each button represents a position in the grid. Players take turns clicking on the buttons to place their marks.
3. The program checks after every move if there is a winner or if the game is a draw.
4. If a player wins, the game displays a message indicating the winner.
5. If there is no winner and all positions are filled, the game ends in a draw.

## Game Logic

The game logic checks the following possible winning combinations for both players:

- Rows: (1, 2, 3), (4, 5, 6), (7, 8, 9)
- Columns: (1, 4, 7), (2, 5, 8), (3, 6, 9)
- Diagonals: (1, 5, 9), (3, 5, 7)

If any of these combinations are filled by the same player's mark (`X` or `O`), that player is declared the winner.

## Contributions

Feel free to fork this repository, create issues, and submit pull requests. Contributions are welcome!

---

Enjoy the game! 😊
