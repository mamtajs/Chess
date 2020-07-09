#ifndef _piece_h_
#define _piece_h_
#include <iostream>
#include <vector>
#include <string>
#include <math.h>

// Color of pieces on the board
enum colors {none=0, black=1, white=2};
// Type of pieces on the board
enum typeP {no=0, king=1, queen=2, knight=3, bishop=4, rook=5, pawn=6};

// Basic piece on board
class Piece{
    public:
        Piece(colors pColor, typeP pType);
        colors pieceColor;
        typeP pieceType;
        virtual bool move(int startR, int startC, int endR, int endC){ return false; };
};

// Pawn pieces on board
class Pawn : public Piece{
    public:
        Pawn(colors pColor, typeP pType);
        bool move(int startR, int startC, int endR, int endC);
};

// King pieces on board
class King : public Piece{
    public:
        King(colors pColor, typeP pType);
        bool move(int startR, int startC, int endR, int endC);
};

// Queen pieces on board
class Queen : public Piece{
    public:
        Queen(colors pColor, typeP pType);
        bool move(int startR, int startC, int endR, int endC);
};

// Bishop pieces on board
class Bishop : public Piece{
    public:
        Bishop(colors pColor, typeP pType);
        bool move(int startR, int startC, int endR, int endC);
};

// Knight pieces on board
class Knight : public Piece{
    public:
        Knight(colors pColor, typeP pType);
        bool move(int startR, int startC, int endR, int endC);
};

// Rook pieces on board
class Rook : public Piece{
    public:
        Rook(colors pColor, typeP pType);
        bool move(int startR, int startC, int endR, int endC);
};

#endif