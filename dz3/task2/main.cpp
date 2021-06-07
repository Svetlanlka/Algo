#include "ListGraph.h"
#include "CountShortPaths.h"
#include <iostream>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

int main() {
	setlocale(LC_ALL, "Rus");

	int v, n;
	std::cin >> v;
	std::cin >> n;

	ListGraph graph2(v);

	for (int i = 0; i < n; ++i) {
		int a, b;
		std::cin >> a;
		std::cin >> b;
		graph2.AddEdge(a, b);
		graph2.AddEdge(b, a);
	}
	int u, w;
	std::cin >> u;
	std::cin >> w;
	// graph2.Print();
	std::cout << CountShortestPath(graph2, u, w);
	
	return 0;
}
