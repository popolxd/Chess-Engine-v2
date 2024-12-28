#ifndef ENGINE_H
#define ENGINE_H

#include "core.h"

typedef struct {
    int16_t eval;
    Move bestMove;
} Output;

Output Minimax(GameState* gs, uint8_t depth, int16_t alpha, int16_t beta);
int16_t CaptureSearch(GameState* gs, int16_t alpha, int16_t beta);

void OrderMoves(GameState* gs, Move* allMoves, uint8_t allMovesLen);
void SortMoves(Move* allMoves, uint8_t allMovesLen, int16_t* moveScores);

int16_t EvaluatePos(GameState* gs);

#endif