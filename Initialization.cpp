#include "raylib.h"
#include "Level.h"

//#include <fstream>
#include <vector>



void Level::Initialization()
{

    pipes.clear();
    collectibles.clear();

    gameState = MENU;

    highscore.score = 0;
    Time = GetTime();

	gameOver = false;
	
    

    playButton = { { (float) screenWidth / 2 - 100, (float)screenHeight / 2 - 25, 200, 50 }, "Play", false };
    highscoreButton = { { (float) screenWidth / 2 - 100, (float)screenHeight / 2 + 50, 200, 50 }, "High Score", false };
    exitButton = { { (float) screenWidth / 2 - 100, (float) screenHeight / 2 + 125, 200, 50 }, "Exit", false };
    backButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 50, 200, 50 }, "Back", false };
    retryButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 125, 200, 50 }, "Retry", false };
    backToMenuButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 200, 200, 50 }, "Menu", false };




	// initialiazation of "floopy"
    floopy.isDead = false;
	floopy.rec.x = 100;  
	floopy.rec.y = (screenHeight - floopy.rec.height) / 2;  
    floopy.speed = 5;


    

    int gapBetweenRectangles = 150; 
    int floopyY = screenHeight / 2; 


   
    for (int i = 0; i < 5; i++)
    {
        
        int topRectHeight = GetRandomValue(100, screenHeight - gapBetweenRectangles - 100);

        Pipes topPipes = {};
        topPipes.size = { (float) screenWidth + i * 200, 0, 50, (float) topRectHeight };
        topPipes.velocity = { -5, 0 };
        topPipes.isDead = false;
        topPipes.isScored = false;
        pipes.push_back(topPipes);

       
        int bottomRectY = topRectHeight + gapBetweenRectangles;

        Pipes bottomPipes = {};
        bottomPipes.size = { (float) screenWidth + i * 200, (float) bottomRectY, 50, (float)screenHeight - bottomRectY };
        bottomPipes.velocity = { -5, 0 };
        bottomPipes.isDead = false;
        bottomPipes.isScored = false;
        pipes.push_back(bottomPipes);

    }

}





