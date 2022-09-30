#include "WireFrameBuilder.h"

#include "../Math/ICurve3d.h"
#include "../Math/ISurface3d.h"

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

void WireFrameBuilder::add(const ISurface3d<float>& surface, const int unum, const int vnum)
{
	assert(2 <= unum);
	assert(2 <= vnum);

	std::vector<std::vector<int>> grid;
	for (int i = 0; i <= unum; ++i) {
		const float u = i / static_cast<float>(unum);
		std::vector<int> g;
		for (int j = 0; j <= vnum; ++j) {
			const float v = i / static_cast<float>(vnum);
			g.push_back( createPosition(surface.getPosition(u, v)));
		}
		grid.push_back(g);
	}
	for (int i = 0; i < grid.size() - 1; ++i) {
		for (int j = 0; j < grid[i].size() - 1; ++j) {
			const auto v1 = grid[i][j];
			const auto v2 = grid[i + 1][j];
			const auto v3 = grid[i + 1][j + 1];
			const auto v4 = grid[i][j + 1];
			edges.push_back(WireFrame::Edge(v1, v2));
			edges.push_back(WireFrame::Edge(v2, v3));
			edges.push_back(WireFrame::Edge(v3, v4));
			edges.push_back(WireFrame::Edge(v4, v1));
		}
	}
}

int WireFrameBuilder::createPosition(const Vector3df& v)
{
	positions.push_back(v);
	return static_cast<int>(positions.size() - 1);
}

std::unique_ptr<WireFrame> WireFrameBuilder::toWireFrame()
{
	auto wf = std::make_unique<WireFrame>();
	for (const auto& p : positions) {
		wf->add(std::make_unique<Vertex>(p));
	}
	for (const auto& e : edges) {
		wf->addEdge(e);
	}
	return wf;
}
