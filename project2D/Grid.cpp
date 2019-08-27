#include "Grid.h"
#include "Node.h"
#include <iostream>
#include <limits>
#include "Map.h"




Grid::Grid(int width, int height)
{
	m_nWidth = width;
	m_nHeight = height; 

	Map arrMap;

	m_bDrawLines = true;
	m_bDrawGrid = true; 

	m_bDrawLines = true; 

	m_arrNodeList = new Node**[m_nWidth];

	for (int i = 0; i < m_nWidth; i++)
	{
		m_arrNodeList[i] = new Node * [m_nHeight];
	}

	for (int x = 0; x < m_nWidth; x++)
	{
		for (int y = 0; y < m_nHeight; y++)
		{
			Vector2 pos;
			pos.x = x * SQUARE_SIZE + GRID_POSX;
			pos.y = y * SQUARE_SIZE + GRID_POSY;
			m_arrNodeList[x][y] = new Node(pos, x, y);
			if (arrMap.m_arrMap[x][y] == 1)
				m_arrNodeList[x][y]->m_bBlocked = true; 
		}
	}

	//	|7|2|6|
	//	|1|C|3|
	//	|4|0|5|
	for (int x = 0; x < m_nWidth; ++x)
	{
		for (int y = 0; y < m_nHeight; ++y)
		{
			if (y > 0)
				m_arrNodeList[x][y]->m_arrNeighbours[0] = m_arrNodeList[x][y - 1];	//Down

			if (x > 0)
				m_arrNodeList[x][y]->m_arrNeighbours[1] = m_arrNodeList[x - 1][y];	//Left

			if (y < m_nHeight - 1)
				m_arrNodeList[x][y]->m_arrNeighbours[2] = m_arrNodeList[x][y + 1];	//Up

			if (x < m_nWidth - 1)
				m_arrNodeList[x][y]->m_arrNeighbours[3] = m_arrNodeList[x + 1][y];	//Right

			if (x < m_nWidth - 1 && y < m_nHeight - 1)
				m_arrNodeList[x][y]->m_arrNeighbours[4] = m_arrNodeList[x + 1][y + 1];	//Right Up

			if (x < m_nWidth - 1 && y > 0)
				m_arrNodeList[x][y]->m_arrNeighbours[5] = m_arrNodeList[x + 1][y - 1];	//Right down

			if (x > 0 && y > 0)
				m_arrNodeList[x][y]->m_arrNeighbours[6] = m_arrNodeList[x - 1][y - 1];	//Left down

			if (x > 0 && y < m_nHeight - 1)
				m_arrNodeList[x][y]->m_arrNeighbours[7] = m_arrNodeList[x - 1][y + 1];	//Left Up

			// Adjacent = 1 
			m_arrNodeList[x][y]->m_arrCosts[0] = 10;
			m_arrNodeList[x][y]->m_arrCosts[1] = 10;
			m_arrNodeList[x][y]->m_arrCosts[2] = 10;
			m_arrNodeList[x][y]->m_arrCosts[3] = 10;

			// Diagonal = 1.4
			m_arrNodeList[x][y]->m_arrCosts[4] = 14;
			m_arrNodeList[x][y]->m_arrCosts[5] = 14;
			m_arrNodeList[x][y]->m_arrCosts[6] = 14;
			m_arrNodeList[x][y]->m_arrCosts[7] = 14;
		}
	}

	m_barrClosedList = new bool[m_nWidth * m_nHeight];

	/*for (int x = 0; x < m_nWidth; x++)
	{
		for (int y = 0; y < m_nHeight; y++)
		{
			if ()
		}
	}*/
}


Grid::~Grid()
{
	for (int x = 0; x < m_nWidth; x++)
	{
		for (int y = 0; y < m_nHeight; y++)
		{
			delete m_arrNodeList[x][y];
			m_arrNodeList[x][y] = nullptr; 
		}
	}

	for (int i = 0; i < m_nWidth; i++)
	{
		delete[] m_arrNodeList[i];
		m_arrNodeList[i] = nullptr;
	}

	delete[] m_arrNodeList;
	m_arrNodeList = nullptr;

	delete[] m_barrClosedList; 
	m_barrClosedList = nullptr; 
}


void Grid::Update(float fDealtaTime)
{
	aie::Input* pInput = aie::Input::GetInstance();

	//Toggle grid
	if (pInput->WasKeyPressed(aie::INPUT_KEY_G))
	{
		if (m_bDrawGrid)
			m_bDrawGrid = false;
		else
			m_bDrawGrid = true;
	}

	//Toggle Lines
	if (pInput->WasKeyPressed(aie::INPUT_KEY_L))
	{
		if (m_bDrawLines)
			m_bDrawLines = false;
		else
			m_bDrawLines = true; 
	}

	
}

void Grid::Draw(aie::Renderer2D* pRenderer)
{
	for (int x = 0; x < m_nWidth; x++)
	{
		for (int y = 0; y < m_nHeight; y++)
		{
			Vector2 v2Pos = m_arrNodeList[x][y]->m_v2Position; 

			pRenderer->SetRenderColour(0.2f, 0.2f, 0.2f);

			if (m_arrNodeList[x][y]->m_bBlocked)
				pRenderer->SetRenderColour(1.0f, 0.0f, 0.0f);

			pRenderer->DrawBox(v2Pos.x, v2Pos.y, SQUARE_SIZE - 10.0f, SQUARE_SIZE - 10.0f);
			
			if (m_bDrawLines)
			{
				for (int n = 0; n < NEIGHBOUR_COUNT; n++)
				{
					if (m_arrNodeList[x][y]->m_arrNeighbours[n])
					{
						Vector2 v2NeighbourPos = m_arrNodeList[x][y]->m_arrNeighbours[n]->m_v2Position; 
						pRenderer->SetRenderColour(0.0f, 0.5f, 0.5f);
						if (m_bDrawGrid)
							pRenderer->DrawLine(v2Pos.x, v2Pos.y, v2NeighbourPos.x, v2NeighbourPos.y, 2.5f); 
					}
				}
			}
		}
	}

	

	pRenderer->SetRenderColour(1.0f, 1.0f, 1.0f); 
}



Node* Grid::GetNodeByPos(Vector2 v2Pos, bool ignoreBlocked)
{
	//int nX = (v2Pos.x - GRID_POSX + (SQUARE_SIZE * 0.5f)) / SQUARE_SIZE;
	//int nY = (v2Pos.y - GRID_POSX + (SQUARE_SIZE * 0.5f)) / SQUARE_SIZE;

	//if (nX < 0 || nY < 0 || nX >= m_nWidth || nY >= m_nHeight)
	//	return nullptr;

	//return m_arrNodeList[nX][nY]; 

	Node* pClosest = nullptr;

	float fMinDist = std::numeric_limits<float>().max();

	for (int x = 0; x < GRID_SIZE_X; x++)
	{
		for (int y = 0; y < GRID_SIZE_Y; y++)
		{
			if (ignoreBlocked && m_arrNodeList[x][y]->m_bBlocked)continue;
			Vector2 v2Sub = ((m_arrNodeList[x][y]->m_v2Position) - v2Pos);

			float fDist = v2Sub.magnitudeSqr();

			if (fDist < fMinDist)
			{
				fMinDist = fDist;
				pClosest = m_arrNodeList[x][y];
			}
		}
	}

	return pClosest; 
}

bool Grid::FindPath(Vector2 v2Start, Vector2 v2End, std::vector<Vector2>& v2Path)
{
	//Find start and end nodes 
	Node* pStartNode = GetNodeByPos(v2Start, true);
	Node* pEndNode = GetNodeByPos(v2End);
	v2Path.clear();
	//std::cout << pEndNode->m_nIndexX << ", " << pEndNode->m_nIndexY << std::endl;


	//Making sure that the path exists and is valid 
	if (!pStartNode || !pEndNode)
		return false;
	if (pStartNode == pEndNode)
		return false;
	if (pStartNode->m_bBlocked || pEndNode->m_bBlocked)
		return false;

	m_phOpenList.Clear();
	memset(m_barrClosedList, 0, sizeof(bool) * m_nWidth * m_nHeight);
	bool bFoundPath = false;

	pStartNode->m_pPrev = nullptr;

	pStartNode->m_nGscore = 0;
	pStartNode->m_nHScore = CalculateHeuristic(pStartNode, pEndNode);
	pStartNode->m_nFScore = pStartNode->m_nGscore + pStartNode->m_nHScore; 

	m_phOpenList.Push(pStartNode);

	while (m_phOpenList.GetCount() > 0)
	{
		//Remove a node from the open list 
		Node* pCurrent = m_phOpenList.Pop();

		//Add current node to closed list 
		int nIndex = pCurrent->m_nIndexY * m_nWidth + pCurrent->m_nIndexX;
		m_barrClosedList[nIndex] = true;

		//Check if the current node is the end of the path 
		if (pCurrent == pEndNode)
		{
			bFoundPath = true;
			break; 
		}

		for (int i = 0; i < NEIGHBOUR_COUNT; i++)
		{
			//Get current nodes neighbour 
			Node* pNeighbour = pCurrent->m_arrNeighbours[i];

			//Check if neighbout list is empty 
			if (!pNeighbour)
				continue;

			//Check the neighbour is transversable 
			if (pNeighbour->m_bBlocked)
				continue;

			int nNeighbourIndex = pNeighbour->m_nIndexY * m_nWidth + pNeighbour->m_nIndexX;
			if (m_barrClosedList[nNeighbourIndex])
				continue; 

			//If neighbour is alone 
			if (!m_phOpenList.Find(pNeighbour))
			{
				pNeighbour->m_pPrev = pCurrent;
				pNeighbour->m_nGscore = pCurrent->m_nGscore + pCurrent->m_arrCosts[i];

				//Calculate total cost 
				pNeighbour->m_nHScore = CalculateHeuristic(pNeighbour, pEndNode);
				pNeighbour->m_nFScore = pNeighbour->m_nGscore + pNeighbour->m_nHScore;

				//Remove node 
				m_phOpenList.Push(pNeighbour);
			}
			else
			{
				//If there is a cheaper node replace current 
				int nCost = pCurrent->m_nGscore + pCurrent->m_arrCosts[i];
				if (nCost < pNeighbour->m_nGscore)
				{
					//Set score 
					pNeighbour->m_nGscore = nCost;

					//Calculate score 
					pNeighbour->m_nFScore = pNeighbour->m_nGscore + pNeighbour->m_nHScore;
					pNeighbour->m_pPrev = pCurrent;
				}
			}
		}
	}

	if (bFoundPath)
	{
		//Get final node 
		Node* pCurrent = pEndNode;

		while (pCurrent)
		{
			//Create the path 
			v2Path.insert(v2Path.begin(), pCurrent->m_v2Position);

			//Return one node 
			pCurrent = pCurrent->m_pPrev;
		}
		return true;
	}
	return false; 
}

int Grid::CalculateHeuristic(Node* pNode, Node* pEndNode)
{
	int nDistx = abs(pNode->m_nIndexX - pEndNode->m_nIndexX);
	int nDistY = abs(pNode->m_nIndexY - pEndNode->m_nIndexY);

	if (nDistx > nDistY)
		return (14 * nDistY) + 10 * (nDistx - nDistY);
	else
		return (14 * nDistx) + 10 * (nDistY - nDistx); 
}

