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

        timeSinceLastPipeSpawn += passedTime;

        UpdatePipes();
        ManagePipes();


      
                // Collision between floopy and pipes
                for (const Pipe& pipe : activePipes) {
                    if (CheckCollisionRecs(floopy.rec, pipe.size)) {

                        //gameOver = true;
                        PlaySound(gameOverSound);


                        bool isHighScore = false;
                        for (const HighScore& score : highScores)
                        {
                            if (highscore.score > score.score)
                            {
                                isHighScore = true;
                                break;
                            }
                        }

                        if (isHighScore)
                        {

                            name = "";
                            letterCount = 0;

                            gameState = WRITE_HIGHSCORE;


                        }
                        else
                        {
                            gameState = GAME_OVER;
                        }

                    }
                    
                    for (auto& pipe : activePipes) {
                        if (!floopy.isDead) {
                            // Collision between floopy and pipes checker
                            if (CheckCollisionRecs(floopy.rec, pipe.size)) {
                                // Handle collision with the pipe
                                floopy.isDead = true;  // Set the player's state to "dead"
                                PlaySound(gameOverSound);
                            }
                        }

                        if (!pipe.isDead && !pipe.isScored) {
                            if (floopy.rec.x > pipe.size.x + pipe.size.width) {
                                pipe.isScored = true;
                                PlaySound(hitSound);
                                highscore.score++;  // Increase the player's score
                            }
                        }
                    }

                }


                for (Pipe& rect : activePipes) {
                    if (!rect.isDead && !rect.isScored) {
                        if (floopy.rec.x > rect.size.x + rect.size.width) {
                            rect.isScored = true;
                            PlaySound(hitSound);
                            highscore.score++;
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

        backButton.isHighlighted = CheckCollisionPointRec(GetMousePosition(), backButton.rect);
    }
    else if (gameState == GAME_OVER)
    {

   
        if (CheckCollisionPointRec(GetMousePosition(), retryButton.rect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            Initialization();
            gameState = GAME; 
        }
        

        else if (CheckCollisionPointRec(GetMousePosition(), backToMenuButton.rect) && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            gameState = MENU; 
        }

        retryButton.isHighlighted = CheckCollisionPointRec(GetMousePosition(), retryButton.rect);
        backToMenuButton.isHighlighted = CheckCollisionPointRec(GetMousePosition(), backToMenuButton.rect);
    }
    if (gameState == WRITE_HIGHSCORE)
    {
        WriteName();
    }
    else if (gameState == EXIT)
    {

        De_Initialization();
        exit(0); 
       
    }

    
}

void Level::WriteHighScoreToFile()
{
    FILE* file = nullptr;

    if (fopen_s(&file, "HighScore.bin", "wb") == 0 && file != nullptr)
    {
        for (int i = 0; i < 5; i++)
        {
            fwrite(&highScores[i], sizeof(HighScore), 1, file);
        }
        fclose(file);
    }
}

void Level::WriteName()
{

    if (!nameConfirmed)
    {
        if (CheckCollisionPointRec(GetMousePosition(), textBox))
        {
            mouseOnText = true;
            SetMouseCursor(MOUSE_CURSOR_IBEAM);

              // Check for player input to enter their name
             if (IsKeyPressed(KEY_ENTER) && name.size() == 3)
             {
                   nameConfirmed = true;

                    HighScore newHighScore;
                    newHighScore.score = highscore.score;
                    strncpy_s(newHighScore.name, name.c_str(), sizeof(newHighScore.name));

                    // highScores.push_back(newHighScore);

            // Check if the new high score is higher than any existing score
                     bool isHighScore = false;

                 for (int i = 0; i < highScores.size(); i++)
                 {
                      if (newHighScore.score > highScores[i].score)
                     {
                       // Insert the new high score at the appropriate position
                      highScores.insert(highScores.begin() + i, newHighScore);
                      isHighScore = true;
                       break;
                  }
             }

            
            if (!isHighScore && highScores.size() < 5)
            {
                highScores.push_back(newHighScore);
            }

            // Ensure only the top 5 high scores are kept
            if (highScores.size() > 5)
            {
                highScores.pop_back();
            }

           
            WriteHighScoreToFile();

           
            gameState = HIGH_SCORE;
        }
        int key = GetCharPressed();
        while (key > 0 && letterCount < 3)
        {
            name += static_cast<char>(key);
            letterCount++;
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE) && letterCount > 0)
        {
            letterCount--;
            name.pop_back();
        }
        }
        else
        {
            mouseOnText = false;
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }
    
    }

    
}



void Level::UpdatePipes() {
    for (auto it = activePipes.begin(); it != activePipes.end();) {
        Pipe& pipe = *it;

        // Update the pipe's position based on its velocity
        pipe.size.x += pipe.velocity.x;

        // Check if the pipe has gone off-screen
        if (pipe.size.x + pipe.size.width < 0) {
            it = activePipes.erase(it); // Remove off-screen pipe
        }
        else {
            ++it;
        }
    }
}

void Level::ManagePipes() {
    if (ShouldSpawnNewPipe()) {
        SpawnPipe();
        timeSinceLastPipeSpawn = 0.0;  // Reset the timer
    }
}


void Level::SpawnPipe() {
    if (activePipes.size() < maxActivePipes) {
        int gapSize = 190;  // Set the desired gap size
        int gapPosition = GetRandomValue(gapSize, screenHeight - gapSize);

        Pipe topPipes = {};
        topPipes.size = { (float)screenWidth, 0, 50, (float)gapPosition - gapSize / 2 };
        topPipes.velocity = { -5, 0 };
        topPipes.isDead = false;
        topPipes.isScored = false;
        activePipes.push_back(topPipes);

        Pipe bottomPipes = {};
        bottomPipes.size = { (float)screenWidth, (float)gapPosition + gapSize / 2, 50, (float)screenHeight - gapPosition - gapSize / 2 };
        bottomPipes.velocity = { -5, 0 };
        bottomPipes.isDead = false;
        bottomPipes.isScored = false;
        activePipes.push_back(bottomPipes);
    }
}



bool Level::ShouldSpawnNewPipe() {
   
    const double pipeSpawnInterval = 100.0; // Adjust this value to control the interval
    return timeSinceLastPipeSpawn >= pipeSpawnInterval;
}
