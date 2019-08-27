#include "Node.h"



Node::Node(Vector2 Pos, int IndexX, int IndexY)
{
	m_v2Position = Pos;
	m_nIndexX = IndexX;
	m_nIndexY = IndexY; 

	m_pPrev = nullptr; 

	m_nGscore = 0; 
	m_nFScore = 0;
	m_nHScore = 0;

	m_bBlocked = false; 

	for (int i = 0; i < NEIGHBOUR_COUNT; i++)
	{
		m_arrNeighbours[i] = nullptr;
		m_arrCosts[i] = 0; 
	}

}


Node::~Node()
{
}
