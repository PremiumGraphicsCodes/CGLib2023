#pragma once

#include <vector>
#include <memory>

#include "../Math/Vector3d.h"

#include "WireFrame.h"

namespace Crystal {
	namespace Math {
		template<typename T>
		class ICurve3d;
		template<typename T>
		class ISurface3d;
		template<typename T>
		class IVolume3d;
	}
	namespace Shape {

class WireFrameBuilder
{
public:
	void add(const Math::ICurve3d<float>& curve, int unum);

	//void add(const Math::ISurface3d<float>& surface, const int unum, const int vnum);

	//void add(const Math::IVolume3d<float>& volume, const int unum, const int vnun, const int wnum);

	//std::unique_ptr<WireFrame> toWireFrame();

private:
	int createPosition(const Math::Vector3df& v);

	void addEdge(const WireFrame::Edge& e) { this->edges.push_back(e); }

	std::vector<Math::Vector3df> positions;
	std::vector<WireFrame::Edge> edges;
};

	}
}