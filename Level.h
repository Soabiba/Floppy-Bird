#pragma once
#include <vector>
#include <iostream>
#include "raylib.h"
#include <string>



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
   void Initialization();
   void Resources();
   void Update();
   void Draw();
   void De_Initialization();
   
 

    int screenWidth = 1250;
    int screenHeight = 600;

private:
    
    GameState gameState;
    bool gameOver;
    bool mainScreen;

    double Time;  
    double passedTime;



    void Variables();
    void SetupMenuButtons();
    void floopyInit();


    void DeSound();
    void DeTexture();

    void UploadSound();
    void UploadTextures();


   



    struct Button
    {
        Rectangle rect;
        const char* text;
        bool isHighlighted;
    }; Button playButton, highscoreButton, exitButton, backButton, retryButton, backToMenuButton;

    void DrawButton(Button button, bool isHighlighted);


    struct Background {
        float scrollSpeed = 2.0f;   
        float offsetX = 0.0f;       

    }; Background background;

   
    struct Collectibles {
        Rectangle size;
        Vector2 velocity;
        bool isDead;
    }; std::vector<Collectibles> collectibles;

    struct Pipe {
        Rectangle size;    // Position and size of the pipe
        Vector2 velocity;  // Velocity of the pipe
        bool isDead;       // Flag to track if the pipe is off-screen
        bool isScored;     // Flag to track if the pipe has been scored
    };

    std::vector<Pipe> pipes;
    const int maxActivePipes = 14; // Adjust the limit as needed
    std::vector<Pipe> activePipes;


   

    struct Floopy
    {
        Rectangle rec = { 0,0,40,40};
        int speed = 200;
        bool isDead;
    }; Floopy floopy;

    int floopyY;

    struct HighScore
    {
        char name[4];
        int score;
    }; HighScore highscore;

    std::vector<HighScore> highScores; 

    void LoadHighScores();
   // void DisplayHighScores();//debugging
    void DrawHighScores();
    void LoadLevelFromFile(const char* fileName);
    void SaveLevelToFile(const char* fileName);

#define MAX_INPUT_CHARS 3

    int letterCount = 0;

    Rectangle textBox = { screenWidth / 2.0f - 100, 180, 225, 50 };

    bool mouseOnText = false;

    // char nameCharArray[MAX_INPUT_CHARS + 1] = "\0";     
    std::string name;

    int framesCounter = 0;
   



    //std::string playerName; // To store the player's name
    bool nameConfirmed;

    void WriteHighScoreToFile();
    void WriteName();
    void DrawWriteNameScore();

    void DrawMenu();
    void DrawGame();
    void DrawHighScoreScreen();
    void DrawGameOverScreen();
    void DrawBackground();
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

    const double pipeSpawnInterval = 2.0;  // Adjust this interval as needed
    double timeSinceLastPipeSpawn = 0.0;    // Track time since the last pipe spawn
    const int gapBetweenRectangles = 150; // You can adjust the gap size as needed



    // Textures
    Texture2D backgroundImage;  // Background Image 
    Texture2D pipeImage; // Pipe Image
    Texture2D mainbackgroundImage;
    Texture2D endbackgroundImage;
    Texture2D highscorebg;

    Sound hitSound;
    Sound gameOverSound;
    Sound hoveringSound;
};
