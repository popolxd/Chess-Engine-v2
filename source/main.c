#include "main.h"
#include "core.h"
#include "ui.h"
#include "engine.h"
#include "textures.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <raylib.h>

int SCREEN_WIDTH;
int SCREEN_HEIGHT;

int main(void)
{
    srand(time(NULL));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess v2!");

    // fullscreen
    int display = GetCurrentMonitor();
    int monitorW = GetMonitorWidth(display), monitorH = GetMonitorHeight(display);
    SCREEN_WIDTH = monitorW;
    SCREEN_HEIGHT = monitorH;
    SetWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    ToggleFullscreen();

    FillLookups();

    GameState gameState;
    InitDefaultGameState(&gameState);
    // InitGameStateFromFEN(&gameState, "r1b1qrk1/ppp2ppp/2n5/b7/2B1PBn1/P1N2N2/1PP2PPP/R2Q1RK1 b - - 2 12");

    UIInfo UIInfo;
    InitUIInfo(&gameState, &UIInfo);

    InitTextures();

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(BLACK);
            
            UpdateGameState(&gameState, &UIInfo);
        EndDrawing();
    }

    // while (1) {

    //     // engine
    //     uint8_t depth = 8.5f - 0.109375f*__builtin_popcountll(gameState.bbs[allP]);
    //     printf("thinking with depth: %d\n", depth);
        
    //     Output output = Minimax(&gameState, depth, -32768, 32767);
    //     MakeMove(&gameState, output.bestMove);

    //     PrintGameState(&gameState);
    //     // PrintMove(output.bestMove);

    //     uint8_t startCol, startRow, endCol, endRow;
    //     Move playedMove;

    //     while (1) {
    //         scanf("%c%hhu %c%hhu", &startCol, &startRow, &endCol, &endRow);

    //         playedMove = (Move){
    //             .startSq = (startRow - 1)*8 + (104 - startCol),
    //             .endSq = (endRow - 1)*8 + (104 - endCol),
    //         };

    //         Move legalMoves[217];
    //         uint8_t legalMovesLen = GenAllPosMoves(&gameState, legalMoves, 0);

    //         // for (uint8_t i = 0; i < legalMovesLen; i++) {
    //         //     PrintMove(legalMoves[i]);
    //         // }

    //         uint8_t isLegal = 0;

    //         for (uint8_t i = 0; i < legalMovesLen; i++) {
    //             if (playedMove.startSq == legalMoves[i].startSq && playedMove.endSq == legalMoves[i].endSq) {
    //                 isLegal = 1;
    //                 break;
    //             }
    //         }

    //         if (isLegal) break;
    //     }

    //     MakeMove(&gameState, playedMove);
    // }

    return 0;
}