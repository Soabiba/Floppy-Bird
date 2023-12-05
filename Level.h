#pragma once
#include <vector>
#include <iostream>
#include "raylib.h"
#include <string>

// Define different game states
enum GameState
{
    MENU,
    GAME,
    HIGH_SCORE,
    GAME_OVER,
    WRITE_HIGHSCORE,
    EXIT
};

class Level
{
public:
    void Initialization(); // Initialize the game
    void Resources();     // Load game resources
    void Update();        // Update game logic
    void Draw();          // Draw game elements
    void De_Initialization(); // Deinitialize and clean up resources

    int screenWidth = 1250;
    int screenHeight = 600;

private:
    GameState gameState;
    bool gameOver;
    bool mainScreen;

    double Time;
    double passedTime;

    // Initialize game variables and setup menu buttons
    void Variables();
    void SetupMenuButtons();
    void floopyInit();

    // Deinitialize game sounds and textures
    void DeSound();
    void DeTexture();

    // Load game sounds and textures
    void UploadSound();
    void UploadTextures();

    // Reset the high scores
    void ResetHighScores();

    // Structure to define buttons
    struct Button
    {
        Rectangle rect;
        const char* text;
        bool isHighlighted;
    };

    Button playButton, highscoreButton, exitButton, backButton, retryButton, backToMenuButton;

    void DrawButton(Button button, bool isHighlighted);

    // Structure for parallax scrolling background
    struct BackgroundSky
    {
        float scrollSpeedSky = 5.0f;
        float offsetX = 0.0f;
    };

    BackgroundSky backgroundsky;

    struct BackgroundGround
    {
        float scrollSpeedGround = 2.0f;
        float offsetX = 0.0f;
    };

    BackgroundGround backgroundground;

    // Structure to define pipes
    struct Pipe
    {
        Rectangle size;    // Position and size of the pipe
        Vector2 velocity;  // Velocity of the pipe
        bool isDead;       // Flag to track if the pipe is off-screen
        bool isScored;     // Flag to track if the pipe has been scored
    };

    std::vector<Pipe> pipes;
    const int maxActivePipes = 14; // Adjust the limit as needed
    std::vector<Pipe> activePipes;

    // Structure for the main character (Floopy)
    struct Floopy
    {
        Rectangle rec = { 0, 0, 40, 40 };
        int speed = 200;
        bool isDead;
    };

    Floopy floopy;
    int floopyY;

    // Structure to store high scores
    struct HighScore
    {
        char name[4];
        int score;
    };

    HighScore highscore;
    std::vector<HighScore> highScores;

    // Load high scores from a file
    void LoadHighScores();
    void DrawHighScores();
    void LoadLevelFromFile(const char* fileName);
    void SaveLevelToFile(const char* fileName);

#define MAX_INPUT_CHARS 3

    int letterCount = 0;
    Rectangle textBox = { screenWidth / 2.0f - 100, 180, 225, 50 };
    bool mouseOnText = false;
    std::string name;
    int framesCounter = 0;
    int currentFrame;
    int NUM_FRAMES;
    int frameWidth;
    bool nameConfirmed;

    void WriteHighScoreToFile();
    void WriteName();
    void DrawWriteNameScore();
    void DrawMenu();
    void DrawGame();
    void DrawHighScoreScreen();
    void DrawGameOverScreen();
    void DrawBackgroundSky();
    void DrawBackgroundGround();
    void DrawFloopy();
    void DrawScore();
    void DrawNameEntryScreen();
    void DrawTextBox();
    void DrawHighlightedTextBox();
    void DrawNormalTextBox();
    void DrawHighScoreEntry(int rank, HighScore score);

    void SpawnPipe();
    void UpdatePipes();
    void ManagePipes();
    void DrawPipes();
    bool ShouldSpawnNewPipe();

    void floopyInput();
    void endGameInteractions();
    void collisionAndScore();

    void UpdateFloopyAnimation();
    float animationFrameDelay;

    const double pipeSpawnInterval = 2.0;  // Adjust this interval as needed
    double timeSinceLastPipeSpawn = 0.0;    // Track time since the last pipe spawn
    const int gapBetweenRectangles = 350; // Gap between every individual pipe

    // Textures
    Texture2D backgroundImage;  // Background Image
    Texture2D floopyAnim; // Pipe Image
    Texture2D mainbackgroundImage;
    Texture2D endbackgroundImage;
    Texture2D highscorebg;
    Texture2D sky_parallax;
    Texture2D ground_parallax;

    Sound hitSound;
    Sound gameOverSound;
    Sound hoveringSound;
};
