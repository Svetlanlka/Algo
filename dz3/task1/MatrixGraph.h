#pragma once
#include "Graph.h"

struct MatrixGraph : public IGraph
{
	MatrixGraph(size_t size)
		: adjacencyMatrix(size, std::vector<bool>(size, false)) {}

	MatrixGraph(const IGraph& graph) 
		:adjacencyMatrix(graph.VerticesCount(), std::vector<bool> (graph.VerticesCount(), false)) 
	{
		for (int from = 0; from < graph.VerticesCount(); from++) {
			std::vector<int> nextVertices = graph.GetNextVertices(from);
			for (int to : nextVertices)
				adjacencyMatrix[from][to] = 1;
		}
	}

	void AddEdge(int from, int to) override {
		assert(0 <= from && from < adjacencyMatrix.size());
		assert(0 <= to && to < adjacencyMatrix.size());
		adjacencyMatrix[from][to] = 1;
	}

	int VerticesCount() const override {
		return (int)adjacencyMatrix.size();
	}

	std::vector<int> GetNextVertices(int vertex) const override {
		assert(0 <= vertex && vertex < adjacencyMatrix.size());
		std::vector<int> nextVertices;

		for (int to = 0; to < adjacencyMatrix[vertex].size(); to++) {
			if (adjacencyMatrix[vertex][to])
				nextVertices.push_back(to);
		}
		return nextVertices;
	}
	std::vector<int> GetPrevVertices(int vertex) const override {
		assert(0 <= vertex && vertex < adjacencyMatrix.size());
		std::vector<int> prevVertices;

		for (int to = 0; to < adjacencyMatrix.size(); to++) {
			if (adjacencyMatrix[to][vertex])
				prevVertices.push_back(to);
		}

		return prevVertices;
	}

	void Print() override {
		for (int i = 0; i < VerticesCount(); i++) {
			for (int j = 0; j < VerticesCount(); ++j)
				std::cout << adjacencyMatrix[i][j] << " ";
			std::cout << std::endl;
		}
	}

private:
	std::vector<std::vector<bool>> adjacencyMatrix;
};

