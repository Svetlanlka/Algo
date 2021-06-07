#pragma once
#include "Graph.h"

struct SetGraph : public IGraph
{
	SetGraph(size_t size)
		: adjacencySet(size) {}

	SetGraph(const IGraph& graph) :adjacencySet(graph.VerticesCount()) {
		for (int from = 0; from < graph.VerticesCount(); from++) {
			std::set<int> nextVertices;
			for (auto to : graph.GetNextVertices(from))
				nextVertices.insert(to);
			adjacencySet[from] = nextVertices;
		}
	}

	void AddEdge(int from, int to) override {
		assert(0 <= from && from < adjacencySet.size());
		assert(0 <= to && to < adjacencySet.size());
		adjacencySet[from].insert(to);
	}

	int VerticesCount() const override {
		return (int)adjacencySet.size();
	}

	std::vector<int> GetNextVertices(int vertex) const override {
		assert(0 <= vertex && vertex < adjacencySet.size());
		std::vector<int> nextVertices;
		for (auto to : adjacencySet[vertex])
			nextVertices.push_back(to);
		return nextVertices;
	}
	std::vector<int> GetPrevVertices(int vertex) const override {
		assert(0 <= vertex && vertex < adjacencySet.size());
		std::vector<int> prevVertices;

		for (auto from = 0; from < adjacencySet.size(); from++) {
			for (int to : adjacencySet[from]) {
				if (to == vertex)
					prevVertices.push_back(from);
			}
		}

		return prevVertices;
	}

	void Print() override {
		for (int i = 0; i < VerticesCount(); ++i) {
			std::cout << i << ": ";
			for (auto value : adjacencySet[i])
				std::cout << value << " ";
			std::cout << std::endl;
		}
	}

private:
	std::vector<std::set<int>> adjacencySet;
};