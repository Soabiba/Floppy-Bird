#include "Draw.h"

void Level::draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (mainScreen)
    {
        //Draw Start Screen
        DrawTexture(Βackground, 0, 0, WHITE);
        DrawText("SPACE ROCKS", screenWidth / 2 - MeasureText("SPACE ROCKS", 30) / 2, screenHeight / 2 - 30, 30, WHITE);
        DrawText("PRESS [ENTER] TO START", screenWidth / 2 - MeasureText("PRESS [ENTER] TO START", 20) / 2, screenHeight / 2 + 20, 20, WHITE);

    }

    else if (gameOver)
    {
        // Draw Game Over Screen
        DrawTexture(Βackground, 0, 0, WHITE);
        DrawText("YOU LOSE!!", GetScreenWidth() / 2 - MeasureText("YOU LOSE!!", 30) / 2, GetScreenHeight() / 2 - 50, 30, RED);
    }

    else
    {
        // Draw the playable Game
        DrawTexture(Βackground, 0, 0, WHITE); //Draw the background

        DrawTexture(Spaceship, (int)player.rec.x, (int)player.rec.y, WHITE); // Draw the Spaceship

        if (shoot.isFired && !shoot.isDead)
        {
            DrawTexture(Shooting, (int)shoot.rec.x, (int)shoot.rec.y, WHITE); // Draw the Missile
        }

        // Draw the meteors
        for (const Enemy& meteor : enemies)
        {
            if (!meteor.isDead)
            {
                DrawTexture(Rock, (int)meteor.rec.x, (int)meteor.rec.y, WHITE); // Draw the meteors when they are not dead
            }
        }

        for (auto& coin : coins)
        {
            if (!coin.isDead)
            {
                DrawTexture(Coins, (int)coin.rec.x, (int)coin.rec.y, WHITE); // Draw the coins when are not dead
            }
        }

        for (auto& scoreDisplay : scoreDisplays)
        {
            DrawText(TextFormat("+%i", scoreDisplay.value), (int)scoreDisplay.position.x, (int)scoreDisplay.position.y, 30, YELLOW);
            scoreDisplay.lifetime--;

            if (scoreDisplay.lifetime <= 0)
            {
                scoreDisplay.isDead = true;
            }
        }

        scoreDisplays.erase(std::remove_if(scoreDisplays.begin(), scoreDisplays.end(), [](ScoreDisplay const& scoreDisplay) { return scoreDisplay.isDead; }), scoreDisplays.end());

        DrawText(TextFormat("Score: %i", score), 10, 10, 20, RAYWHITE); //Display the  score

        // Display the Missile charge
        if (shoot.isFired == false)
        {
            int barWidth = 200;
            int barHeight = 20;
            int barX = (screenWidth - barWidth);
            int barY = 10;

            //Display the green bar going up with the charge
            if (shoot.charge < 100) DrawRectangle(barX, barY, (int)(barWidth * (shoot.charge / 100.0f)), barHeight, YELLOW);
            {
                DrawRectangleLines(barX, barY, barWidth, barHeight, WHITE); // Display the bar limits 
            }

            if (shoot.loaded == true)
            {

                DrawText(TextFormat("READY TO SHOOT"), barX + 8, barY + 2, 20, PINK); //Diplay a Charge sign 
            }
        }
    }
    EndDrawing();
}