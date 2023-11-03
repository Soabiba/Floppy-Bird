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

void Level::DrawMenu()
{
    DrawTexture(mainbackgroundImage, 0, 0, WHITE);
    DrawButton(playButton, playButton.isHighlighted);
    DrawButton(highscoreButton, highscoreButton.isHighlighted);
    DrawButton(exitButton, exitButton.isHighlighted);
}

void Level::DrawGame()
{
    DrawBackground();
    DrawFloopy();
    DrawPipes();
    DrawScore();
}

void Level::DrawBackground()
{
    background.offsetX += background.scrollSpeed;
    if (background.offsetX >= backgroundImage.width)
    {
        background.offsetX = 0;
    }

    DrawTexture(backgroundImage, -(int)background.offsetX, 0, WHITE);
    DrawTexture(backgroundImage, -(int)background.offsetX + backgroundImage.width, 0, WHITE);
}

void Level::DrawFloopy()
{

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

    DrawTextureRec(floopyAnim, sourceRect, floopyPosition, WHITE);




    //  DrawRectangle(static_cast<int>(floopy.rec.x), static_cast<int>(floopy.rec.y), static_cast<int>(floopy.rec.width), static_cast<int>(floopy.rec.height), BLUE);
}

void Level::DrawScore()
{
    DrawText(TextFormat("Score: %d", highscore.score), screenWidth - 200, 10, 30, DARKPURPLE);
}

void Level::DrawHighScoreScreen()
{
    DrawTexture(highscorebg, 0, 0, WHITE);
    DrawHighScores();
    DrawButton(backButton, backButton.isHighlighted);
}

void Level::DrawWriteNameScore()
{
    if (nameConfirmed)
    {
        std::string playerNameAndScore = "Name: " + name + " Score: " + std::to_string(highscore.score);
        DrawText(playerNameAndScore.c_str(), 240, 140, 20, GRAY);
    }
    else
    {
        DrawNameEntryScreen();
    }
}

void Level::DrawNameEntryScreen()
{
    DrawText("Enter 3 initials and press Enter to confirm.", 240, 140, 20, GRAY);
    DrawTextBox();
}

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

void Level::DrawNormalTextBox()
{
    DrawRectangleLines(static_cast<int>(textBox.x), static_cast<int>(textBox.y), static_cast<int>(textBox.width), static_cast<int>(textBox.height), DARKGRAY);
    DrawText(name.c_str(), static_cast<int>(textBox.x + 5), static_cast<int>(textBox.y + 8), 40, MAROON);
}

void Level::DrawGameOverScreen()
{
    DrawTexture(endbackgroundImage, 0, 0, WHITE);
    DrawButton(retryButton, retryButton.isHighlighted);
    DrawButton(backToMenuButton, backToMenuButton.isHighlighted);
}

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

void Level::DrawHighScoreEntry(int rank, HighScore score)
{
    char scoreText[128];
    snprintf(scoreText, sizeof(scoreText), "High Score #%d: Name: %s, Score: %d", rank + 1, score.name, score.score);
    DrawText(scoreText, (screenWidth - MeasureText(scoreText, 30)) / 2, 150 + rank * 30, 30, YELLOW);
}

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

