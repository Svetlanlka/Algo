#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"
#include "ArcGraph.h"
#include <iostream>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	ListGraph graph(7);
	graph.AddEdge(0, 1);
	graph.AddEdge(0, 5);
	graph.AddEdge(1, 2);
	graph.AddEdge(1, 3);
	graph.AddEdge(1, 5);
	graph.AddEdge(1, 6);
	graph.AddEdge(3, 2);
	graph.AddEdge(3, 4);
	graph.AddEdge(3, 6);
	graph.AddEdge(5, 4);
	graph.AddEdge(5, 6);
	graph.AddEdge(6, 4);

	std::cout << "ListGraph: \n";
	graph.Print();
	testGraph(graph);

	MatrixGraph mGraph(graph);
	std::cout << "MatrixGraph: \n";
	mGraph.Print();
	testGraph(mGraph);

	SetGraph sGraph(mGraph);
	std::cout << "SetGraph: \n";
	sGraph.Print();
	testGraph(sGraph);

	ArcGraph aGraph(sGraph);
	std::cout << "ArcGraph: \n";
	aGraph.Print();
	testGraph(aGraph);

	return 0;
}
