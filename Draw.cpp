
#include "raylib.h"
#include "Level.h"

void Level::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);


    if (gameState == MENU)
    {
        // Draw the menu screen

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
        DrawRectangle(floopy.rec.x, floopy.rec.y, floopy.rec.width, floopy.rec.height, BLUE);


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
        DrawText(TextFormat("Score: %d", highscore.score), screenWidth - 200, 10, 30, YELLOW);
    }
    else if (gameState == HIGH_SCORE)
    {
        
      

        DrawButton(backButton, false); 
        

    }
    else if (gameState == GAME_OVER)
    {
       
        DrawButton(retryButton, retryButton.isHighlighted);

       
        DrawButton(backToMenuButton, backButton.isHighlighted);

        
    }

    
    EndDrawing();


   
}

void Level::DrawButton(Button button, bool isHighlighted)
{
    
    DrawRectangleRec(button.rect, isHighlighted ? LIGHTGRAY : BLACK);

   
    DrawText(button.text, button.rect.x + 70, button.rect.y + 10, 20, RED);
}
