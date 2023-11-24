#include "Game2D.h"
#include "StateManager.h"
#include "Application.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Player.h"
#include "Node.h"
#include <time.h>

Game2D::Game2D(const char* title, int width, int height, bool fullscreen) : Game(title, width, height, fullscreen)
{
	aie::Application* application = aie::Application::GetInstance();

	StateManager::Create(); 
	// Initalise the 2D renderer.
	m_2dRenderer = new aie::Renderer2D();

	// Create some textures for testing.
	
	m_font = new aie::Font("./font/consolas.ttf", 24);
	m_pGrid = new Grid(GRID_SIZE_X /*application->GetWindowWidth() / 40*/, GRID_SIZE_Y /*application->GetWindowHeight() / 40*/);

	srand(time(0));

	// Create a player object.
	//m_Player1 = new Guards(m_pGrid);

	//m_Player2 = new Guards(m_pGrid); 
}

Game2D::~Game2D()
{
	delete States::SearchState;
	delete States::WaitState;
	delete States::WalkState;
	delete States::PatrolState; 

	StateManager::Destroy(); 

	// Delete player.
	delete m_Player1;
	m_Player1 = nullptr;

	//delete m_Player2;
	//m_Player2 = nullptr; 

	// Deleted the textures.
	delete m_font;
	m_font = nullptr;


	// Delete the renderer.
	delete m_2dRenderer;
	m_2dRenderer = nullptr;

	//Delete the grid
	delete m_pGrid; 
	m_pGrid = nullptr; 
}

void Game2D::Update(float deltaTime)
{
	//StateManager::Update(deltaTime); 
	// Update the player.
	//m_Player1->Update(deltaTime);

	//m_Player2->Update(deltaTime); 
	// Input example: Update the camera position using the arrow keys.
	aie::Input* input = aie::Input::GetInstance();
	//float camPosX;
	//float camPosY;

	

	Vector2 v2MousePos;
	v2MousePos.x = input->GetMouseX();
	v2MousePos.y = input->GetMouseY();

	//Path Finding 
	if (input->IsMouseButtonDown(0))
	{
		Node* pMouseNode = m_pGrid->GetNodeByPos(v2MousePos);

		if (pMouseNode)
			pMouseNode->m_bBlocked = true;
	}
	if (input->IsMouseButtonDown(1))
	{
		Node* pMouseNode = m_pGrid->GetNodeByPos(v2MousePos);
		if (pMouseNode)
			pMouseNode->m_bBlocked = false;
	}
	if (input->WasKeyPressed(aie::INPUT_KEY_G))
	{
		if (m_pGrid->GetDrawGrid())
			m_pGrid->SetDrawGrid(false);
		else
			m_pGrid->SetDrawGrid(true);
	}

	

	//m_2dRenderer->GetCameraPos(camPosX, camPosY);

	//if (input->IsKeyDown(aie::INPUT_KEY_W))
	//	camPosY += 500.0f * deltaTime;

	//if (input->IsKeyDown(aie::INPUT_KEY_S))
	//	camPosY -= 500.0f * deltaTime;

	//if (input->IsKeyDown(aie::INPUT_KEY_A))
	//	camPosX -= 500.0f * deltaTime;

	//if (input->IsKeyDown(aie::INPUT_KEY_D))
	//	camPosX += 500.0f * deltaTime;

	//m_2dRenderer->SetCameraPos(camPosX, camPosY);

	// Exit the application if escape is pressed.


	if (input->IsKeyDown(aie::INPUT_KEY_ESCAPE))
	{
		aie::Application* application = aie::Application::GetInstance();
		application->Quit();
	}
}

void Game2D::Draw()
{
	aie::Application* application = aie::Application::GetInstance();
	float time = application->GetTime();

	// Wipe the screen to clear away the previous frame.
	application->ClearScreen();

	// Prepare the renderer. This must be called before any sprites are drawn.
	m_2dRenderer->Begin();

	m_pGrid->Draw(m_2dRenderer); 

	// Draw the player.
	//m_Player1->Draw(m_2dRenderer);

	//m_Player2->Draw(m_2dRenderer); 
	
	
	// Draw some text.
	float windowHeight = (float)application->GetWindowHeight();
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", application->GetFPS());
	m_2dRenderer->DrawText(m_font, fps, 15.0f, windowHeight - 32.0f);


	// Done drawing sprites. Must be called at the end of the Draw().
	m_2dRenderer->End();
}