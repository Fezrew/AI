#include "raylib.h"
#include "Agent.h"
#include "NodeMap.h"

int main(int argc, char* argv[])
{
    NodeMap* map = new NodeMap();

    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 500;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    float deltaTime = 0;

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        deltaTime = GetFrameTime();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        map->DrawGraph();
        //DrawText("Click anywhere to set a new target position", 20, 20, 12, RED);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    delete map;
    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}