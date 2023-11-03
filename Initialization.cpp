#include "raylib.h"
#include "Level.h"
#include <vector>
#include <fstream>

// Initialize the game
void Level::Initialization()
{
    Variables();  // Set initial game variables
    SetupMenuButtons();  // Set up buttons for the main menu
    floopyInit();  // Initialize the Floopy character

    LoadHighScores();  // Load high scores from a file

    SaveLevelToFile("level.txt");  // Save the current level state

    LoadLevelFromFile("level.txt");  // Load the level from a file

    // Debugging: Reset the high scores
    // ResetHighScores();
}

// Initialize game variables
void Level::Variables()
{
    gameState = MENU;  // Set the initial game state to MENU
    highscore.score = 0;  // Initialize the player's score
    Time = GetTime();
    gameOver = false;  // Flag to track if the game is over
    activePipes.clear();  // Clear the list of active pipes
    currentFrame = 0;  // Current frame for animation
    NUM_FRAMES = 9;  // Total frames for the Floopy animation
    frameWidth = floopyAnim.width / NUM_FRAMES;  // Calculate frame width
    animationFrameDelay = 5.0f;  // Delay between animation frames
}

// Set up menu buttons
void Level::SetupMenuButtons()
{
    playButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 - 25, 200, 50 }, "Play", false };
    highscoreButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 50, 200, 50 }, "High Score", false };
    exitButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 125, 200, 50 }, "Exit", false };
    backButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 125, 200, 50 }, "Back", false };
    retryButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 50, 200, 50 }, "Retry", false };
    backToMenuButton = { { (float)screenWidth / 2 - 100, (float)screenHeight / 2 + 125, 200, 50 }, "Menu", false };
}

// Initialize Floopy character
void Level::floopyInit()
{
    floopy.isDead = false;  // Floopy is alive
    floopy.rec.x = 100;  // Initial X position
    floopy.rec.y = (screenHeight - floopy.rec.height) / 2;  // Center Y position
    floopy.speed = 5;  // Floopy's movement speed
}

// Load high scores from a file
void Level::LoadHighScores()
{
    highScores.clear();  // Clear the list of high scores

    FILE* file = nullptr;
    if (fopen_s(&file, "HighScore.bin", "rb") == 0 && file != nullptr)
    {
        // Read high scores from the file
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
        // Initialize high scores with default values
        for (int i = 0; i < 5; i++)
        {
            HighScore score = {};
            score.name[0] = '\0';  // Empty name
            score.score = 0;  // Score is zero
            highScores.push_back(score);
        }

        if (fopen_s(&file, "HighScore.bin", "wb") == 0 && file != nullptr)
        {
            // Write default high scores to the file
            for (int i = 0; i < 5; i++)
            {
                fwrite(&highScores[i], sizeof(HighScore), 1, file);
            }
            fclose(file);
        }
    }

    name = "";  // Initialize player's name
    nameConfirmed = false;
}

// Save the current level to a file
void Level::SaveLevelToFile(const char* fileName)
{
    std::ofstream file(fileName, std::ios::trunc);

    if (file.is_open())
    {
        // Save the positions and sizes of active pipes
        for (const Pipe& pipe : activePipes)
        {
            file << pipe.size.x << " " << pipe.size.y << " " << pipe.size.width << " " << pipe.size.height << std::endl;
        }

        file.close();
    }
}

// Reset high scores (for debugging)
void Level::ResetHighScores()
{
    highScores.clear();

    // Debug for you Filippo
    for (int i = 0; i < 5; i++)
    {
        HighScore score = {};
        score.name[0] = '\0';  // Empty name
        score.score = 0;  // Score is zero
        highScores.push_back(score);
    }

    // Write the reset high scores to a file
    WriteHighScoreToFile();
}
