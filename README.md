# SudokuSolver


This is a C++ program designed to solve Sudoku puzzles. It provides functionalities to initialize Sudoku boards, check if a puzzle is solvable, and display the solved or unsolved Sudoku puzzle. Sudoku is a logic-based number-placement puzzle where the objective is to fill a 9x9 grid with digits so that each column, each row, and each of the nine 3x3 subgrids that compose the grid contain all of the digits from 1 to 9.

The paramaterized constructor reads a Sudoku puzzle from an input file named input_file.txt. The file should contain 9 rows, each with 9 digits separated by commas, representing the Sudoku board. Empty squares should be represented by the digit 0. After reading the file, the constructor attempts to solve the puzzle and records whether the puzzle has a solution or not.
