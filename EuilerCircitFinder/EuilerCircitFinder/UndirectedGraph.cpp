#include "UndirectedGraph.h"


UndirectedGraph::UndirectedGraph(int V)
{
	adjacency.resize(V);
	IteratorVector.resize(V);
	this->NumOfVertices = V;

	for (int i = 0; i < V; i++)
	{
		adjacency[i].push_back(Edge(-1));
	}
}

void UndirectedGraph::AddEdge(int u, int v)
{
	adjacency[u - 1].push_back(Edge(v - 1));
	adjacency[v - 1].push_back(Edge(u - 1));

	if (adjacency[u - 1].size() == 2)//if its the first value added we need to make dummy head point to it 

		adjacency[u - 1].front().parallelEdge = &(*(++adjacency[u - 1].begin()));

	adjacency[u - 1].back().parallelEdge = &adjacency[v - 1].back();//we always push to the list end 

	if (adjacency[v - 1].size() == 2)//if its the first value added we need to make dummy head point to it 
	
		adjacency[v - 1].front().parallelEdge = &(*(++adjacency[v - 1].begin()));
	
	adjacency[v - 1].back().parallelEdge = &adjacency[u - 1].back();//we always push to the list end 
}

void UndirectedGraph::DeleteEdge(int u, int v)
{

}

void UndirectedGraph::NeighborsList(int u)
{
	for (auto i = ++adjacency[u - 1].begin(); i != adjacency[u - 1].end(); i++)
	{
		cout << (*i).Vnum+1 << " ";
	}
	/*for (int i = 0; i < NumOfVertices; i++)
	{
		list<Edge>::iterator t = adjacency[i].begin();
		cout << "the " << i + 1 << " rep : " << (*t).Vnum + 1 << " my paralel is : " << (*t).parallelEdge->Vnum + 1<< endl;
		t++;
		cout << " the rest is : "<<endl;
		for (auto z = t; z != adjacency[i].end(); z++)
		{
			cout << (*z).Vnum + 1 << " " << "my paralel is : " << (*z).parallelEdge->Vnum + 1 <<" at address : " << &(*z) << endl;
		}
		cout << endl;
	}*/
}

bool UndirectedGraph::AreNeighbors(int u, int v)
{
	for (auto i = adjacency[u - 1].begin(); i != adjacency[u - 1].end(); i++)
	{
		if ((*i).Vnum == v - 1)
			return true;
	}
	return false;
}

void UndirectedGraph::DFSConnectionCheck(int v, bool* visited)
{
	visited[v] = true;
	list<Edge>::iterator i;

	for (i = adjacency[v].begin(); i != adjacency[v].end(); ++i)
	{
		if (!visited[(*i).Vnum])
		{
			DFSConnectionCheck((*i).Vnum, visited);
		}
	}
}


bool UndirectedGraph::isGraphConnected()
{
	bool* visited = new bool[NumOfVertices];
	int i;
	for (i = 0; i < NumOfVertices; i++)
		visited[i] = false;

	//fills the visited array 
	DFSConnectionCheck(0, visited);

	// if all vertices are visited so graph is connected 
	for (i = 0; i < NumOfVertices; i++)
		if (visited[i] == false)
			return false;

	return true;
}

bool UndirectedGraph::isEulerian()
{
	if (isGraphConnected() == false)// if there graph is not connected graph is not euiler
	{
		cout << "not euiler";
		return false;
	}

	int even = 0;
	for (int i = 0; i < NumOfVertices; i++)
	{
		if (adjacency[i].size() % 2 -1 != 0)// if there is a vertex with odd degree graph is not euiler because of dummy head we take off 1 
			return false;
	}
	cout << "euiler circuit : ";
	printEulerianCircle();
	return true;
}



list<int> UndirectedGraph::FindCircuit(int v , bool flag)
{
	list<int> tempListToReturn;
	int thisVertex = v;
	int NextVertex;
	tempListToReturn.push_back(thisVertex);
	while (IteratorVector[v] != adjacency[v].end())
	{
		(*IteratorVector[thisVertex]).CanWeGoThroghThisEdge = false;//mark this edge 
		(*IteratorVector[thisVertex]).parallelEdge->CanWeGoThroghThisEdge = false;//mark paralel edge 
		NextVertex = (*IteratorVector[thisVertex]).Vnum;
		tempListToReturn.push_back(NextVertex);
		while ((*IteratorVector[thisVertex]).CanWeGoThroghThisEdge == false)//check if we stand on an edge that we already stood on 
		{
			(IteratorVector[thisVertex])++;
			if (IteratorVector[thisVertex] == adjacency[thisVertex].end())//check we do not exceed the limit
				break;
		}
		while ((*IteratorVector[NextVertex]).CanWeGoThroghThisEdge == false)//check if we stand on an edge that we already stood on 
		{
			(IteratorVector[NextVertex])++;
			if (IteratorVector[NextVertex] == adjacency[NextVertex].end())//check we do not exceed the limit
				break;
		}
		thisVertex = NextVertex;
	}
	if (flag == true)//aka first time we use find circuit 
		return tempListToReturn;//return full list
	tempListToReturn.pop_front();
	return tempListToReturn;
}

void UndirectedGraph::printEulerianCircle()
{
	initIteratorVector();
	list<int> EulerianCircle = FindCircuit(0,true);
	list<int>::iterator currEulerianCircleIterator = EulerianCircle.begin();
	list<int>::iterator nextEulerianCircleIterator = ++EulerianCircle.begin();
	list<int>::iterator tempIterator;
	while (currEulerianCircleIterator != EulerianCircle.end())
	{
		int i = *currEulerianCircleIterator;
		if (IteratorVector[i] == adjacency[i].end())
		{
			currEulerianCircleIterator++;
			nextEulerianCircleIterator++;
		}
		if (nextEulerianCircleIterator == EulerianCircle.end())
			break;
		i = *currEulerianCircleIterator;
		list<int> tempEulerianCircle = FindCircuit(i,false);
		EulerianCircle.splice(nextEulerianCircleIterator, tempEulerianCircle);
		tempIterator = currEulerianCircleIterator;
		nextEulerianCircleIterator = ++currEulerianCircleIterator;
		currEulerianCircleIterator = tempIterator;
	}
	for (list<int>::iterator i = EulerianCircle.begin(); i != EulerianCircle.end(); i++)
		cout << *i+1 << " ";
}

void UndirectedGraph::initIteratorVector()
{
	for (int i = 0; i < NumOfVertices; i++)
	{
		IteratorVector[i] = ++adjacency[i].begin();
	}
}
