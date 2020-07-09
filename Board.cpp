#include "Board.h"

Board::Board(){
    this->turn = true;

    std::vector<Piece* > temp(BOARD_SIZE);
    for(int i=0; i<BOARD_SIZE; i++)
       statusBoard.push_back(temp);
    
    resetBoard();
}

// Reset board to original state
void Board::resetBoard(){
    //std::cout << statusBoard.size() <<":" << statusBoard[0].size() << std::endl;
    // Initialize all the positions to None
    for(int r=0; r<BOARD_SIZE; r++){
        for(int c=0; c<BOARD_SIZE; c++){
            statusBoard[r][c] = new Piece(none, no);
        }
    }

    // Initializing Pawns
    for(int c =0; c<8; c++){
        statusBoard[1][c] = new Pawn(black, pawn);
        statusBoard[6][c] = new Pawn(white, pawn);
    }

    int rB = 0;
    int rW = 7;

    // initializing King 
    statusBoard[rB][4] = new King(black, king);
    statusBoard[rW][4] = new King(white, king);

    // initializing Queen  
    statusBoard[rB][3] = new Queen(black, queen);
    statusBoard[rW][3] = new Queen(white, queen);
    
    // initializing Bishop
    statusBoard[rB][2] = new Bishop(black, bishop);
    statusBoard[rB][5] = new Bishop(black, bishop);
    statusBoard[rW][2] = new Bishop(white, bishop);
    statusBoard[rW][5] = new Bishop(white, bishop);

    // initializing Knight
    statusBoard[rB][1] = new Knight(black, knight);
    statusBoard[rB][6] = new Knight(black, knight);
    statusBoard[rW][1] = new Knight(white, knight);
    statusBoard[rW][6] = new Knight(white, knight);

    // initializing Rook
    statusBoard[rB][0] = new Rook(black, rook);
    statusBoard[rB][7] = new Rook(black, rook);
    statusBoard[rW][0] = new Rook(white, rook);
    statusBoard[rW][7] = new Rook(white, rook);

}

// Print the row of board
void Board::printRow(int rNum, std::vector<Piece*> &row){
    std::cout << rNum+1 << "";
    for(int c =0; c<row.size(); c++){
        if(row[c]->pieceColor == white)
            std::cout << "|" << BOLDWHITE << symbols[row[c]->pieceType] << RESET << " ";
        else
            std::cout << "|" << BOLDBLUE << symbols[row[c]->pieceType] << RESET << " ";
    }
    std::cout << "|" << std::endl;
}

// Print the current state of the board
void Board::printBoard(){
    std::cout << std::endl;
    std::cout << "  1  2  3  4  5  6  7  8 " << std::endl;

    for(int r=0; r<BOARD_SIZE; r++){
        // print dashes to separate rows
        std::cout << "  ________________________" << std::endl;
        printRow(r, statusBoard[r]);
    }
    std::cout << "  ________________________" << std::endl;
    std::cout << "  1  2  3  4  5  6  7  8 " << std::endl;
    std::cout << std::endl;
}

// returns true if the elements on row (sR,col) to (eR,col) are empty
bool Board::checkAllPossRow(int col, int sR, int eR){
    sR>eR? sR-- : sR++;
    while(sR != eR){
        
        if(statusBoard[sR][col]->pieceType != no)
            return false;

        sR>eR? sR-- : sR++;
    }

    return true;
}

// returns true if the elements on column (row,sC) to (row,eC) are empty
bool Board::checkAllPossCol(int row, int sC, int eC){
    sC>eC? sC-- : sC++;
    while(sC != eC){   
        if(statusBoard[row][sC]->pieceType != no)
            return false;

        sC>eC? sC-- : sC++;  
    }
    return true;
}

// returns true if the elements on diagonal (sR,sC) to (eR,eC) are empty
bool Board::checkDiagonal(int sR, int sC, int eR, int eC){
    sR>eR? sR-- : sR++;
    sC>eC? sC-- : sC++;
    while(sR!=eR){
        if(statusBoard[sR][sC]->pieceType != no)
            return false;
        
        sR>eR? sR-- : sR++;
        sC>eC? sC-- : sC++;
    }
    return true;
}

// check the basic error conditions (return true in case error is found)
bool Board::checkErrorCond(int startR, int startC, int endR, int endC){
    return ( (statusBoard[startR][startC]->pieceColor == none) || (startR==endR && startC==endC) ||
        // check if to the place where it needs to be moved is having same colored piece then invalid
        (turn && statusBoard[endR][endC]->pieceColor == white) || (!turn && statusBoard[endR][endC]->pieceColor == black) ||
        // check if turn is of white but black piece is moved and vice a versa
        (turn && statusBoard[startR][startC]->pieceColor != white) || (!turn && statusBoard[startR][startC]->pieceColor != black) );
}

// makes a move on the board after validating 
void Board::makeMove(int startR, int startC, int endR, int endC){
    // move outside the boundary of the board
    if(startR>=1 && startR<=8 && startC>=1 && startC<=8 && endR>=1 && endR<=8 && endC>=1 && endC<=8){
        startR--; startC--; endR--; endC--;
        
        if(checkErrorCond(startR, startC, endR, endC)){  // check basic error conditions
            std::cout << RED << "Invalid move, Please make a valid move!"  << RESET << std::endl;
            return;
        }
        else{
            // check if move is valid based on type of piece
            if(statusBoard[startR][startC]->move(startR, startC, endR, endC)){ // If this is a valid move

                // Game termination condition: if a king is killed
                if(statusBoard[endR][endC]->pieceType == king){ 
                    if(turn)
                        std::cout << "White wins with below board position." << std::endl;
                    else
                        std::cout << "Black wins with below board position." << std::endl;
                    
                    printBoard();
                    exit(0);
                }

                // For Queen, Bishop and Rook check if the path to the destination is clear
                switch(statusBoard[startR][startC]->pieceType){
                    case 2: // If move was of Queen and row/col/diagonal was not empty
                        if(startR==endR && !checkAllPossCol(startR, startC, endC) ){
                            std::cout << RED << "Invalid move, Please make a valid move!"  << RESET << std::endl;
                            return;
                        }
                        else if(startC==endC && !checkAllPossRow(startC, startR, endR) ){
                            std::cout << RED << "Invalid move, Please make a valid move!"  << RESET << std::endl;
                            return;
                        }
                        else if(startR!=endR && startC!=endC && !checkDiagonal(startR, startC, endR, endC) ){
                            std::cout << RED << "Invalid move, Please make a valid move!"  << RESET << std::endl;
                            return;
                        }
                    break;

                    case 4: // If move was of Bishop and diagonal was not empty
                        if(!checkDiagonal(startR, startC, endR, endC) ){
                            std::cout << RED << "Invalid move, Please make a valid move!"  << RESET << std::endl;
                            return;
                        }
                    break;

                    case 5: // If move was of Rook and if the whole row/column was not empty
                        if(startR==endR && !checkAllPossCol(startR, startC, endC)){
                            std::cout << RED << "Invalid move, Please make a valid move!"  << RESET << std::endl;
                            return;
                        }
                        else if(startC==endC && !checkAllPossRow(startC, startR, endR)){
                            std::cout << RED << "Invalid move, Please make a valid move!"  << RESET << std::endl;
                            return;
                        }  
                    break;
                }
                
                // Move the piece and mark its previous position as unused.
                statusBoard[endR][endC] = statusBoard[startR][startC];
                statusBoard[startR][startC] = new Piece(none, no);

                // Alternate the turn
                turn = !turn;
            }
            else{ // move was invalid based on the piece type
                std::cout << RED << "Piece out:Invalid move, Please make a valid move!"  << RESET << std::endl;
                return;
            }            
        }
    }
    else{ // move out of board
        std::cout << RED << "Invalid position, the row and column can be from 1 to 8 only!"  << RESET << std::endl;
    }
}

// get current turn (true--> white, false-->black)
bool Board::getTurn(){
    return this->turn;
}

// print the display menu information
void printMenu(){
    std::cout << "\nThe color " << BOLDBLUE << "Bold Blue " << RESET << "is Black and " << BOLDWHITE << "Bold white " << RESET << "is white player.\n";
    std::cout << BOLDMAGENTA << "The symbols on the board mean the following: R--> Rook, K --> Knight, B-->Bishop, Q-->Queen, K*-->King, P-->Pawn\n\n";
    std::cout << "The following input choices are available: \n";
    std::cout << "Enter 0 to make a new move\n";
    std::cout << "Enter 1 to reset the board\n";
    std::cout << "Enter 2 to print the current status of board\n";
    std::cout << "Enter 3 to print the information menu\n"; 
    std::cout << "Enter 4 to got to seamless play mode\n\n"; 
    std::cout << "After entering 0, input the move using following format\n";
    std::cout << "<current_row_index><space><current_column_index><space><destination_row_index><space><destination_column_index><enter>\n\n" << RESET;
}

void playSeamless(Board b){
    int sR, sC, eR, eC;
    while(true){
        // display board
        b.printBoard();

        // get move
        if(b.getTurn())
            std::cout << "Enter move for white: ";
        else
            std::cout << "Enter move for Black: ";

        std::cin >> sR >> sC >> eR >> eC;

        // make move
        b.makeMove(sR, sC, eR, eC);
    }
}

int main(){

    // Instantiate board
    Board b = Board();

    int sR, sC, eR, eC;
    int choice;

    printMenu();

    while(true){
        std::cout << "Enter choice(3 for Help): ";
        // Take choice and perform action accordingly
        std::cin >> choice;

        switch(choice){
            case 0: // Make a move
                if(b.getTurn())
                    std::cout << "Enter move for white: ";
                else
                    std::cout << "Enter move for Black: ";

                std::cin >> sR >> sC >> eR >> eC;
                b.makeMove(sR, sC, eR, eC);
                //b.printBoard();
            break;

            case 1: // Reset board
                b.resetBoard();
            break;

            case 2: // print state of current board
                b.printBoard();
            break;

            case 3: // Print information
                printMenu();
            break;

            case 4:
                playSeamless(b);
                exit(0);
            break;
        }
        
    }
    return 0;
}