#include "raylib.h"
#include "Level.h"


void Level::Draw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (gameState == MENU)
    {
        DrawMenu();
    }
    else if (gameState == GAME)
    {
        DrawGame();
    }
    else if (gameState == HIGH_SCORE)
    {
        DrawHighScoreScreen();
    }
    else if (gameState == WRITE_HIGHSCORE)
    {
        DrawWriteNameScore();
    }
    else if (gameState == GAME_OVER)
    {
        DrawGameOverScreen();
    }

    EndDrawing();
}

// Draw the main menu

void Level::DrawMenu()
{
    DrawTexture(mainbackgroundImage, 0, 0, WHITE);
    DrawButton(playButton, playButton.isHighlighted);
    DrawButton(highscoreButton, highscoreButton.isHighlighted);
    DrawButton(exitButton, exitButton.isHighlighted);
}

// Draw the game screen

void Level::DrawGame()
{
    DrawBackgroundSky();
    DrawBackgroundGround();
    DrawFloopy();
    DrawPipes();
    DrawScore();
}

// Draw the scrolling background

void Level::DrawBackgroundSky()
{
    backgroundsky.offsetX += backgroundsky.scrollSpeedSky;
    if (backgroundsky.offsetX >= sky_parallax.width)
    {
        backgroundsky.offsetX = 0;
    }

    DrawTexture(sky_parallax, -(int)backgroundsky.offsetX, 0, WHITE);
    DrawTexture(sky_parallax, -(int)backgroundsky.offsetX + backgroundImage.width, 0, WHITE);
}

void Level::DrawBackgroundGround()
{
    backgroundground.offsetX += backgroundground.scrollSpeedGround;
    if (backgroundground.offsetX >= ground_parallax.width)
    {
        backgroundground.offsetX = 0;
    }

    // Adjust the Y-coordinate to start from the top of the screen
    int groundY = GetScreenHeight() - ground_parallax.height;

    // Draw ground parallax
    DrawTexture(ground_parallax, -(int)backgroundground.offsetX, groundY, WHITE);
    DrawTexture(ground_parallax, -(int)backgroundground.offsetX + ground_parallax.width, groundY, WHITE);
}

// Draw the Floopy character

void Level::DrawFloopy()
{
    // Define the source rectangle for the animation frame
    Rectangle sourceRect = {
     static_cast<float>(frameWidth * currentFrame),
     0,
     static_cast<float>(frameWidth),
     static_cast<float>(floopyAnim.height)
    };

    Vector2 floopyPosition = {
        floopy.rec.x,
        floopy.rec.y
    };

    // Draw the Floopy character
    DrawTextureRec(floopyAnim, sourceRect, floopyPosition, WHITE);
}

// Draw the player's score

void Level::DrawScore()
{
    DrawText(TextFormat("Score: %d", highscore.score), screenWidth - 200, 10, 30, DARKPURPLE);
}

// Draw the high score screen

void Level::DrawHighScoreScreen()
{
    DrawTexture(highscorebg, 0, 0, WHITE);
    DrawHighScores();
    DrawButton(backButton, backButton.isHighlighted);
}

// Draw the writing name

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
        DrawNameEntryScreen();
    }
}

// Draw the name entry screen

void Level::DrawNameEntryScreen()
{
    DrawText("Enter 3 initials and press Enter to confirm.", 240, 140, 20, GRAY);
    DrawTextBox();
}

// Draw the text box for entering player initials

void Level::DrawTextBox()
{
    DrawRectangleRec(textBox, LIGHTGRAY);

    if (mouseOnText)
    {
        DrawHighlightedTextBox();
    }
    else
    {
        DrawNormalTextBox();
    }
}

// Draw the highlighted text box

void Level::DrawHighlightedTextBox()
{
    DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y), static_cast<int>(textBox.width), static_cast<int>(textBox.height), RED);
    DrawText(name.c_str(), static_cast<int>(textBox.x + 5), static_cast<int>(textBox.y + 8), 40, MAROON);

    if (letterCount < MAX_INPUT_CHARS)
    {
        if (((framesCounter / 20) % 2) == 0)
        {
            DrawText("_", static_cast<int>(textBox.x + 8 + MeasureText(name.c_str(), 40)), static_cast<int>(textBox.y + 12), 40, BLUE);
        }
    }
}

// Draw the normal text box

void Level::DrawNormalTextBox()
{
    DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y), static_cast<int>(textBox.width), static_cast<int>(textBox.height), DARKGRAY);
    DrawText(name.c_str(), static_cast<int>(textBox.x + 5), static_cast<int>(textBox.y + 8), 40, MAROON);
}

// Draw the game over screen

void Level::DrawGameOverScreen()
{
    DrawTexture(endbackgroundImage, 0, 0, WHITE);
    DrawButton(retryButton, retryButton.isHighlighted);
    DrawButton(backToMenuButton, backToMenuButton.isHighlighted);
}

// Draw an entry in the high scores list

void Level::DrawHighScores()
{
    FILE* file = nullptr;
    if (fopen_s(&file, "HighScore.bin", "rb") == 0 && file != nullptr)
    {
        HighScore scores[5];
        fread(scores, sizeof(HighScore), 5, file);
        fclose(file);

        for (int i = 0; i < 5; i++)
        {
            DrawHighScoreEntry(i, scores[i]);
        }
    }
    else
    {
        DrawText("No High Scores Available", (screenWidth - MeasureText("No High Scores Available", 20)) / 2, 100, 20, DARKGRAY);
    }

    DrawButton(backButton, backButton.isHighlighted);
}

// Draw an entry in the high scores list

void Level::DrawHighScoreEntry(int rank, HighScore score)
{
    char scoreText[128];
    snprintf(scoreText, sizeof(scoreText), "High Score #%d: Name: %s, Score: %d", rank + 1, score.name, score.score);
    DrawText(scoreText, (screenWidth - MeasureText(scoreText, 30)) / 2, 150 + rank * 30, 30, SKYBLUE);
}

// Draw the game's pipes

void Level::DrawPipes()
{
    for (const Pipe& pipe : activePipes)
    {
        if (!pipe.isDead)
        {
            DrawRectangleRec(pipe.size, GREEN);
        }
    }
}

// Draw buttons with text

void Level::DrawButton(Button button, bool isHighlighted)
{
    if (isHighlighted)
    {
        PlaySound(hoveringSound);
    }
    // Draw the button
    Color gold = { 255,215,0, 100 };
    DrawRectangleRec(button.rect, isHighlighted ? LIGHTGRAY : gold);

    // Calculate the text position to center it in the button
    int textWidth = MeasureText(button.text, 23);
    int textX = static_cast<int>(button.rect.x + (button.rect.width - textWidth) / 2);
    int textY = static_cast<int>(button.rect.y + (button.rect.height - 23) / 2);

    // Draw the text inside the button
    Color blue = { 25, 25, 112, 200 };
    DrawText(button.text, textX, textY, 23, blue);
}

