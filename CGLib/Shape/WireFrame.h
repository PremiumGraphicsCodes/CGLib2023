#pragma once

#include <vector>
#include "IVertex.h"

namespace Crystal {
	namespace Shape {

class WireFrame
{
public:
	void add(Shape::IVertex* v);

	std::vector<Shape::IVertex*> getVertices() const { return vertices; }

	void addIndex(const unsigned int index) { this->indices.push_back(index); }

	std::vector<unsigned int> getIndices() const { return indices; }

private:
	std::vector<unsigned int> indices;
	std::vector<Shape::IVertex*> vertices;

};
	}
}