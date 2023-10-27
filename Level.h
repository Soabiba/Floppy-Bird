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

    struct Pipes
    {
        Rectangle size;
        Vector2 velocity;
        bool isDead;
        bool isScored;
    };  std::vector<Pipes> pipes;
   

    struct Floopy
    {
        Rectangle rec = { 0,0,40,40};
        int speed = 200;
        bool isDead;
    }; Floopy floopy;


    struct HighScore
    {
        char name[4];
        int score;
    }; HighScore highscore;

    std::vector<HighScore> highScores; 

    void LoadHighScores();
    void DisplayHighScores();//debugging
    void DrawHighScores();

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
