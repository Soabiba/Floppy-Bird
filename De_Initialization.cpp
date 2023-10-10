#include "raylib.h"
#include "Level.h"

void Level::De_Initialization()
{

    UnloadTexture(backgroundImage);
    UnloadTexture(pipeImage);
    UnloadTexture(mainbackgroundImage);
    UnloadTexture(endbackgroundImage);
    UnloadTexture(highscorebg);

    UnloadSound(hitSound);
    UnloadSound(gameOverSound);
    UnloadSound(hoveringSound);

    pipes.clear();
    collectibles.clear();
    
    CloseAudioDevice();

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

}