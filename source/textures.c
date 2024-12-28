#include "textures.h"

Texture2D chessPieces;
Rectangle textRecs[12] = {
    TRect(5, 0), TRect(3, 0), TRect(4, 0), TRect(2, 0), TRect(1, 0), TRect(0, 0),
    TRect(5, 1), TRect(3, 1), TRect(4, 1), TRect(2, 1), TRect(1, 1), TRect(0, 1)
};

void InitTextures()
{
    chessPieces = LoadTexture("resources/chessPieces.png");
}