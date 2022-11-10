#include "PointCloudBuilder.h"

#include "CGLib/Math/ICurve3d.h"
#include "CGLib/Math/ISurface3d.h"
#include "CGLib/Math/IVolume3d.h"

using namespace Crystal::Math;
using namespace Crystal::PC;

void PointCloudBuilder::add(const ICurve3d<float>& curve, int unum)
{
	assert(1 <= unum);
	for (int i = 0; i <= unum; ++i) {
		const float u = i / static_cast<float>(unum);
		positions.push_back(curve.getPosition(u));
	}
}

void PointCloudBuilder::add(const ISurface3d<float>& surface, const int unum, const int vnum)
{
	assert(1 <= unum);
	assert(1 <= vnum);

	for (int i = 0; i <= unum; ++i) {
		const float u = i / static_cast<float>(unum);
		for (int j = 0; j <= vnum; ++j) {
			const float v = j / static_cast<float>(vnum);
			positions.push_back(surface.getPosition(u, v));
		}
	}
}

void PointCloudBuilder::add(const IVolume3d<float>& volume, const int unum, const int vnum, const int wnum)
{
	assert(1 <= unum);
	assert(1 <= vnum);
	assert(1 <= wnum);

	for (int i = 0; i <= unum; ++i) {
		const float u = i / static_cast<float>(unum);
		for (int j = 0; j <= vnum; ++j) {
			const float v = j / static_cast<float>(vnum);
			for (int k = 0; k <= wnum; ++k) {
				const float w = k / static_cast<float>(wnum);
				positions.push_back(volume.getPosition(u, v, w));
			}
		}
	}
}

std::unique_ptr<PointCloud> PointCloudBuilder::toPointCloud()
{
	auto ps = std::make_unique<PointCloud>();
	for (const auto& p : positions) {
		ps->add(std::make_unique<Point>(p));
	}
	return ps;
}