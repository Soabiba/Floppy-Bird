#include "raylib.h"
#include "Level.h"
#include <vector>
#include <fstream>

void Level::Initialization()
{
    Variables();
    SetupMenuButtons();
    floopyInit();


    LoadHighScores();

    LoadLevelFromFile("level.txt");

}



void Level::Variables() {
    gameState = MENU;
    highscore.score = 0;
    Time = GetTime();
    gameOver = false;
    activePipes.clear();
    int gapBetweenRectangles = 150;
}

void Level::SetupMenuButtons() {

    playButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 - 25, 200, 50 }, "Play", false };
    highscoreButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 50, 200, 50 }, "High Score", false };
    exitButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 125, 200, 50 }, "Exit", false };
    backButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 125, 200, 50 }, "Back", false };
    retryButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 50, 200, 50 }, "Retry", false };
    backToMenuButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 125, 200, 50 }, "Menu", false };
}

void Level::floopyInit() {
    floopy.isDead = false;
    floopy.rec.x = 100;
    floopy.rec.y = (screenHeight - floopy.rec.height) / 2;
    floopy.speed = 5;
    int floopyY = screenHeight / 2;
}


void Level::LoadHighScores()
{
    highScores.clear(); // Clear the existing high scores

    // Try to open the binary file for reading
    FILE* file = nullptr;
    if (fopen_s(&file, "HighScore.bin", "rb") == 0 && file != nullptr)
    {
        // File exists, read high scores
        for (int i = 0; i < 5; i++)
        {
            HighScore score;
            if (fread(&score, sizeof(HighScore), 1, file) == 1)
            {
                highScores.push_back(score);
            }
        }

        fclose(file);
    }
    else
    {
        // File doesn't exist or couldn't be opened, initialize with default scores
        for (int i = 0; i < 5; i++)
        {
            HighScore score;
            score.name[0] = '\0'; // Empty name
            score.score = 0;
            highScores.push_back(score);
        }

        // Attempt to create and write the default high scores to the file
        if (fopen_s(&file, "HighScore.bin", "wb") == 0 && file != nullptr)
        {
            for (int i = 0; i < 5; i++)
            {
                fwrite(&highScores[i], sizeof(HighScore), 1, file);
            }
            fclose(file);
        }
    }

     name = ""; // Initialize the player's name
    nameConfirmed = false;

}



void Level::LoadLevelFromFile(const char* fileName) {
    std::ifstream file(fileName);

    if (file.is_open()) {
        
        file.close();
    }
    else {
       //debug
    }
}
