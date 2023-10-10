#include "raylib.h"
#include "Level.h"

void Level::Resources()
{
	//---------------Textures------------------------------------------------
	

	//Upload textures for Game

	backgroundImage = LoadTexture("./Source/Assets/Background_Asset.png");
	pipeImage = LoadTexture("./Source/Assets/Pipe_Asset.png");
	mainbackgroundImage = LoadTexture("./Source/Assets/mainmenubg.png");
	endbackgroundImage = LoadTexture("./Source/Assets/endgame.png");
	highscorebg = LoadTexture("./Source/Assets/highscorebg.png");
	
	hitSound = LoadSound("./Source/Assets/Hitting.mp3");
	gameOverSound = LoadSound("./Source/Assets/gameOver.mp3");
	hoveringSound = LoadSound("./Source/Assets/hovering sound.mp3");
}