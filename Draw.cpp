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
    DrawRectangle(static_cast<int>(floopy.rec.x), static_cast<int>(floopy.rec.y), static_cast<int>(floopy.rec.width), static_cast<int>(floopy.rec.height), BLUE);
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
    DrawText(scoreText, (screenWidth - MeasureText(scoreText, 20)) / 2, 100 + rank * 30, 20, YELLOW);
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
    DrawRectangleRec(button.rect, isHighlighted ? LIGHTGRAY : BLACK);
    DrawText(button.text, (int)button.rect.x + 70, (int)button.rect.y + 10, 20, RED);
}



