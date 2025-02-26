# Self Solving Maze Generator in C++

## Description
This project is a simple C++ program that generates a random maze using depth-first search and then solves it using a stack-based approach. The maze is represented as a grid where walls and paths are marked accordingly. The program creates a perfect maze (one without loops) and then finds a solution path from the start to the end.

## Features
- Generates a random maze of specified dimensions.
- Uses depth-first search for maze generation.
- Implements a backtracking algorithm to find the solution.
- Displays the maze in a textual format.

## How It Works
### Maze Generation
1. The maze grid is initialized with walls and empty spaces.
2. A random starting point is chosen.
3. The depth-first search algorithm recursively carves paths until all cells are visited.

### Maze Solving
1. The solver starts at the entrance of the maze.
2. It explores possible paths using a stack-based depth-first search.
3. The correct path is marked, leading to the exit.


