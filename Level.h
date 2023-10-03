#pragma once
#include <vector>
#include "raylib.h"

enum GameState
{
    MENU,
    GAME,
    HIGH_SCORE,
    GAME_OVER,
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


    // Textures
    Texture2D backgroundImage;  // Background Image 

    Texture2D pipeImage; // Pipe Image
    
};
