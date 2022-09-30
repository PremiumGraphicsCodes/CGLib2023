#include "WireFrameBuilder.h"

#include "../Math/ICurve3d.h"

using namespace Crystal::Math;
using namespace Crystal::Shape;

void WireFrameBuilder::add(const ICurve3d<float>& curve, int unum)
{
	assert(2 <= unum);
	std::vector<int> indices;
	for (int i = 0; i <= unum; ++i) {
		const float u = i / static_cast<float>(unum);
		indices.push_back( createPosition( curve.getPosition(u) ) );
	}
	for (int i = 0; i < indices.size() -1; ++i) {
		edges.push_back(WireFrame::Edge(indices[i], indices[i + 1]));
	}
}

int WireFrameBuilder::createPosition(const Vector3df& v)
{
	positions.push_back(v);
	return static_cast<int>(positions.size() - 1);
}

/*
std::unique_ptr<WireFrame> WireFrameBuilder::toWireFrame()
{
	WireFrame wf;
	wf.add()
	return std::make_unique<WireFrame>(positions, edges);
}
*/