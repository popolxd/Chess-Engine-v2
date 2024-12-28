#ifndef TEXTURES_H
#define TEXTURES_H

#include <raylib.h>

#define TRect(x, y) (Rectangle){64*x, 64*y, 64, 64}

extern Texture2D chessPieces;
extern Rectangle textRecs[12];

void InitTextures();

#endif