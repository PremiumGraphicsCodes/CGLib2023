#include "WireFrameScene.h"

using namespace Crystal::Scene;

void WireFrameScene::add(IVertex* v)
{
	this->vertices.push_back(v);
}