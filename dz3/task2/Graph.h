#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <functional>
#include <queue>
#include <sstream>
#include <deque>
#include <set>

struct IGraph {
	virtual ~IGraph() {}

	// Добавление ребра от from к to.
	virtual void AddEdge(int from, int to) = 0;

	virtual int VerticesCount() const = 0;

	virtual std::vector<int> GetNextVertices(int vertex) const = 0;
	virtual std::vector<int> GetPrevVertices(int vertex) const = 0;

	virtual void Print() = 0;
};

void BFS(const IGraph& graph, int vertex, std::vector<bool>& visited, std::function<void(int)>& func) {
	std::queue<int> qu;
	qu.push(vertex);
	visited[vertex] = true;

	while (!qu.empty()) {
		int cur = qu.front();
		qu.pop();

		func(cur);

		for (int nextVertex : graph.GetNextVertices(cur)) {
			if (!visited[nextVertex]) {
				visited[nextVertex] = true;
				qu.push(nextVertex);
			}
		}
	}
}

void mainBFS(const IGraph& graph, std::function<void(int)> func) {
	std::vector<bool> visited(graph.VerticesCount(), false);
	for (int i = 0; i < graph.VerticesCount(); i++)
	{
		if (!visited[i])
			BFS(graph, i, visited, func);
	}
}

void DFS(const IGraph& graph, int vertex, std::vector<bool>& visited, std::function<void(int)>& func)
{
	visited[vertex] = true;
	func(vertex);

	for (int nextVertex : graph.GetNextVertices(vertex))
	{
		if (!visited[nextVertex])
			DFS(graph, nextVertex, visited, func);
	}
}

void mainDFS(const IGraph& graph, std::function<void(int)> func)
{
	std::vector<bool> visited(graph.VerticesCount(), false);
	for (int i = 0; i < graph.VerticesCount(); i++)
	{
		if (!visited[i])
			DFS(graph, i, visited, func);
	}
}

void topologicalSortInternal(const IGraph& graph, int vertex, std::vector<bool>& visited, std::deque<int>& sorted)
{
	visited[vertex] = true;

	for (int nextVertex : graph.GetNextVertices(vertex))
	{
		if (!visited[nextVertex])
			topologicalSortInternal(graph, nextVertex, visited, sorted);
	}

	sorted.push_front(vertex);
}

std::deque<int> topologicalSort(const IGraph& graph)
{
	std::deque<int> sorted;
	std::vector<bool> visited(graph.VerticesCount(), false);

	for (int i = 0; i < graph.VerticesCount(); i++)
	{
		if (!visited[i])
			topologicalSortInternal(graph, i, visited, sorted);
	}

	return sorted;
}

void testGraph(const IGraph& graph) {
	std::cout << "Test: " << std::endl;
	mainBFS(graph, [](int vertex) { std::cout << vertex << " "; });
	std::cout << std::endl;
	mainDFS(graph, [](int vertex) { std::cout << vertex << " "; });
	std::cout << std::endl;

	for (int vertex : topologicalSort(graph)) {
		std::cout << vertex << " ";
	}
	std::cout << std::endl;
}