#pragma once
#include "Renderer2D.h"
#include "Vector2.h"
#include "Input.h"
#include "PathHeap.h"
#include <vector>

#define SQUARE_SIZE 40
#define GRID_POSX 10
#define GRID_POSY 10


#define GRID_SIZE_X 10
#define GRID_SIZE_Y 10
class Node; 

class Grid
{
public:
	Grid(int width, int height);
	~Grid();

	void Update(float fDeltaTime);
	void Draw(aie::Renderer2D* pRenderer); 

	//Returns a pointer to a node 
	Node* GetNodeByPos(Vector2 v2Pos, bool ignoreBlocked = false);

	//Finds best path
	//Give me two vector 2 to know where to start and end 
	//Give me a vector of vector2 to write the path too child
	bool FindPath(Vector2 v2Start, Vector2 v2End, std::vector<Vector2>& v2Path);

	//Calcualtes score 
	int CalculateHeuristic(Node* pNode, Node* pEndNode); 


	void SetDrawGrid(bool bflag) { m_bDrawGrid = bflag; }

	bool GetDrawGrid() { return m_bDrawGrid; }
	int m_nWidth;
	int m_nHeight; 
private:

	Node*** m_arrNodeList; 

	//Vector2 m_v2Position; 

	

	PathHeap m_phOpenList;
	bool* m_barrClosedList;

	bool m_bDrawLines;
	bool m_bDrawGrid; 

	bool m_bDrawStart;
	bool m_bDrawEnd; 
};

