#include "PathHeap.h"
#include "Node.h"
#include <algorithm>


PathHeap::PathHeap()
{
}


PathHeap::~PathHeap()
{
}

void PathHeap::Push(Node* pNode)
{
	m_arrHeap.push_back(pNode);

	int nCurrent = m_arrHeap.size() - 1;
	int nParent = GetParent(nCurrent);

	while (m_arrHeap[nCurrent]->m_nFScore < m_arrHeap[nParent]->m_nFScore)
	{
		Node* pSwap = m_arrHeap[nCurrent];
		m_arrHeap[nCurrent] = m_arrHeap[nParent];
		m_arrHeap[nParent] = pSwap;

		nCurrent = nParent;
		nParent = GetParent(nCurrent); 
	}
}

Node* PathHeap::Pop()
{
	Node* pNode = m_arrHeap[0];
	int nLast = m_arrHeap.size() - 1;
	int nCurrent = 0;

	m_arrHeap[0] = m_arrHeap[nLast];
	m_arrHeap.pop_back();

	int nChild1Index = GetChild(nCurrent, 1);
	int nChild2Index = GetChild(nCurrent, 2);

	int nCheapestIndex = nChild1Index;
	if (nCheapestIndex >= m_arrHeap.size())
		return pNode;

	if (nChild2Index < m_arrHeap.size() && m_arrHeap[nChild2Index]->m_nFScore < m_arrHeap[nCheapestIndex]->m_nFScore)
		nCheapestIndex = nChild2Index;

	while (m_arrHeap[nCheapestIndex]->m_nFScore < m_arrHeap[nCurrent]->m_nFScore)
	{
		Node* pSwap = m_arrHeap[nCheapestIndex];
		m_arrHeap[nCheapestIndex] = m_arrHeap[nCurrent]; 
		m_arrHeap[nCurrent] = pSwap;

		nCurrent = nCheapestIndex;
		nChild1Index = GetChild(nCurrent, 1);
		nChild2Index = GetChild(nCurrent, 2);

		nCheapestIndex = nChild1Index;
		if (nCheapestIndex >= m_arrHeap.size())
			return pNode;

		if (nChild2Index < m_arrHeap.size() && m_arrHeap[nChild2Index]->m_nFScore < m_arrHeap[nCheapestIndex]->m_nFScore)
			nCheapestIndex = nChild2Index;
	}

	return pNode; 
}

int PathHeap::GetParent(int nIndex)
{
	return (nIndex - 1) / 2;
}
int PathHeap::GetChild(int nIndex, int nChild)
{
	return (2 * nIndex) + nChild; 
}

int PathHeap::GetCount()
{
	return m_arrHeap.size();
}

void PathHeap::Clear()
{
	m_arrHeap.clear();
}

bool PathHeap::Find(Node* pNode)
{
	return std::find(m_arrHeap.begin(), m_arrHeap.end(), pNode) != m_arrHeap.end(); 
}