#ifndef UI_H
#define UI_H

#include "core.h"

#include <raylib.h>

typedef struct {
    uint8_t engineColor;
    uint8_t engineStatus; // 0 - sleep, 1 - should move, 2 - waiting

    int8_t selectedSq;
    Move lastMove;

    Move allPosMoves[217];
    uint8_t allPosMovesLen;

    uint8_t posMoves[27];
    uint8_t posMovesLen;
} UIInfo;

void InitUIInfo(GameState* gs, UIInfo* UIInfo);
void UpdateGameState(GameState* gs, UIInfo* UIInfo);

void PrintGameState(GameState* gameState);
void PrintBB(uint64_t bitb);
void PrintMove(Move move);

void* MinimaxWrapper(void* args);

#endif