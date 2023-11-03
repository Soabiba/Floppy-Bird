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

    SaveLevelToFile("level.txt");

    LoadLevelFromFile("level.txt");

    // ResetHighScores(); this is for you Filippo to ccheck the highscore
}



void Level::Variables() {
    gameState = MENU;
    highscore.score = 0;
    Time = GetTime();
    gameOver = false;
    activePipes.clear();
    currentFrame = 0;
    NUM_FRAMES = 9;
    frameWidth = floopyAnim.width / NUM_FRAMES;
    animationFrameDelay = 5.0f;

}

void Level::SetupMenuButtons() 
{

    playButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 - 25, 200, 50 }, "Play", false };
    highscoreButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 50, 200, 50 }, "High Score", false };
    exitButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 125, 200, 50 }, "Exit", false };
    backButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 125, 200, 50 }, "Back", false };
    retryButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 50, 200, 50 }, "Retry", false };
    backToMenuButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 125, 200, 50 }, "Menu", false };
}

void Level::floopyInit() 
{
    floopy.isDead = false;
    floopy.rec.x = 100;
    floopy.rec.y = (screenHeight - floopy.rec.height) / 2;
    floopy.speed = 5;

}


void Level::LoadHighScores()
{
    highScores.clear();


    FILE* file = nullptr;
    if (fopen_s(&file, "HighScore.bin", "rb") == 0 && file != nullptr)
    {

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

        for (int i = 0; i < 5; i++)
        {
            HighScore score = {};
            score.name[0] = '\0'; // Empty name
            score.score = 0;
            highScores.push_back(score);
        }


        if (fopen_s(&file, "HighScore.bin", "wb") == 0 && file != nullptr)
        {
            for (int i = 0; i < 5; i++)
            {
                fwrite(&highScores[i], sizeof(HighScore), 1, file);
            }
            fclose(file);
        }
    }

    name = "";
    nameConfirmed = false;

}

void Level::SaveLevelToFile(const char* fileName) {
    std::ofstream file(fileName, std::ios::trunc);

    if (file.is_open()) {

        for (const Pipe& pipe : activePipes) {
            file << pipe.size.x << " " << pipe.size.y << " " << pipe.size.width << " " << pipe.size.height << std::endl;
        }

        file.close();
    }
}


void Level::ResetHighScores() {
    highScores.clear();

    // Debug for you Filippo

    for (int i = 0; i < 5; i++) {
        HighScore score = {};
        score.name[0] = '\0';
        score.score = 0;
        highScores.push_back(score);
    }


    WriteHighScoreToFile();
}