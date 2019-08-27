#pragma once
#include "Vector2.h"

#define NEIGHBOUR_COUNT 8

class Node
{
public:
	Node(Vector2 Pos, int IndexX, int IndexY);

	~Node();

	Vector2 m_v2Position;

	int m_nIndexX;
	int m_nIndexY;

	Node* m_pPrev;

	int m_nGscore;
	int m_nFScore;
	int m_nHScore;



	Node* m_arrNeighbours[NEIGHBOUR_COUNT];
	int m_arrCosts[NEIGHBOUR_COUNT];
	bool m_bBlocked; 
};

