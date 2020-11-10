/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/
#include <cstdlib>

#include "raylib.h"
#include "raymath.h"

#include "Agent.h"
#include "Circle.h"
#include "Seek.h"
#include "Avoid.h"
#include "Flee.h"

Agent* m_seeker;
static std::vector<Agent*> agents;

std::vector<IBehaviour*> Behaviours;
std::vector<Circle*> circles;

int mouse_x = 0;
int mouse_y = 0;
Vector2 mouse_xy;

int main(int argc, char* argv[])
{

	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - Flocking AI");

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Setup scenario
	Vector2 startAt = { (float)screenWidth * 0.5f, ((float)screenHeight * 0.5f) };
	m_seeker = new Agent(RED, 10, startAt);

	Seek* seek = new Seek();
	seek->m_targetPosition = &mouse_xy;

	m_seeker->AddBehaviour(seek);

	Flee* flee = new Flee();
	flee->m_targetPosition = &mouse_xy;

	// Create our agents
	unsigned int agentAmount = 20;
	for (unsigned int i = 0; i < agentAmount; i++)
	{
		Avoid* avoid = new Avoid();
		avoid->m_circles = &circles;
		avoid->m_targetPosition = &m_seeker->GetPosition();

		startAt = { 400.0f + i * 5, 300.0f + i * 5 };
		agents.push_back(new Agent(RED, 10, startAt));
		agents[i]->AddBehaviour(avoid);
		//agents[i]->AddBehaviour(flee);
	}

	//Agent::agents = &agents;

	// Create circles to use as obsticles
	unsigned int circleAmount = rand() % 25;
	for (unsigned int i = 0; i <= circleAmount; i++)
	{
		circles.push_back(new Circle(Vector2{ (float)(rand() % screenWidth), (float)(rand() % screenHeight) }, (float)(rand() % 40)));
	}
	// End setup


	float deltaTime = 0;

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		deltaTime = GetFrameTime();

		if (IsMouseButtonDown(0) == true)
		{
			//GetMousePosition
			  // Update Agents;
			  // Store the mouse position as floats here to conversions don't have to happen else where
			mouse_xy = GetMousePosition();
		}

		m_seeker->Update(deltaTime);

		// update the agents to sense, think, and act
		for (unsigned int i = 0; i < agents.size(); i++)
		{
			agents[i]->Update(deltaTime);
		}

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground({ 0,0,0,255 });

		// Draw Debug
		DrawText("Click anywhere to set a new target position", 20, 20, 12, RED);
		//DrawLine(target.x - 5, target.y, target.x + 5, target.y, BLUE);
		//DrawLine(target.x, target.y - 5, target.x, target.y + 5, BLUE);

		// Draw the circles
		for (auto circle : circles)
		{
			DrawCircle(circle->m_position.x, circle->m_position.y, circle->m_radius, Color{ 0,255,0,255 });
		}

		DrawCircle(m_seeker->GetPosition().x, m_seeker->GetPosition().y, 5, Color{ 255,0,0,255 });

		// Draw the agents at their current position and rotation
		for (auto agent : agents)
		{
			DrawCircle(agent->GetPosition().x, agent->GetPosition().y, 5, Color{ 255,255,0,255 });
		}

		// Draw Agents

		EndDrawing();
		//----------------------------------------------------------------------------------
	}



	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	for (unsigned int i = 0; i < agents.size(); i++)
	{
		delete agents[i];
	}
	agents.clear();

	/*for (unsigned int i = 0; i < Behaviours.size(); i++)
	{
		delete Behaviours[i];
	}
	Behaviours.clear();*/

	for (unsigned int i = 0; i < circles.size(); i++)
	{
		delete circles[i];
	}
	circles.clear();

	return 0;
}