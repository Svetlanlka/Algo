#pragma once
#include "Graph.h"
#include <climits>

int CountShortestPath(const IGraph& graph, int u, int w) {
	std::vector<int> d(graph.VerticesCount()), k(graph.VerticesCount());
	for (int i = 0; i < graph.VerticesCount(); i++) {
		d[i] = INT_MAX;
		k[i] = 0;
	}
	k[u] = 1;
	d[u] = 0;

	std::vector<bool> visited(graph.VerticesCount(), false);
	std::queue<int> qu;
	qu.push(u);
	visited[u] = true;

	while (!qu.empty())
	{
	int curVertex = qu.front();
	qu.pop();
	if (curVertex == w) break;

	for (int nextVertex : graph.GetNextVertices(curVertex))
	{
	    // ++ Как DFS, только еще считаем расстояние d[u] и кол-во путей k[u]
	    if (d[curVertex] + 1 == d[nextVertex])
		k[nextVertex] += k[curVertex];

	    if (d[curVertex] + 1 < d[nextVertex]) {
		d[nextVertex] = d[curVertex] + 1;
		k[nextVertex] = k[curVertex];
	    }
	    // ++

	    if (!visited[nextVertex])
	    {
		visited[nextVertex] = true;
		qu.push(nextVertex);
	    }
	}
	}
	/*for (int i = 0; i < graph.VerticesCount(); ++i) {
	std::cout << "\tk[" << i << "]: " << k[i] << " | ";
	 	std::cout << "d[" << i << "]: " << d[i] << std::endl;
	}*/
	return k[w];
}
