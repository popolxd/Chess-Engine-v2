#include "ui.h"
#include "main.h"
#include "textures.h"
#include "engine.h"

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;
pthread_cond_t cond;
pthread_t threadId;
uint8_t engineFinished = 1;

void InitUIInfo(GameState* gs, UIInfo* UIInfo)
{
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    UIInfo->engineColor = 0;

    if (UIInfo->engineColor == gs->wtm) {
        UIInfo->engineStatus = 1;
    } else {
        UIInfo->engineStatus = 0;
        UIInfo->allPosMovesLen = GenAllPosMoves(gs, UIInfo->allPosMoves, 0);
    } 

    UIInfo->selectedSq = -1;
    UIInfo->lastMove = (Move){0, 0};

    UIInfo->posMovesLen = 0;
}

void UpdateGameState(GameState* gs, UIInfo* UIInfo)
{
    int ts = SCREEN_HEIGHT / 8;

    if (UIInfo->engineStatus == 1) {
        engineFinished = 0;
        pthread_create(&threadId, NULL, MinimaxWrapper, (void*)gs);
        UIInfo->engineStatus = 2;
    }

    if (UIInfo->engineStatus == 2 && engineFinished) {
        Output* output;
        pthread_join(threadId, (void**)(&output));

        MakeMove(gs, (*output).bestMove);
        UIInfo->lastMove = (*output).bestMove;
        free(output);

        UIInfo->allPosMovesLen = GenAllPosMoves(gs, UIInfo->allPosMoves, 0);

        UIInfo->engineStatus = 0;
    }

    // update
    if (UIInfo->engineStatus == 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

        Vector2 mousePos = GetMousePosition();

        int8_t xPos = mousePos.x / ts;
        int8_t yPos = mousePos.y / ts;

        if (UIInfo->selectedSq == -1) {
            if (xPos >= 0 && xPos < 8 && yPos >= 0 && yPos < 8) {
                uint8_t selSq = 63 - yPos*8 - xPos;

                if (gs->bbs[blackP - gs->wtm] & (1ULL << selSq)) {
                    UIInfo->selectedSq = selSq;
                    UIInfo->posMovesLen = 0;

                    for (uint8_t i = 0; i < UIInfo->allPosMovesLen; i++) {
                        if (selSq == UIInfo->allPosMoves[i].startSq) {
                            UIInfo->posMoves[UIInfo->posMovesLen] = UIInfo->allPosMoves[i].endSq;
                            UIInfo->posMovesLen++;
                        }
                    }
                }
            }
        } else {

            if (xPos >= 0 && xPos < 8 && yPos >= 0 && yPos < 8) {
                uint8_t selSq = 63 - yPos*8 - xPos;

                uint8_t valid = 0;

                for (uint8_t i = 0; i < UIInfo->posMovesLen; i++) {
                    if (selSq == UIInfo->posMoves[i]) {
                        valid = 1; break;
                    }
                }

                if (valid) {
                    UIInfo->lastMove = (Move){UIInfo->selectedSq, selSq};
                    MakeMove(gs, UIInfo->lastMove);

                    UIInfo->engineStatus = 1;
                }
            }

            UIInfo->selectedSq = -1;
        }
    }

    // draw
    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            if ((i+j) % 2) DrawRectangle(j*ts, i*ts, ts, ts, (Color){30, 30, 30, 255});
            else DrawRectangle(j*ts, i*ts, ts, ts, (Color){230, 230, 230, 255}); 
        }
    }

    if (UIInfo->lastMove.startSq != UIInfo->lastMove.endSq) {
        uint8_t xInd = 7 - UIInfo->lastMove.startSq % 8;
        uint8_t yInd = 7 - UIInfo->lastMove.startSq / 8;

        DrawRectangle(xInd*ts, yInd*ts, ts, ts, (Color){20, 230, 20, 150});

        xInd = 7 - UIInfo->lastMove.endSq % 8;
        yInd = 7 - UIInfo->lastMove.endSq / 8;

        DrawRectangle(xInd*ts, yInd*ts, ts, ts, (Color){20, 230, 20, 150});
    }

    if (UIInfo->selectedSq != -1) {
        uint8_t xInd = 7 - UIInfo->selectedSq % 8;
        uint8_t yInd = 7 - UIInfo->selectedSq / 8;

        DrawRectangle(xInd*ts, yInd*ts, ts, ts, RED);

        for (uint8_t i = 0; i < UIInfo->posMovesLen; i++) {
            xInd = 7 - UIInfo->posMoves[i] % 8;
            yInd = 7 - UIInfo->posMoves[i] / 8;

            DrawRectangle(xInd*ts, yInd*ts, ts, ts, BLUE);
        }
    }

    for (uint8_t i = 0; i < 12; i++) {
        uint8_t locs[10];
        uint8_t locsLen = OnesFromBBToArr(gs->bbs[i], locs);

        for (uint8_t j = 0; j < locsLen; j++) {
            uint8_t xInd = 7 - locs[j] % 8;
            uint8_t yInd = 7 - locs[j] / 8;

            DrawTexturePro(chessPieces, textRecs[i], (Rectangle){xInd*ts, yInd*ts, ts, ts}, (Vector2){0, 0}, 0.0f, WHITE);
        }
    }
}

void PrintGameState(GameState* gameState)
{
    uint8_t board[8][8] = {
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'},
        {'-', '-', '-', '-', '-', '-', '-', '-'}
    };

    uint8_t names[] = {'P', 'N', 'B', 'R', 'Q', 'K', 'p', 'n', 'b', 'r', 'q', 'k'};

    for (uint8_t i = 0; i < 12; i++) {
        uint64_t curBitboard = gameState->bbs[i];

        while (1) {
            int index = __builtin_ctzll(curBitboard);
            if (index == 64) break;

            curBitboard &= (curBitboard - 1);

            uint8_t xPos = 7 - index % 8;
            uint8_t yPos = 7 - index / 8;

            if (board[yPos][xPos] != '-') {
                printf("Multiple pieces on on square! %d %d\n", xPos, yPos);
                // return;
            }

            board[yPos][xPos] = names[i];
        }
    }

    for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 8; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("%s\n", (gameState->wtm) ? "white" : "black");
}

void PrintBB(uint64_t bitb)
{
    for (int8_t i = 7; i >= 0; i--) {
        for (int8_t j = 7; j >= 0; j--) {
            if (bitb & (1ULL << (i*8 + j))) {
                printf("1");
            } else {
                printf("0");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void PrintMove(Move move)
{
    uint8_t startCol = 104 - move.startSq % 8;
    uint8_t startRow = move.startSq / 8 + 1;
    uint8_t endCol = 104 - move.endSq % 8;
    uint8_t endRow = move.endSq / 8 + 1;

    printf("%c%hhu %c%hhu\n", startCol, startRow, endCol, endRow);
}

void* MinimaxWrapper(void* args)
{
    uint8_t depth = 5;

    GameState gs;
    CopyGameState(&gs, (GameState*)args);
    
    Output* output = (Output*)malloc(sizeof(Output));
    *output = Minimax(&gs, depth, -32768, 32767);

    pthread_mutex_lock(&lock);
    engineFinished = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);

    return (void*)output;
}