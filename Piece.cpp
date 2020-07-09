#include "Piece.h"

// PIECES
Piece::Piece(colors pColor, typeP ptype){
    this->pieceColor = pColor;
    this->pieceType = ptype;
}


// PAWN
Pawn::Pawn(colors pColor, typeP pType) : Piece(pColor, pType){};

bool Pawn::move(int startR, int startC, int endR, int endC){ 
    if(this->pieceColor == white){   // white
        if( (startR!=6 && startR-endR>=2) || (startR<endR) || (startR==6 && startR-endR>=3) || (abs(endC-startC)>1) ){
            //std::cout << "Error: Invalid pawn move!";
            return false;
        }
    }
    else{   // black
        if( (startR!=1 && endR-startR>=2) || (endR<startR) || (startR==1 && endR-startR>=3) || (abs(endC-startC)>1) ){
            //std::cout << "Error: Invalid pawn move!";
            return false;
        } 
    }
    //std::cout << "valid pawn move!";
    return true;
}


// KING
King::King(colors pColor, typeP pType) : Piece(pColor, pType){};

bool King::move(int startR, int startC, int endR, int endC){
    return (abs(startR-endR)<=1 && abs(startC-endC)<=1);
}


// QUEEN
Queen::Queen(colors pColor, typeP pType) : Piece(pColor, pType){};

bool Queen::move(int startR, int startC, int endR, int endC){
    return (abs(startR-endR) == abs(startC-endC)) || (abs(startR-endR)>0 && startC==endC) || (abs(startC-endC)>0 && startR==endR);
}


// BISHOP
Bishop::Bishop(colors pColor, typeP pType) : Piece(pColor, pType){};

bool Bishop::move(int startR, int startC, int endR, int endC){
    return (abs(startR-endR) == abs(startC-endC));
}


// KNIGHT
Knight::Knight(colors pColor, typeP pType) : Piece(pColor, pType){};

bool Knight::move(int startR, int startC, int endR, int endC){
    return (abs(startR-endR)==2 && abs(startC-endC)==1) || (abs(startR-endR)==1 && abs(startC-endC)==2);
}


// ROOK
Rook::Rook(colors pColor, typeP pType) : Piece(pColor, pType){};

bool Rook::move(int startR, int startC, int endR, int endC){
    return (abs(startR-endR)>0 && startC==endC) || (abs(startC-endC)>0 && startR==endR);
}


