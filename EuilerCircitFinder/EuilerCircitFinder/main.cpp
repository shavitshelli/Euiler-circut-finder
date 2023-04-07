#include<iostream>
#include "UndirectedGraph.h"
using namespace std;

/*
void main()
{
	int n, m;
	int vertix1, vertix2;
	char ch;
	cout<<"is the graph directed?";
	cin >> ch;
	cin >> n;
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cin >> vertix1;
		cin >> vertix2;
		if (vertix1 > m || vertix2 > m)
		{
			cout << "Wrong Input";
		}
	}

}
*/
void main()
{
	UndirectedGraph g1(6);
	g1.AddEdge(1, 2);
	g1.AddEdge(1, 3);
	g1.AddEdge(2, 3);
	g1.AddEdge(2, 4);
	g1.AddEdge(2, 5);
	g1.AddEdge(3, 4);
	g1.AddEdge(3, 5);
	g1.AddEdge(4, 5);
	g1.AddEdge(4, 6);
	g1.AddEdge(5, 6);
	g1.isEulerian();
	

}