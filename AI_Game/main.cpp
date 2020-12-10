#include "raylib.h"
#include "MoveBehaviour.h"
#include "Agent.h"
#include "NodeMap.h"
#include <string>

NodeMap* map = nullptr;
float hungerCap = 600;
float thirstCap = 300;

int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 500;
	float hunger = hungerCap;
	float thirst = thirstCap;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------
	map = new NodeMap();

	Agent* boy = new Agent();
	boy->SetPosition({ (float)(screenWidth >> 1), (float)(screenHeight >> 1) });
	boy->SetMaxSpeed(50);

	MoveBehaviour* move = new MoveBehaviour;
	move->targetNode = &map->WorldNode[8][5];
	move->SetDestination(move->targetNode);

	boy->AddBehaviour(move);

	float deltaTime = 0;

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		deltaTime = GetFrameTime();

		if (IsKeyDown(KEY_A))
		{
			move->Seek(&map->WorldNode[2][4]);
		}
		else if (IsKeyDown(KEY_S))
		{
			move->Seek(&map->WorldNode[13][4]);
		}

		move->Update(boy, deltaTime);
		boy->Update(deltaTime);

		thirst -= deltaTime;
		hunger -= deltaTime;

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(RAYWHITE);

		map->DrawGraph();
		if (IsKeyDown(KEY_D))
		{
			DrawCircle(move->targetNode->position.x, move->targetNode->position.y, 15, MAGENTA);
		}
		boy->Draw();

		char buffer[3];
		char output[50];

		strcpy_s(output, "Hunger: ");
		snprintf(buffer, sizeof(buffer), "%d", (int)(hunger / hungerCap * 100));
		strcat_s(output, buffer);
		DrawText(output, 20, 20, 20, RED);

		strcpy_s(output, "Thirst: ");
		snprintf(buffer, sizeof(buffer), "%d", (int)(thirst / thirstCap * 100));
		strcat_s(output, buffer);
		DrawText(output, 200, 20, 20, RED);

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