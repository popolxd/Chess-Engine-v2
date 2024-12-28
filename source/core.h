#ifndef CORE_H
#define CORE_H

#include <stdint.h>

#define wp 0
#define wn 1
#define wb 2
#define wr 3
#define wq 4
#define wk 5

#define bp 6
#define bn 7
#define bb 8
#define br 9
#define bq 10
#define bk 11

#define whiteP 12
#define blackP 13
#define allP 14

typedef struct {
    uint8_t startSq, endSq;
} Move;

typedef struct {
    uint64_t bbs[15];
    uint8_t wtm;
    uint8_t castle[4];
    int8_t enPassantSq;
} GameState;

void InitDefaultGameState(GameState* gameState);
void InitGameStateFromFEN(GameState* gs, char* fen);

uint8_t GenPLPawnMoves(GameState* gs, uint8_t pos, uint8_t* PLMoves, uint8_t onlyCaptures);
uint8_t GenPLKnightMoves(GameState* gs, uint8_t pos, uint8_t* PLMoves, uint8_t onlyCaptures);
uint8_t GenPLKingMoves(GameState* gs, uint8_t pos, uint8_t* PLMoves, uint8_t onlyCaptures);
uint8_t GenPLBishopMoves(GameState* gs, uint8_t pos, uint8_t* PLMoves, uint8_t onlyCaptures);
uint8_t GenPLRookMoves(GameState* gs, uint8_t pos, uint8_t* PLMoves, uint8_t onlyCaptures);
uint8_t GenPLQueenMoves(GameState* gs, uint8_t pos, uint8_t* PLMoves, uint8_t onlyCaptures);

uint8_t GenAllPosMoves(GameState* gs, Move* moves, uint8_t onlyCaptures);
uint8_t GetLMovesFromPLMoves(GameState* gs, uint8_t pos, uint8_t pieceType, uint8_t* PLMoves, uint8_t PLMovesLen, Move* LMoves);
uint8_t IsCheck(GameState* gs);

uint8_t OnesFromBBToArr(uint64_t bitb, uint8_t* arr);
uint16_t GenAllPosBlockersComb(uint64_t posBlockersBB, uint64_t* result);
void FillLookups();

void MakeMove(GameState* gs, Move move);

void CopyGameState(GameState* to, GameState* from);

#endif