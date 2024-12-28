#include "engine.h"
#include "core.h"

Output Minimax(GameState* gs, uint8_t depth, int16_t alpha, int16_t beta)
{
    if (depth == 0) {
        return (Output){
            .eval = CaptureSearch(gs, alpha, beta),
            .bestMove = (Move){.startSq = 64, .endSq = 64},
        };
    }

    Output output;

    GameState save;
    CopyGameState(&save, gs);

    if (gs->wtm) {
        output.eval = -32768;

        Move allPosMoves[217];
        uint8_t allPosMovesLen = GenAllPosMoves(gs, allPosMoves, 0);

        if (allPosMovesLen == 0) {
            if (IsCheck(gs)) return (Output){.eval = -32700 - depth, .bestMove = (Move){.startSq = 65, .endSq = 65},};
            else return (Output){.eval = 0, .bestMove = (Move){.startSq = 66, .endSq = 66},};
        }

        OrderMoves(gs, allPosMoves, allPosMovesLen);

        for (uint8_t i = 0; i < allPosMovesLen; i++) {
            MakeMove(gs, allPosMoves[i]);
            Output search = Minimax(gs, depth-1, alpha, beta);
            CopyGameState(gs, &save);

            if (search.eval > output.eval) {
                output.eval = search.eval;
                output.bestMove = allPosMoves[i];
            }
            if (search.eval > alpha) {
                alpha = search.eval;
                if (beta <= alpha) break; // pruning
            }
        }

    } else {
        output.eval = 32767;

        Move allPosMoves[217];
        uint8_t allPosMovesLen = GenAllPosMoves(gs, allPosMoves, 0);

        if (allPosMovesLen == 0) {
            if (IsCheck(gs)) return (Output){.eval = 32700 + depth, .bestMove = (Move){.startSq = 67, .endSq = 67},};
            else return (Output){.eval = 0, .bestMove = (Move){.startSq = 68, .endSq = 68},};
        }

        OrderMoves(gs, allPosMoves, allPosMovesLen);

        for (uint8_t i = 0; i < allPosMovesLen; i++) {
            MakeMove(gs, allPosMoves[i]);
            Output search = Minimax(gs, depth-1, alpha, beta);
            CopyGameState(gs, &save);

            if (search.eval < output.eval) {
                output.eval = search.eval;
                output.bestMove = allPosMoves[i];
            }
            if (search.eval < beta) {
                beta = search.eval;
                if (beta <= alpha) break; // pruning
            }
        }
    }

    return output;
}

int16_t CaptureSearch(GameState* gs, int16_t alpha, int16_t beta)
{
    int16_t eval = EvaluatePos(gs);

    GameState save;
    CopyGameState(&save, gs);

    if (gs->wtm) {
        if (eval > alpha) {
            alpha = eval;
            if (beta <= alpha) return eval;
        }

        Move allPosMoves[71];
        uint8_t allPosMovesLen = GenAllPosMoves(gs, allPosMoves, 1);

        if (allPosMovesLen == 0) {
            int16_t posEval = EvaluatePos(gs);
            if (posEval > eval) eval = posEval;
        }

        OrderMoves(gs, allPosMoves, allPosMovesLen);

        for (uint8_t i = 0; i < allPosMovesLen; i++) {
            MakeMove(gs, allPosMoves[i]);
            int16_t searchEval = CaptureSearch(gs, alpha, beta);
            CopyGameState(gs, &save);

            if (searchEval > eval) eval = searchEval;
            if (searchEval > alpha) {
                alpha = eval;
                if (beta <= alpha) break; // pruning
            }
        }

    } else {
        if (eval < beta) {
            beta = eval;
            if (beta <= alpha) return eval;
        }

        Move allPosMoves[71];
        uint8_t allPosMovesLen = GenAllPosMoves(gs, allPosMoves, 1);

        if (allPosMovesLen == 0) {
            int16_t posEval = EvaluatePos(gs);
            if (posEval < eval) eval = posEval;
        }

        OrderMoves(gs, allPosMoves, allPosMovesLen);

        for (uint8_t i = 0; i < allPosMovesLen; i++) {
            MakeMove(gs, allPosMoves[i]);
            int16_t searchEval = CaptureSearch(gs, alpha, beta);
            CopyGameState(gs, &save);

            if (searchEval < eval) eval = searchEval;
            if (searchEval < beta) {
                beta = eval;
                if (beta <= alpha) break; // pruning
            }
        }
    }

    return eval;
}

int16_t pawnSquareTable[64] = {
    0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
    5,  5, 10, 25, 25, 10,  5,  5,
    0,  0,  0, 20, 20,  0,  0,  0,
    5, -5,-10,  0,  0,-10, -5,  5,
    5, 10, 10,-20,-20, 10, 10,  5,
    0,  0,  0,  0,  0,  0,  0,  0
};

int16_t knightSquareTable[64] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50,
};

int16_t bishopSquareTable[64] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -20,-10,-10,-10,-10,-10,-10,-20,
};

int16_t rookSquareTable[64] = {
    0,  0,  0,  0,  0,  0,  0,  0,
    5, 10, 10, 10, 10, 10, 10,  5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    0,  0,  0,  5,  5,  0,  0,  0
};

int16_t queenSquareTable[64] = {
    -20,-10,-10, -5, -5,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -5,  0,  5,  5,  5,  5,  0, -5,
    0,  0,  5,  5,  5,  5,  0, -5,
    -10,  5,  5,  5,  5,  5,  0,-10,
    -10,  0,  5,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
};

int16_t kingSquareTable[64] = {
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -20,-30,-30,-40,-40,-30,-30,-20,
    -10,-20,-20,-20,-20,-20,-20,-10,
    20, 20,  0,  0,  0,  0, 20, 20,
    20, 30, 10,  0,  0, 10, 30, 20
};

int16_t pawnEndgameSquareTable[64] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    60, 60, 60, 60, 60, 60, 60, 60,
    45, 45, 45, 45, 45, 45, 45, 45,
    30, 30, 30, 30, 30, 30, 30, 30,
    15, 15, 15, 15, 15, 15, 15, 15,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

int16_t kingEndgameSquareTable[64] = {
    -50,-40,-30,-20,-20,-30,-40,-50,
    -30,-20,-10,  0,  0,-10,-20,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 30, 40, 40, 30,-10,-30,
    -30,-10, 20, 30, 30, 20,-10,-30,
    -30,-30,  0,  0,  0,  0,-30,-30,
    -50,-30,-30,-30,-30,-30,-30,-50
};

int16_t EvaluatePos(GameState* gs)
{
    int16_t eval = 0;

    uint8_t locs[10];
    uint8_t locsLen;

    uint8_t pieceLeft = __builtin_popcountll(gs->bbs[allP]);
    float ratio = (float)pieceLeft / 32;

    locsLen = OnesFromBBToArr(gs->bbs[wp], locs);
    eval += locsLen * 100;
    for (uint8_t i = 0; i < locsLen; i++) {
        eval += ratio * pawnSquareTable[63 - locs[i]] + (1 - ratio) * pawnEndgameSquareTable[63 - locs[i]];
    }
    locsLen = OnesFromBBToArr(gs->bbs[wn], locs);
    eval += locsLen * 300;
    for (uint8_t i = 0; i < locsLen; i++) {
        eval += knightSquareTable[63 - locs[i]];
    }
    locsLen = OnesFromBBToArr(gs->bbs[wb], locs);
    eval += locsLen * 320;
    for (uint8_t i = 0; i < locsLen; i++) {
        eval += bishopSquareTable[63 - locs[i]];
    }
    locsLen = OnesFromBBToArr(gs->bbs[wr], locs);
    eval += locsLen * 500;
    for (uint8_t i = 0; i < locsLen; i++) {
        eval += rookSquareTable[63 - locs[i]];
    }
    locsLen = OnesFromBBToArr(gs->bbs[wq], locs);
    eval += locsLen * 900;
    for (uint8_t i = 0; i < locsLen; i++) {
        eval += queenSquareTable[63 - locs[i]];
    }
    locsLen = OnesFromBBToArr(gs->bbs[wk], locs);
    for (uint8_t i = 0; i < locsLen; i++) {
        eval += ratio * kingSquareTable[63 - locs[i]] + (1 - ratio) * kingEndgameSquareTable[63 - locs[i]];
    }

    locsLen = OnesFromBBToArr(gs->bbs[bp], locs);
    eval -= locsLen * 100;
    for (uint8_t i = 0; i < locsLen; i++) {
        eval -= ratio * pawnSquareTable[locs[i]] + (1 - ratio) * pawnEndgameSquareTable[locs[i]];
    }
    locsLen = OnesFromBBToArr(gs->bbs[bn], locs);
    eval -= locsLen * 300;
    for (uint8_t i = 0; i < locsLen; i++) {
        eval -= knightSquareTable[locs[i]];
    }
    locsLen = OnesFromBBToArr(gs->bbs[bb], locs);
    eval -= locsLen * 320;
    for (uint8_t i = 0; i < locsLen; i++) {
        eval -= bishopSquareTable[locs[i]];
    }
    locsLen = OnesFromBBToArr(gs->bbs[br], locs);
    eval -= locsLen * 500;
    for (uint8_t i = 0; i < locsLen; i++) {
        eval -= rookSquareTable[locs[i]];
    }
    locsLen = OnesFromBBToArr(gs->bbs[bq], locs);
    eval -= locsLen * 900;
    for (uint8_t i = 0; i < locsLen; i++) {
        eval -= queenSquareTable[locs[i]];
    }
    locsLen = OnesFromBBToArr(gs->bbs[bk], locs);
    for (uint8_t i = 0; i < locsLen; i++) {
        eval -= ratio * kingSquareTable[locs[i]] + (1 - ratio) * kingEndgameSquareTable[locs[i]];
    }

    return eval;
}

void OrderMoves(GameState* gs, Move* allMoves, uint8_t allMovesLen)
{
    int16_t moveScores[allMovesLen];
    int16_t values[] = {100, 300, 320, 500, 900, 0};

    int8_t selectedPiece = -1;
    int8_t targetPiece = -1;

    for (uint8_t i = 0; i < allMovesLen; i++) {
        moveScores[i] = 0;

        for (uint8_t j = gs->wtm*6; j < 6 + gs->wtm*6; j++) {
            if (gs->bbs[i] & (1ULL << allMoves[i].endSq)) {
                targetPiece = j;
                break;
            }
        }

        if (targetPiece != -1) {
            for (uint8_t j = 6 - gs->wtm*6; j < 12 - gs->wtm*6; j++) {
                if (gs->bbs[i] & (1ULL << allMoves[i].startSq)) {
                    selectedPiece = j;
                    break;
                }
            }
            moveScores[i] += 10 * values[targetPiece - gs->wtm*6] - values[selectedPiece - 6 + gs->wtm*6];
        }
    }

    SortMoves(allMoves, allMovesLen, moveScores);
}

void SortMoves(Move* allMoves, uint8_t allMovesLen, int16_t* moveScores)
{
    // bubble sort
    for (uint8_t i = 0; i < allMovesLen - 1; i++) {
        int16_t maxScore = -32768;
        uint8_t maxIndex = -1;

        for (uint8_t j = i; j < allMovesLen; j++) {
            if (moveScores[j] > maxScore) {
                maxScore = moveScores[j];
                maxIndex = j;
            }
        }

        int8_t temp = moveScores[i];
        moveScores[i] = moveScores[maxIndex];
        moveScores[maxIndex] = temp;

        Move mtemp = allMoves[i];
        allMoves[i] = allMoves[maxIndex];
        allMoves[maxIndex] = mtemp;
    }
}