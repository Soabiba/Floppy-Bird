#include "raylib.h"
#include "Level.h"

void Level::Resources()
{
	UploadSound();
	UploadTextures();
}

void Level::UploadSound() {
	hitSound = LoadSound("./Source/Assets/Hitting.mp3");
	gameOverSound = LoadSound("./Source/Assets/gameOver.mp3");
	hoveringSound = LoadSound("./Source/Assets/hovering sound.mp3");
}

void Level::UploadTextures() {
	backgroundImage = LoadTexture("./Source/Assets/Background_Asset.png");
	floopyAnim = LoadTexture("./Source/Assets/floopy.png");
	mainbackgroundImage = LoadTexture("./Source/Assets/mainmenubg.png");
	endbackgroundImage = LoadTexture("./Source/Assets/endgame.png");
	highscorebg = LoadTexture("./Source/Assets/highscorebg.png");
}
