#pragma once
#include "Graph.h"
#include <climits>

struct ListWeightGraph : public IGraph
{
	ListWeightGraph(size_t size)
		: adjacencyLists(size) {}

	ListWeightGraph(const IGraph& graph) :adjacencyLists(graph.VerticesCount()) {
		for (int i = 0; i < graph.VerticesCount(); i++) {
			std::vector<std::pair<int, int>> elements;
			for (auto el : graph.GetNextVertices(i)) {
				elements.push_back(std::make_pair(el, 0));
			}
			adjacencyLists[i] = elements;
		}
	}

	void AddEdge(int from, int to) override {
		assert(0 <= from && from < adjacencyLists.size());
		assert(0 <= to && to < adjacencyLists.size());
		adjacencyLists[from].push_back(std::make_pair(to, 0));
	}

	void AddEdge(int from, int to, int weight) {
		assert(0 <= from && from < adjacencyLists.size());
		assert(0 <= to && to < adjacencyLists.size());
		if (from == to) return; 																																																																																																																																					
		
		for (int i = 0; i < adjacencyLists[from].size(); ++i)
			if (adjacencyLists[from][i].first == to) {
				if (adjacencyLists[from][i].second <= weight) return;
				adjacencyLists[from].erase(adjacencyLists[from].begin() + i);
			}
				
		adjacencyLists[from].push_back(std::make_pair(to, weight));
	}

	int VerticesCount() const override {
		return (int)adjacencyLists.size();
	}

	std::vector<int> GetNextVertices(int vertex) const override {
		assert(0 <= vertex && vertex < adjacencyLists.size());
		std::vector<int> nextVertices;
		for (auto el : adjacencyLists[vertex])
			nextVertices.push_back(el.first);
		return nextVertices;
	}
	std::vector<std::pair<int, int>> GetNextVerticesWithWeight(int vertex) const {
		assert(0 <= vertex && vertex < adjacencyLists.size());
		return adjacencyLists[vertex];
	}
	std::vector<int> GetPrevVertices(int vertex) const override {
		assert(0 <= vertex && vertex < adjacencyLists.size());
		std::vector<int> prevVertices;

		for (int from = 0; from < adjacencyLists.size(); from++) {
			for (auto to : adjacencyLists[from]) {
				if (to.first == vertex)
					prevVertices.push_back(from);
			}
		}
		return prevVertices;
	}

	int getWeight(int u, int v) const {
		assert(0 <= u && u < adjacencyLists.size());
		assert(0 <= v && v < adjacencyLists.size());
		for (auto to : adjacencyLists[u]) {
			if (to.first == v)
				return to.second;
		}
	}

	void Print() override {
		for (int i = 0; i < VerticesCount(); ++i) {
			std::cout << i << ": ";
			for (auto value : adjacencyLists[i])
				std::cout << "[" << value.first << "," << value.second << "] ";
			std::cout << std::endl;
		}
	}

private:
	std::vector<std::vector<std::pair<int, int>>> adjacencyLists;
};

bool Relax(const ListWeightGraph& graph, std::vector<int> &d, std::vector<int> &pi, int u, int v) {
	if (d[v] > d[u] + graph.getWeight(u, v)) {
		d[v] = d[u] + graph.getWeight(u, v);
		pi[v] = u;
		return true;
	}
	return false;
}

struct queueCompare {
	bool operator() (const std::pair<int, int>& l, const std::pair<int, int>& r) const {
		if (l.second < r.second)
			return true;
		if (l.first == r.first)
			if (l.first < l.first)
				return true;
		return false;
	}
};

struct queueEqual {
	bool operator() (const std::pair<int, int>& l, const std::pair<int, int>& r) const {
		if (l.second == r.second && l.first == r.first)
			return true;
		return false;
	}
};

// Задача 3
int ShortestTownPath(const ListWeightGraph& graph, int u, int w) {
	std::vector<int> d(graph.VerticesCount()), pi(graph.VerticesCount());
	for (int i = 0; i < graph.VerticesCount(); i++) {
		d[i] = INT_MAX;
		pi[i] = -1;
	}
	d[u] = 0;

	// используем set, чтобы можно было менять значения в нашей *очереди*
	std::set<std::pair<int, int>, queueCompare> qu;
	qu.insert(std::make_pair(u, 0));


	while (!qu.empty())
	{
		int curVertex = (qu.begin())->first;
		qu.erase(qu.begin());
		// std::cout << "\tcur: " << curVertex;
		if (curVertex == w) break;

		for (auto nextVertex : graph.GetNextVerticesWithWeight(curVertex))
		{
			if (d[nextVertex.first] == INT_MAX) {
				d[nextVertex.first] = d[curVertex] + graph.getWeight(curVertex, nextVertex.first);
				pi[nextVertex.first] = curVertex;
				qu.insert(std::make_pair(nextVertex.first, d[nextVertex.first]));
			}
			else {
				int tmpD = d[nextVertex.first];
				if (Relax(graph, d, pi, curVertex, nextVertex.first)) {
					// std::cout << nextVertex.first << "! ";
					
					/*auto fnd = qu.find(std::make_pair(nextVertex.first, tmpD));
					qu.erase(fnd);
					qu.insert(std::make_pair(nextVertex.first, d[nextVertex.first]));*/
					auto i = qu.begin();
					for (auto el : qu) {
						if (el.first == nextVertex.first && el.second == tmpD) {
							qu.erase(i);
							qu.insert(std::make_pair(nextVertex.first, d[nextVertex.first]));
							break;
						}
						i++;
					}
				}	
			}

		}
		/*std::cout << "\n\nqueue: ";
		for (auto el : qu)
			std::cout << "{" << el.first << "," << el.second << "} ";
		std::cout << "\n\n";*/
		
	}

	/*for (int i = 0; i < graph.VerticesCount(); ++i) {
		std::cout << "\tpi[" << i << "]: " << pi[i] << " | ";
		std::cout << "d[" << i << "]: " << d[i] << std::endl;
	}*/

	return d[w];
}
