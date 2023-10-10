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
      

        DrawButton(backButton, backButton.isHighlighted);
        

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

