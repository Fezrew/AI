#include "raylib.h"
#include "MoveBehaviour.h"
#include "Agent.h"
#include "NodeMap.h"
#include <string>

NodeMap* map = nullptr;
float hungerCap = 600;
float thirstCap = 300;
bool hungry = false;
bool thirsty = false;

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

#pragma region Hunger/Thirst Coding
		if (IsKeyDown(KEY_A))
		{
			move->Seek(&map->WorldNode[2][4]);
		}
		else if (IsKeyDown(KEY_S))
		{
			move->Seek(&map->WorldNode[13][4]);
		}

		if (thirst <= 150)
		{
			thirsty = true;
		}
		if (hunger <= 450)
		{
			hungry = true;
		}

		if (hungry || thirsty)
		{
			move->canWander = false;
			if (thirsty)
			{
				if (move->theTrailWeBlaze.size() == 0)
				{
					move->Seek(&map->WorldNode[2][4]);
				}

				if (thirst >= thirstCap)
				{
					thirsty = false;
				}
			}
			else if (!thirsty && hungry)
			{
				if (move->theTrailWeBlaze.size() == 0)
				{
					move->Seek(&map->WorldNode[13][4]);
				}
				if (hunger >= hungerCap)
				{
					hungry = false;
				}
			}
		}
		else if (!hungry && !thirsty)
		{
			move->canWander = true;
		}

		move->Update(boy, deltaTime);
		boy->Update(deltaTime);

		if (boy->GetPosition().x <= map->WorldNode[1][4].position.x + 20 && boy->GetPosition().x >= map->WorldNode[1][4].position.x - 20)
		{
			if (boy->GetPosition().y <= map->WorldNode[1][4].position.y + 20 && boy->GetPosition().y >= map->WorldNode[1][4].position.y - 20)
			{
				thirst += deltaTime * 10;
			}
		}
		else
		{
			thirst -= deltaTime;
		}

		if (boy->GetPosition().x <= map->WorldNode[14][4].position.x + 20 && boy->GetPosition().x >= map->WorldNode[14][4].position.x - 20)
		{
			if (boy->GetPosition().y <= map->WorldNode[14][4].position.y + 20 && boy->GetPosition().y >= map->WorldNode[14][4].position.y - 20)
			{
				hunger += deltaTime * 10;
			}
		}
		else
		{
			hunger -= deltaTime;
		}
#pragma endregion

#pragma region Drawing
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

		char buffer[4];
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
#pragma endregion
	}

	delete map;
	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}