#include "Level.h"
#include "raylib.h"

#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>


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

        double currentTime = GetTime();
        passedTime = currentTime - Time;

        timeSinceLastPipeSpawn += passedTime;

        floopyInput();

        UpdatePipes();
        ManagePipes();

        endGameInteractions();
        collisionAndScore();

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


void Level::endGameInteractions() {

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

    }
}


void Level::collisionAndScore() {

    for (const Pipe& pipe : activePipes) {


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
}


void Level::floopyInput() {
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

                HighScore newHighScore = {};
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

        // Update the pipe's position 
        pipe.size.x += pipe.velocity.x;

        // Check if the pipe has gone off-screen
        if (pipe.size.x + pipe.size.width < 0) {
            it = activePipes.erase(it); // delete off-screen pipe
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

    const double pipeSpawnInterval = 100.0; 
    return timeSinceLastPipeSpawn >= pipeSpawnInterval;
}

void Level::LoadLevelFromFile(const char* fileName) {
    std::ifstream file(fileName);


    if (file.is_open()) {
       
        activePipes.clear();

        
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string token;
            std::vector<std::string> tokens;

            while (iss) {
                iss >> token;
                tokens.push_back(token);
            }

            
            if (tokens.size() >= 4) {
                Pipe newPipe = {};
                newPipe.size.x = std::stof(tokens[0]);
                newPipe.size.y = std::stof(tokens[1]);
                newPipe.size.width = std::stof(tokens[2]);
                newPipe.size.height = std::stof(tokens[3]);

                
                activePipes.push_back(newPipe);
            }
            else {
                
                std::cerr << "Error: Invalid or incomplete data in level file." << std::endl;
                activePipes.clear(); 
                break;
            }
        }

        file.close();
    }
    else {
        std::cerr << "Error: Could not open the level file." << std::endl;
    }
}


