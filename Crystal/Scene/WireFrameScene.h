#pragma once

#include "IScene.h"
#include "IVertex.h"
#include <vector>

namespace Crystal {
	namespace Scene {
		class IVertex;

class WireFrameScene : public IScene
{
public:
	void add(IVertex* v);

	std::vector<IVertex*> getVertices() const { return vertices; }

	void addIndex(const unsigned int index) { this->indices.push_back(index); }

	std::vector<unsigned int> getIndices() const { return indices; }

private:
	std::vector<unsigned int> indices;
	std::vector<IVertex*> vertices;
};

	}
}