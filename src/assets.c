#include "raylib.h"
#include "assets.h"
#include "consts.h"


Texture2D spriteSheet; 

void LoadAssets() {
	Image img = LoadImage("art/pieces.png");
	ImageResizeNN(&img, SQUARE_SIZE * 6, SQUARE_SIZE * 2);
	spriteSheet = LoadTextureFromImage(img);
}

