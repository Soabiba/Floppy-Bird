#include "raylib.h"
#include "Level.h"

void Level::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);


    if (gameState == MENU)
    {
        // Draw the menu screen
        DrawTexture(mainbackgroundImage, 0, 0, WHITE);

        // Draw the "Play" button with highlight
        DrawButton(playButton, playButton.isHighlighted);

        // Draw the "High Score" button with highlight
        DrawButton(highscoreButton, highscoreButton.isHighlighted);

        // Draw the "Exit" button with highlight
        DrawButton(exitButton, exitButton.isHighlighted);


    }

    else if (gameState == GAME)
    {
       

        //-------- Background ----------------------------------------------------------------------------------------

        //Background Movement
        background.offsetX += background.scrollSpeed;

        if (background.offsetX >= backgroundImage.width) background.offsetX = 0;

        // Draw Background Image
        DrawTexture(backgroundImage, -(int)background.offsetX, 0, WHITE);
        // Redraw the image to create loop
        DrawTexture(backgroundImage, -(int)background.offsetX + backgroundImage.width, 0, WHITE);


        //DrawTexture(floopyTexture, floopy.rec.x, floopy.rec.y, WHITE);
        DrawRectangle(static_cast<int>(floopy.rec.x), static_cast<int>(floopy.rec.y), static_cast<int>(floopy.rec.width), static_cast<int>(floopy.rec.height), BLUE);


        //pipes
        for (const auto& rect : pipes)
        {
            if (!rect.isDead)
            {
                DrawRectangleRec(rect.size, GREEN);
                // DrawTexture(pipeImage, rect.size.x, rect.size.y, WHITE);
            }
        }

        // Draw the score
        DrawText(TextFormat("Score: %d", highscore.score), screenWidth - 200, 10, 30, DARKPURPLE);
    }
    else if (gameState == HIGH_SCORE)
    {
        DrawTexture(highscorebg, 0, 0, WHITE);
      
        DrawHighScores();

        DrawButton(backButton, backButton.isHighlighted);
        

    }
    else if(gameState == WRITE_HIGHSCORE)
    { 
        DrawWriteNameScore();
    }
    else if (gameState == GAME_OVER)
    {
        DrawTexture(endbackgroundImage, 0, 0, WHITE);

        DrawButton(retryButton, retryButton.isHighlighted);
       
        DrawButton(backToMenuButton, backToMenuButton.isHighlighted);

        
    }

    
    EndDrawing();


   
}

void Level::DrawButton(Button button, bool isHighlighted)
{
    if (isHighlighted)
    {
        PlaySound(hoveringSound);
    }
    // Draw the button
    Color blue = { 51,42,95, 200};
    DrawRectangleRec(button.rect, isHighlighted ? LIGHTGRAY : blue);

    // Calculate the text position to center it in the button
    int textWidth = MeasureText(button.text, 23);
    int textX = static_cast<int>(button.rect.x + (button.rect.width - textWidth) / 2);
    int textY = static_cast<int>(button.rect.y + (button.rect.height - 23) / 2);

    // Draw the text inside the button
    Color green = { 0, 250, 154, 200 };
    DrawText(button.text, textX, textY, 23, green);
}

void Level::DrawHighScores()
{
    // Try to open the binary file for reading
    FILE* file = nullptr;
    if (fopen_s(&file, "HighScore.bin", "rb") == 0 && file != nullptr)
    {
        HighScore scores[5];

        fread(scores, sizeof(HighScore), 5, file);

        fclose(file);

        // Now, display the high scores in the high score screen
        for (int i = 0; i < 5; i++)
        {
            char scoreText[128];
            snprintf(scoreText, sizeof(scoreText), "High Score #%d: Name: %s, Score: %d", i + 1, scores[i].name, scores[i].score);
            DrawText(scoreText, (screenWidth - MeasureText(scoreText, 20)) / 2, 100 + i * 30, 20, YELLOW);
        }
    }
    else
    {
        // File doesn't exist or couldn't be opened, display a message
        DrawText("No High Scores Available", (screenWidth - MeasureText("No High Scores Available", 20)) / 2, 100, 20, DARKGRAY);
    }

    // Display the "Back" button
    DrawButton(backButton, backButton.isHighlighted);
}


void Level::DrawWriteNameScore()
{
    if (nameConfirmed)
    {
        // Display the player's name and score
        std::string playerNameAndScore = "Name: " + name + " Score: " + std::to_string(highscore.score);
        DrawText(playerNameAndScore.c_str(), 240, 140, 20, GRAY);
    }
    else
    {
        DrawText("Enter 3 initials and press Enter to confirm.", 240, 140, 20, GRAY);
        DrawRectangleRec(textBox, LIGHTGRAY);

        if (mouseOnText)
        {
            DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y), static_cast<int>(textBox.width), static_cast<int>(textBox.height), RED);
            DrawText(name.c_str(), static_cast<int>(textBox.x + 5), static_cast<int>(textBox.y + 8), 40, MAROON);

            if (letterCount < MAX_INPUT_CHARS)
            {
                // Draw blinking underscore character
                if (((framesCounter / 20) % 2) == 0)
                {
                    DrawText("_", static_cast<int>(textBox.x + 8 + MeasureText(name.c_str(), 40)), static_cast<int>(textBox.y + 12), 40, BLUE);
                }
            }
           
        }
        else
        {
            DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y), static_cast<int>(textBox.width), static_cast<int>(textBox.height), DARKGRAY);
            DrawText(name.c_str(), static_cast<int>(textBox.x + 5), static_cast<int>(textBox.y + 8), 40, MAROON);
        }
    }
}