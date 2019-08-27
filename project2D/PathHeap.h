#pragma once
#include <vector>

class Node; 

class PathHeap
{
public:
	PathHeap();
	~PathHeap();

	void Push(Node* pNode);
	
	Node* Pop();
	
	int GetCount();

	void Clear();

	bool Find(Node* pNode);

private:
	int GetParent(int nIndex);
	int GetChild(int nIndex, int nChild);

	std::vector<Node*> m_arrHeap; 
};

