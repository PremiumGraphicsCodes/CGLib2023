#include "VDBVolume.h"

#include "VDBVolumeImpl.h"
#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

using namespace openvdb;

VDBVolume::VDBVolume() :
	VDBVolume(0.0f)
{
	using FloatTreeType = openvdb::tree::Tree4<float, 5, 4, 3>::Type;
	using FloatGridType = openvdb::Grid<FloatTreeType>;
	auto grid = openvdb::createGrid<FloatGridType>();

	impl = std::make_unique<VDBVolumeImpl>(grid);
}

VDBVolume::VDBVolume(const float value)
{
	using FloatTreeType = openvdb::tree::Tree4<float, 5, 4, 3>::Type;
	using FloatGridType = openvdb::Grid<FloatTreeType>;
	auto grid = openvdb::createGrid<FloatGridType>(value);
	impl = std::make_unique<VDBVolumeImpl>(grid);
}

void VDBVolume::fill(const unsigned int coord1, const unsigned int coord2, const float value)
{
	openvdb::CoordBBox bbox;// openvdb::Coord(Int32(coord1)), openvdb::Coord(Int32(coord2)));
	bbox.reset(Coord(coord1), Coord(coord2));
	impl->getPtr()->tree().fill(bbox, value);

	//impl->getPtr()->tree().
}

void VDBVolume::setValue(const std::array<int, 3>& index, const float value)
{
	math::Coord coord(index[0], index[1], index[2]);
	impl->getPtr()->getAccessor().setValue(coord, value);
}

float VDBVolume::getValue(const std::array<int, 3> index)
{
	math::Coord coord(index[0], index[1], index[2]);
	return impl->getPtr()->getAccessor().getValue(coord);
}

int VDBVolume::getActiveVoxelCount() const
{
	return impl->getPtr()->activeVoxelCount();
}

Box3df VDBVolume::getBoundingBox() const
{
	auto grid = impl->getPtr();
	if (grid->empty()) {
		return Box3df::createDegeneratedBox();
	}
	auto transform = grid->transform();
	auto firstPos = transform.indexToWorld(grid->cbeginValueOn().getCoord());
	Box3df bb(Converter::fromVDB(firstPos));
	for (auto iter = grid->cbeginValueOn(); iter; ++iter) {
		auto coord = transform.indexToWorld(iter.getCoord());
		bb.add(Converter::fromVDB(coord));
	}
	return bb;
}

void VDBVolume::setScale(const float scale)
{
	impl->setScale(scale);
}
