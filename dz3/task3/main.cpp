#include "Dijkstra.h"
#include <iostream>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");
	
	int n, m;
	std::cin >> n;
	std::cin >> m;

	ListWeightGraph graph2(n);

	for (int i = 0; i < m; ++i) {
		int a, b, t;
		std::cin >> a;
		std::cin >> b;
		std::cin >> t;
		graph2.AddEdge(a, b, t);
		graph2.AddEdge(b, a, t);
	}
	int u, w;
	std::cin >> u;
	std::cin >> w;
	// std::cout << "Graph2:" << std::endl;
	// graph2.Print();
	std::cout << ShortestTownPath(graph2, u, w);
	return 0;
}
