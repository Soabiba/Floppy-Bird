#include "raylib.h"
#include "Level.h"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    SetTargetFPS(60);

    //new file old file broken

    Level level;

    level.Initialization();

    InitWindow(level.screenWidth, level.screenHeight, "Floopy Bird");

    InitAudioDevice();

    level.Resources();
    //put in initialize
    auto sound = LoadSound("./hitHurt.ogg");


    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        level.Update();
        level.Draw();

    }

    level.De_Initialization();


    return 0;
}