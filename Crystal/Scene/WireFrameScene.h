#pragma once

#include "IScene.h"
#include <vector>

namespace Crystal {
	namespace Scene {
		class IVertex;

class WireFrameScene : public IScene
{
public:
	void add(IVertex* v);

	std::vector<IVertex*> getVertices() const { return vertices; }

private:
	std::vector<unsigned int> indices;
	std::vector<IVertex*> vertices;
};

	}
}