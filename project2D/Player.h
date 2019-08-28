#pragma once

#include "Renderer2D.h"
#include "Texture.h"
#include "Node.h"
#include "Grid.h"
#include <vector>
#include "Matrix3.h"
#include "StateMachine.h"
#include "Map.h"



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
	static State<Guards>* PatrolState;

};


struct Walk : public State<Guards>
{
	void update(float deltaTime, Guards* guards, StateMachine<Guards>* smGuard)
	{
		if (guards->m_arrPath.size() < 2)
		{
			smGuard->SetState(States::PatrolState); 
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

		if (fTimer >= 2)
		{
			fTimer = 0; 
			smGuard->SetState(States::PatrolState);
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

struct Patrol : public State<Guards>
{
	int nPatrolPointIndex = 0;
	Vector2 arrPatrolPoints[4];
	Map arrMap;
	
	
	Vector2 v2Patrol1;
	Vector2 v2Patrol2;
	Vector2 v2Patrol3;
	Vector2 v2Patrol4;

	void init(Guards* guards)
	{
		float a = guards->m_fSpeed;

		/*v2Patrol1.x = arrMap.m_arrMap[2][2]; 
		v2Patrol1.y = arrMap.m_arrMap[2][2]; 
		
		v2Patrol2.x = arrMap.m_arrMap[7][7];
		v2Patrol2.y = arrMap.m_arrMap[2][2];
		
		v2Patrol3.x = arrMap.m_arrMap[7][7];
		v2Patrol3.y = arrMap.m_arrMap[7][7];
		
		v2Patrol4.x = arrMap.m_arrMap[2][2];
		v2Patrol4.y = arrMap.m_arrMap[7][7]; */


		arrPatrolPoints[0] = v2Patrol1;
		arrPatrolPoints[1] = v2Patrol2;
		arrPatrolPoints[2] = v2Patrol3;
		arrPatrolPoints[3] = v2Patrol4;


		for (int x = 0; x < guards->m_pGrid->m_nWidth; x++)
		{
			for (int y = 0; y < guards->m_pGrid->m_nHeight; y++)
			{
				if (arrMap.m_arrMap[x][y] == 2)
				{
					Vector2 v2pos;
					v2pos.x = x * SQUARE_SIZE + GRID_POSX;
					v2pos.y = y * SQUARE_SIZE + GRID_POSY; 
		
					//arrPatrolPoints[nPatrolPointIndex] = v2pos; 
		
					//nPatrolPointIndex++; 
				}
			}
		}
	}
	
	void update(float deltaTime, Guards* guards, StateMachine<Guards>* smGuard)
	{
		Node* pTargetNode = guards->m_pGrid->GetNodeByPos(arrPatrolPoints[nPatrolPointIndex]); 
		Node* pCurrentNode = guards->m_pGrid->GetNodeByPos(guards->m_v2CurrentPos); 

		std::cout << nPatrolPointIndex <<  " " << arrPatrolPoints[nPatrolPointIndex].x << " " << arrPatrolPoints[nPatrolPointIndex].y << std::endl; 

		guards->m_v2End = pTargetNode->m_v2Position; 

		if (pTargetNode == pCurrentNode)
		{
			nPatrolPointIndex++; 

			if (nPatrolPointIndex > 3)
				nPatrolPointIndex = 0;
		}


		smGuard->SetState(States::WalkState); 

	}

	void exit()
	{
	}
};


