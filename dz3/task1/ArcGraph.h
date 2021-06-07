#pragma once
#include "Graph.h"

struct ArcGraph : public IGraph
{
	ArcGraph(size_t size)
		: adjacencyArc(size) {}

	ArcGraph(const IGraph& graph) {
		for (int from = 0; from < graph.VerticesCount(); from++) {
			std::vector<int> nextVertices = graph.GetNextVertices(from);
			for (auto to : nextVertices)
				adjacencyArc.push_back(std::make_pair(from, to));
		}
	}

	void AddEdge(int from, int to) override {
		assert(0 <= from && from < adjacencyArc.size());
		assert(0 <= to && to < adjacencyArc.size());
		adjacencyArc.push_back(std::make_pair(from, to));
	}

	int VerticesCount() const override {
		std::set<int> vertices;
		for (auto value : adjacencyArc) {
			vertices.insert(value.first);
			vertices.insert(value.second);
		}
		return (int)vertices.size();
	}

	std::vector<int> GetNextVertices(int vertex) const override {
		assert(0 <= vertex && vertex < adjacencyArc.size());
		std::vector<int> nextVertices;
		for (auto value : adjacencyArc) {
			if (value.first == vertex)
				nextVertices.push_back(value.second);
		}
		return nextVertices;
	}
	std::vector<int> GetPrevVertices(int vertex) const override {
		assert(0 <= vertex && vertex < adjacencyArc.size());
		std::vector<int> prevVertices;
		for (auto value : adjacencyArc) {
			if (value.second == vertex)
				prevVertices.push_back(value.first);
		}
		return prevVertices;
	}

	void Print() override {
		for (auto value : adjacencyArc) {
			std::cout << "{" << value.first << "," << value.second << "}" << " ";
		}
		std::cout << std::endl;
	}

private:
	std::vector<std::pair<int, int>> adjacencyArc;
};
