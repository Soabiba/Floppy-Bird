// Include necessary headers
#include "raylib.h"
#include "Level.h"

// Load game resources (sounds and textures)
void Level::Resources()
{
    UploadSound();    // Load game sounds
    UploadTextures(); // Load game textures
}

// Load game sounds
void Level::UploadSound()
{
    // Load sound effects from the specified file paths
    hitSound = LoadSound("./Source/Assets/Hitting.mp3");
    gameOverSound = LoadSound("./Source/Assets/gameOver.mp3");
    hoveringSound = LoadSound("./Source/Assets/hovering sound.mp3");
}

// Load game textures
void Level::UploadTextures()
{
    // Load textures from the specified image file paths
    backgroundImage = LoadTexture("./Source/Assets/Background_Asset.png");
    floopyAnim = LoadTexture("./Source/Assets/floopy.png");
    mainbackgroundImage = LoadTexture("./Source/Assets/mainmenubg.png");
    endbackgroundImage = LoadTexture("./Source/Assets/endgame.png");
    highscorebg = LoadTexture("./Source/Assets/highscorebg.png");
    sky_parallax = LoadTexture("./Source/Assets/Background_Asset sky.png");
    ground_parallax = LoadTexture("./Source/Assets/Background_Asset ground.png");
}
