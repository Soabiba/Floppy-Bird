#include "Level.h"
#include "raylib.h"

#include <fstream>
#include <vector>
#include <algorithm>

void Level::Update()
{


    if (gameState == MENU)
    {

       
        if (CheckCollisionPointRec(GetMousePosition(), playButton.rect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            Initialization();
            gameState = GAME; 
        }
        
        else if (CheckCollisionPointRec(GetMousePosition(), highscoreButton.rect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            gameState = HIGH_SCORE; 
        }
        
        else if (CheckCollisionPointRec(GetMousePosition(), exitButton.rect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            gameState = EXIT; 
        }

        
        playButton.isHighlighted = CheckCollisionPointRec(GetMousePosition(), playButton.rect);
        highscoreButton.isHighlighted = CheckCollisionPointRec(GetMousePosition(), highscoreButton.rect);
        exitButton.isHighlighted = CheckCollisionPointRec(GetMousePosition(), exitButton.rect);

    }
    else if (gameState == GAME)
    {

        //Flooypy Movement

        if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W))
        {
            floopy.rec.y -= floopy.speed;
        }
        else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S))
        {

            floopy.rec.y += floopy.speed;
        }


        if (floopy.rec.y < 0)
        {
            floopy.rec.y = 0;
        }
        else if (floopy.rec.y + floopy.rec.height > screenHeight)
        {
            floopy.rec.y = screenHeight - floopy.rec.height;

        }


        //Pipes

        double currentTime = GetTime();
        passedTime = currentTime - Time;



        for (auto& rect : pipes)
        {
            if (!rect.isDead)
            {
                rect.velocity.x = -5 - static_cast<float>(passedTime * 0.1);
                rect.size.x += rect.velocity.x;


                if (rect.size.x + rect.size.width < 0)
                {

                    rect.size.x = static_cast<float>(screenWidth);


                    rect.isScored = false;
                }
            }
        }

        


        //Collision 
        for (auto& rect : pipes)
        {
            if (!floopy.isDead)
            {
                // Collision between floopy and pipes checker
                if (CheckCollisionRecs(floopy.rec, rect.size))
                {

                    gameOver = true;
                    PlaySound(gameOverSound);

                    gameState = GAME_OVER;

                    printf("game over");
                }


                if (!rect.isDead && !rect.isScored)
                {
                    if (floopy.rec.x > rect.size.x + rect.size.width)
                    {

                        rect.isScored = true;
                        PlaySound(hitSound);
                        highscore.score++;
                    }
                }
            }
        }


    }

    else if (gameState == HIGH_SCORE)
    {
        
        if (CheckCollisionPointRec(GetMousePosition(), backButton.rect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            gameState = MENU; // Transition back to the MENU state
        }
    }
    else if (gameState == GAME_OVER)
    {
   
        if (CheckCollisionPointRec(GetMousePosition(), retryButton.rect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            Initialization();
            gameState = GAME; 
        }
        

        else
           
        if (CheckCollisionPointRec(GetMousePosition(), backToMenuButton.rect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            gameState = MENU; 
        }

        retryButton.isHighlighted = CheckCollisionPointRec(GetMousePosition(), retryButton.rect);
        backToMenuButton.isHighlighted = CheckCollisionPointRec(GetMousePosition(), backToMenuButton.rect);
    }
    else if (gameState == EXIT)
    {

        De_Initialization();
        exit(0); 
       
    }

    
}

