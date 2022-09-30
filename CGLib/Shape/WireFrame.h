#pragma once

#include <vector>
#include "IVertex.h"

namespace Crystal {
	namespace Shape {

class WireFrame
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

	void add(Shape::IVertex* v);

	std::vector<Shape::IVertex*> getVertices() const { return vertices; }

	void addEdge(const Edge& edge);

	std::vector<unsigned int> getIndices() const { return indices; }

private:
	std::vector<unsigned int> indices;
	std::vector<Shape::IVertex*> vertices;

};
	}
}