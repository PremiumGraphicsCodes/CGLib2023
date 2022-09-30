#pragma once

#include <vector>
#include <memory>

#include "IVertex.h"
#include "IShape.h"
#include "../Math/Box3d.h"

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

	WireFrame() = default;

	void add(std::unique_ptr<IVertex> v);

	const std::vector<std::unique_ptr<IVertex>>& getVertices() const { return vertices; }

	void addEdge(const Edge& edge);

	std::vector<Edge> getEdges() const { return edges; }

	Math::Box3df getBoundingBox() const;

private:
	std::vector<Edge> edges;
	std::vector<std::unique_ptr<Shape::IVertex>> vertices;

};
	}
}