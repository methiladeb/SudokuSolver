/*
Name: Methila Deb
*/

#include "SudokuSolver.hpp"

/*
default constructor initializing an empty board -> board filled with zeros
marked unsolvable
*/
SudokuSolver::SudokuSolver() {
    //iterates over each element of puzzle_ array & sets those values to 0
    for (int i=0; i<9; i++) {
        puzzle_[i] = new int[9];
        for(int j=0; j<9; j++) {
            puzzle_[i][j] = 0;
        }
    }
}

/* 
Param constructor reads input file to intialize board.
Input file consists of 9 digits on each row seperated by commas
  & 9 rows seperated by new line characters \n, corresponding to a sudoku board.
Empty squares contain the digit 0.
After reading the file, the constructor tries to solve it & records whether the puzzle
  has a solution or not.
*/
SudokuSolver::SudokuSolver(std::string input_file) {
  // open the file using an input stream
  std::ifstream infile(input_file);

  // declare variables to hold puzzle strings & digits
  std::string puzzle;
  std::string digit;
  int digit_;

  // initialize the row & col indices 
  int row = -1;
  int col;

  // create 2D array to hold the puzzle
  for (int i = 0; i < 9; i++) {
    puzzle_[i] = new int[9];
  }

  // read puzzle from file, one line at a time
  while(getline(infile, puzzle)){

    // use a string stream to split each line into individual digits
    std::stringstream line(puzzle);

    // increment row index for each line
    row++;
    // reset col index to -1
    col = -1;

    // read each digit from line & store it in puzzle array
    while(getline(line, digit, ',')){
      col++;
      digit_ = stoi(digit);
      puzzle_[row][col] = digit_;
    }
  }

  // if puzzle can be solved, mark it as solvable
  if(solve(puzzle_)){
    setSolvable();
  }
}

// returns if puzzle is solvable or not
bool SudokuSolver::isPuzzleSolvable() const
{
  return is_solvable_;
}

// records the puzzle as being solvable
void SudokuSolver::setSolvable()
{
  is_solvable_ = true;
}

// returns 2D pointer array representing the puzzle
int** SudokuSolver::getPuzzleNumbers()
{
  return puzzle_;
}

// sets 2D pointer array representing puzzle to value of parameter
void SudokuSolver::setPuzzleNumbers(int** puzzle)
{
  puzzle_ = puzzle;
}

Sudoku::Location SudokuSolver::returnNextEmpty() const {
  // creates location object to hold row & column indices of next empty cell
  Sudoku::Location position;
  position.row = -1;
  position.col = -1;

  // iterate through each cell in Sudoku board
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      
      // if cell is empty, then store its row & column indices in position object & return it
      if (puzzle_[i][j]==0) {
        position.row = i;
        position.col = j;
        return position;
      }
    }
  }
  // if no empty cell is found, return position object w/ row & column indices set to -1
  return position;
}

bool SudokuSolver::checkLegalValue(int value, Sudoku::Location location) const {
  // calculate row & column indices of 3x3 sub-grid containing given location
  int row_index = location.row/3;
  int col_index = location.col/3;

  // calculate starting row & column indeces of 3x3 sub-grid
  int r = row_index*3;
  int c = col_index*3;

  // if cell at given location already contains a value, then value is not legal
  if (puzzle_[location.row][location.col] != 0) {
    return false;
  }

  // iterate through each cell in 3x3 sub-grid containing given location
  for (int i=0; i<3; i++) {
    for (int j=0; j<3; j++) {

      // if any of the cells in sub-grid already contains a value, then value is not legal
      if (puzzle_[r+i][c+j] == value) {
        return false;
      }
    }
  }

  // iterate through each cell in same row & column as given location
  for (int i=0; i<9; i++) {
    
    // if any of the cells in same row/column already contains given value, then value is not legal
    if (puzzle_[i][location.col] == value || puzzle_[location.row][i] == value) {
      return false;
    }
  }

  // if none of above conditions are met, then value is legal
  return true;
}

void SudokuSolver::display() const {
  // iterates through each row of puzzle board
  for(int i=0; i<9; i++){
    // if it's a multiple of 3 rows, print out a seperate line to seperate 3x3 sub-grids
    if((i)%3 == 0 && i !=0) {
      std::cout << "- - - - - - - - - - - -\n";
    }
    // iterates through each column of puzzle board
    for(int j=0; j<9; j++) {
      // if it's a multiple of 3 columns, print out a seperator to seperate 3x3 sub-grids
      if((j)%3 == 0 && j !=0) {
        std::cout << " | ";
      }

      // if cell at current posiiton is empty, print out X to represent it
      if(puzzle_[i][j] == 0) {
        std::cout << "X";
      }
      // otherwise, print out value of cell
      else {
        std::cout << puzzle_[i][j];
      }

      // if not in last column of row, print out a space to seperate cells
      if(j !=8) {
        std::cout << " ";
      }
    }

    // go to the next row of the board
    std::cout << std::endl;
  }
}

// puzzle takes in 2D array representing Sudoku puzzle 
bool SudokuSolver::solve(int** puzzle) {
  // get the next empty cell in the puzzle
  Sudoku::Location position = {returnNextEmpty().row, returnNextEmpty().col};

  // if there are no empty cells left, the puzzle is solved
  if (position.row == -1 && position.col == -1) {
    return true;
  }

  // try each value from 1-9 in current cell
  for (int i=1; i<=9; i++) {
    // check if current value is legal choice for current cell
    if (checkLegalValue(i,position)) {
      // if current value is legal, set it in puzzle & attempt to solve the puzzle revursively
      puzzle_[position.row][position.col] = i;
      if (solve(puzzle_)) {
        return true;
      }

      // if recursive solve fails, reset current cell & try next value
      puzzle_[position.row][position.col] = 0;
    }
  }
  // if no value works, backtrack & try diff value
  return false;
}