#include "WireFrame.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

void WireFrame::add(std::unique_ptr<IVertex> v)
{
	this->vertices.push_back(std::move(v));
}

void WireFrame::addEdge(const Edge& edge)
{
	this->edges.push_back(edge);
}

