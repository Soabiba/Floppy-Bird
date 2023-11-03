#include "raylib.h"
#include "Level.h"

void Level::De_Initialization()
{
    DeSound();
    DeTexture();
 
    activePipes.clear();
    collectibles.clear();
    
    CloseAudioDevice();

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

}

void Level::DeSound() {
    UnloadSound(hitSound);
    UnloadSound(gameOverSound);
    UnloadSound(hoveringSound);
}

void Level::DeTexture() {
    UnloadTexture(backgroundImage);
    UnloadTexture(pipeImage);
    UnloadTexture(mainbackgroundImage);
    UnloadTexture(endbackgroundImage);
    UnloadTexture(highscorebg);
}