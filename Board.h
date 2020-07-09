#ifndef _board_h_
#define _board_h_
#define BOARD_SIZE 8

#include <iostream>
#include <vector>
#include <string>
#include "Piece.h"

// Output colors for display
#define RED         "\033[31m"              /* Red */
#define BOLDBLUE    "\033[1m\033[34m"       /* Bold Blue */
#define BOLDWHITE   "\033[1m\033[37m"       /* Bold White */
#define RESET       "\033[0m"
#define BOLDMAGENTA "\033[1m\033[35m"       /* Bold Magenta */

class Board{
    private:
        std::vector<std::vector<Piece*> > statusBoard;                  // current board status
        bool turn;                                                      // true:white player turn, false: black olayer turn
        void printRow(int rNum, std::vector<Piece*> &row);              // Helper function of printBoard
        std::string symbols[7] = {" ","K*", "Q", "K", "B", "R", "P"};   // Symbol mapping to display the board
        bool checkAllPossRow(int col, int row1, int row2);              // returns true if the elements on row (sR,col) to (eR,col) are empty
        bool checkAllPossCol(int row, int col1, int col2);              // returns true if the elements on column (row,sC) to (row,eC) are empty
        bool checkDiagonal(int row1, int col1, int row2, int col2);     // returns true if the elements on diagonal (sR,sC) to (eR,eC) are empty
        bool checkErrorCond(int startR, int startC, int endR, int endC);// check the basic error conditions (return true in case error is found)
    public: 
        Board();                                                        
        bool getTurn();                                                 // get current turn
        void makeMove(int startR, int startC, int endR, int endC);      // makes a move on the board after validating
        void resetBoard();                                              // Reset board to original state
        void printBoard();                                              // Print the current state of the board
};

#endif