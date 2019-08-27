//#include "Edge.h"
//#include "Node.h"
//#include <vector>
//
//
//
//void DijkstrasSearch(Node* pStart, Node* pEnd)
//{
//	//Validate the input 
//	if (pStart == nullptr || pEnd == nullptr)
//		return;
//
//	if (pStart == pEnd)
//		return; 
//
//	//Initialise the starting node 
//	pStart->m_fGScore = 0;
//	pStart->m_pParent = nullptr;
//
//	//Create out temporary lists for storing the nodes we're visiting/visited
//	std::vector<Node*> arrOpenList;
//	std::vector<Node*> arrClosedList;
//
//	arrOpenList.insert(arrOpenList.begin(), pStart); 
//
//	while (arrOpenList.size() != 0)
//	{
//		if (arrOpenList.front() + 1)
//		{
//			while (arrOpenList.front()->m_fGScore < arrOpenList.front()->m_fGScore)
//			{
//				Node* Temp = arrOpenList.front();
//
//				arrOpenList.front() = arrOpenList.front(); 
//
//				arrOpenList.front() = Temp;
//			}
//		}
//		
//	}
//
//}
//
//void main()
//{
//
//}