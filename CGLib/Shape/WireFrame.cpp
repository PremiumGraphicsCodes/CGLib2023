#include "WireFrame.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

void WireFrame::add(IVertex* v)
{
	this->vertices.push_back(v);
}

void WireFrame::addEdge(const Edge& edge)
{
	this->indices.push_back(edge.startIndex);
	this->indices.push_back(edge.endIndex);
}

