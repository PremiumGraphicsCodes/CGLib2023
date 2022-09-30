#include "WireFrame.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

void WireFrame::add(IVertex* v)
{
	this->vertices.push_back(v);
}
