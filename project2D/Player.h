#pragma once

#include "Renderer2D.h"
#include "Texture.h"
#include "Node.h"
#include "Grid.h"
#include <vector>
#include "Matrix3.h"
#include "StateMachine.h"


class Guards
{
public:
	Guards(Grid* pGrid);
	~Guards();

	void Update(float deltaTime);
	void Draw(aie::Renderer2D* renderer);


	aie::Texture* m_texture;

	bool m_bDrawCirle; 


	Grid* m_pGrid; 


	float m_fSpeed; 
	
	Vector2 m_v2Direction; 

	Vector2 m_v2CurrentPos;
	Vector2 m_v2End; 

	StateMachine<Guards> m_StateMachine; 

	std::vector<Vector2> m_arrPath; 
	//aie::Input* m_pInput; 
};

struct States
{
	static State<Guards>* SearchState; 
	static State<Guards>* WaitState; 
	static State<Guards>* WalkState;

};


struct Walk : public State<Guards>
{
	void update(float deltaTime, Guards* guards, StateMachine<Guards>* smGuard)
	{
		if (guards->m_arrPath.size() < 2)
		{
			smGuard->SetState(States::WaitState); 
			return; 
		}
		
		if (guards->m_v2End.magnitudeSqr() < 0.001f)
			return;
		guards->m_v2Direction = guards->m_arrPath[1] - guards->m_v2CurrentPos;

		guards->m_v2Direction.normalise();

		guards->m_v2CurrentPos += guards->m_v2Direction * guards->m_fSpeed * deltaTime;
	}
};

struct Wait : public State<Guards>
{
	float fTimer = 0; 
	void update(float deltaTime, Guards* guards, StateMachine<Guards>* smGuard)
	{
		fTimer += deltaTime; 

		if (fTimer >= 5)
		{
			fTimer = 0; 
			smGuard->SetState(States::SearchState);
		}
	}
};

struct Search : public State<Guards>
{
	void update(float deltaTime, Guards* guards, StateMachine<Guards>* smGuard)
	{
		Vector2 randPos = Vector2(((float)rand() / (float)RAND_MAX) * guards->m_pGrid->m_nWidth * SQUARE_SIZE, ((float)rand() / (float)RAND_MAX) * guards->m_pGrid->m_nHeight * SQUARE_SIZE);
		Node* n = guards->m_pGrid->GetNodeByPos(randPos);
		if (n)
			guards->m_v2End = n->m_v2Position;

		if (guards->m_pGrid->FindPath(guards->m_v2CurrentPos, guards->m_v2End, guards->m_arrPath))
			smGuard->SetState(States::WalkState);
			
	}


};


