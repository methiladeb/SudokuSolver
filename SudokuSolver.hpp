/*
Name: Methila Deb
*/

#ifndef SUDOKU_SOLVER_HPP_
#define SUDOKU_SOLVER_HPP_
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

namespace Sudoku
{ 
  struct Location
  {
    int row;
    int col;
  };
}

class SudokuSolver
{
public:

//public members here

  //default constructor that will initialize empty board
  SudokuSolver();
  //parameterized constructor that reads input file to initialize board
  SudokuSolver(std::string input_file);

//Accessors & Mutators

  //returns true if puzzle is solvable, false otherwise
  bool isPuzzleSolvable() const; //may remove const
  //records the puzzle as being solvable
  void setSolvable();
  //returns 2D pointer array representing the puzzle
  int** getPuzzleNumbers();
  //sets 2D pointer array representing puzzle to value of parameter
  void setPuzzleNumbers(int** puzzle);

// Utility functions

  //returns Location object w/ coordinates of first 0 found in 2D pointer array
  Sudoku::Location returnNextEmpty() const; //may remove const
  //returns true if value parameter can legally be placed at given location in 2D array w/o breaking rules
  bool checkLegalValue(int value, Sudoku::Location location) const; //may remove const
  //will display board as given illustration
  void display() const;

  // Helper function
  bool solve(int** puzzle);



private:
//private members here

  int** puzzle_ = new int*[9];
  bool is_solvable_ = false;

};

#endif
