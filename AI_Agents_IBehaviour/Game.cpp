#include "Game.h"
#include "Agent.h"
#include "KeyboardBehaviour.h"
#include "raylib.h"

Game::Game(unsigned int windowWidth, unsigned int windowHeight, const char *title) 
{
	InitWindow(windowWidth, windowHeight, title);
	SetTargetFPS(60);
}

Game::~Game()
{
}

bool Game::Startup()
{
	m_testAgent = new Agent(RED, 10, { (float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2 });

	m_keyboardBehaviour = new KeyboardBehaviour();
	m_testAgent->AddBehaviour(m_keyboardBehaviour);

	m_agentTexture = LoadTexture("agent.png");
	m_mouseTexture = LoadTexture("nodeTexture.png");

	return true;
}

void Game::Shutdown()
{	
	delete m_testAgent;

	UnloadTexture(m_agentTexture);
	UnloadTexture(m_mouseTexture);

	CloseWindow();        // Close window and OpenGL context
}

void Game::Update(float deltaTime)
{	
	m_testAgent->Update(deltaTime);
}

void Game::Draw()
{
	BeginDrawing();

	ClearBackground(RAYWHITE);

	// Draw the test agent at its current position		
	DrawTexturePro(m_agentTexture,
			// source rect... simply the dimensions of the image to draw
		Rectangle{ 0, 0, (float)m_agentTexture.width, (float)m_agentTexture.height },
			// target rect... the output position and image dimensions
		Rectangle{ m_testAgent->GetPosition().x,
		m_testAgent->GetPosition().y,
		(float)m_agentTexture.width, (float)m_agentTexture.height },
			// offset, the center of the image. This is the reason we're using the DrawTexturePro fuction
		Vector2{ m_agentTexture.width / 2.0f, m_agentTexture.height / 2.0f },

			// rotation and tint
		m_testAgent->GetRotation(), WHITE);

	// Draw the mouse pointer, calculating the offset manually
	DrawTextureEx(m_mouseTexture, Vector2Subtract(GetMousePosition(), Vector2{ m_mouseTexture.width / 2.0f, m_mouseTexture.height / 2.0f }), 0, 1.0f, WHITE);

	// Draw info text
	DrawText("Use WASD to move the agent by using the keyboard Behaviour", 50, 50, 14, LIGHTGRAY);

	EndDrawing();
}