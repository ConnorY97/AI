#include "Player.h"
#include <iostream>
#include "Input.h"
#include <random>

State<Guards>* States::WalkState = new Walk();
State<Guards>* States::WaitState = new Wait();
State<Guards>* States::SearchState = new Search();
State<Guards>* States::PatrolState = new Patrol();


Guards::Guards(Grid* pGrid) : m_StateMachine(this)
{
	m_StateMachine.SetState(States::SearchState);

	// Load the player's sprite.
	m_texture = new aie::Texture("./textures/ship.png");

	m_pGrid = pGrid; 

	m_bDrawCirle = false; 

	m_fSpeed = 100.0f; 
		
}

Guards::~Guards()
{
	// Delete the player's sprite.
	delete m_texture;
	m_texture = nullptr;

	
}

void Guards::Update(float deltaTime)
{
	
	

	// Update input for the player.
	aie::Input* input = aie::Input::GetInstance(); 
	
	Vector2 v2MousePos;
	v2MousePos.x = input->GetMouseX();
	v2MousePos.y = input->GetMouseY();

	if (input->IsKeyDown(aie::INPUT_KEY_S))
	{
		m_v2CurrentPos = v2MousePos; 
	}
	if (input->IsKeyDown(aie::INPUT_KEY_E))
	{
		m_v2End = v2MousePos; 
	}
	
	m_pGrid->FindPath(m_v2CurrentPos, m_v2End, m_arrPath); 

	std::cout << m_arrPath.size() << std::endl;
}

void Guards::Draw(aie::Renderer2D* renderer)
{
	float fRotation = atan2f(m_v2Direction.y, m_v2Direction.x); 

	// Draw the player's sprite.
	renderer->DrawSprite(m_texture, m_v2CurrentPos.x, m_v2CurrentPos.y, 0, 0, fRotation);

	renderer->DrawCircle(m_v2End.x, m_v2End.y, 10.0f); 

	//renderer->SetRenderColour(0.0f, 0.0f, 1.0f);

	

	for (int i = 1; i < m_arrPath.size(); i++)
	{
		renderer->DrawLine(m_arrPath[i - 1].x, m_arrPath[i - 1].y, m_arrPath[i].x, m_arrPath[i].y, 5.0f); 
	}

	renderer->SetRenderColour(1.0f, 1.0f, 1.0f); 
}

