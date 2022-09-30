#pragma once

#include <vector>
#include <memory>

#include "IVertex.h"
#include "IShape.h"

namespace Crystal {
	namespace Shape {

class WireFrame : public IShape
{
public:
	struct Edge
	{
		Edge() = default;

		Edge(const unsigned int startIndex, const unsigned int endIndex) :
			startIndex(startIndex),
			endIndex(endIndex)
		{}

		unsigned int startIndex;
		unsigned int endIndex;
	};

	void add(std::unique_ptr<Shape::IVertex> v);

	const std::vector<std::unique_ptr<Shape::IVertex>>& getVertices() const { return vertices; }

	void addEdge(const Edge& edge);

	std::vector<Edge> getEdges() const { return edges; }

private:
	std::vector<Edge> edges;
	std::vector<std::unique_ptr<Shape::IVertex>> vertices;

};
	}
}