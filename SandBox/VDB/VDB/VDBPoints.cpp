#include "VDBPoints.h"

#include "VDBPointsImpl.h"

#include "Converter.h"

#include <openvdb/points/PointConversion.h>

using namespace Crystal::Math;
using namespace Crystal::VDB;

VDBPoints::VDBPoints()
{
    impl = std::make_unique<VDBPointsImpl>();
}

VDBPoints::~VDBPoints()
{
}

void VDBPoints::create(const std::vector<Vector3df>& positions)
{
    std::vector<openvdb::Vec3f> coords;
    for (const auto& p : positions) {
        coords.push_back(Converter::toVDB(p));
    }

    const auto transform = openvdb::math::Transform::createLinearTransform();
    //auto ptr = openvdb::points::createPointDataGrid<openvdb::points::NullCodec, openvdb::points::PointDataGrid>(coords, transform);
    auto ptr = openvdb::points::createPointDataGrid<openvdb::points::NullCodec, openvdb::points::PointDataGrid>(coords, *transform);

    impl->setPtr(ptr);
    //this->impl->setPtr()
}

Box3df VDBPoints::getBoundingBox() const
{
    const auto size = impl->size();
    if (size == 0) {
        return Box3df::createDegeneratedBox();
    }
    const auto positions = getPositions();
    Box3df box(positions.front());
    for (int i = 0; i < size; ++i) {
        box.add(positions[i]);
    }
    return box;
}

std::vector<Vector3df> VDBPoints::getPositions() const
{
    std::vector<Vector3df> positions;
    const auto ps = impl->getPositions();
    for (int i = 0; i < impl->size(); ++i) {
        positions.emplace_back(Converter::fromVDB(ps[i]));
    }
    return positions;
}

void VDBPoints::resetImpl()
{
    this->impl = std::make_unique<VDBPointsImpl>();
}

void VDBPoints::addFloatAttribute(const std::string& name)
{
    this->impl->addFloatAttribute(name);
}

void VDBPoints::setFloatAttribute(const std::string& name, const std::vector<float>& values)
{
    this->impl->setFloatAttributes(name, values);
}

std::vector<float> VDBPoints::getFloatAttribute(const std::string& name)
{
    return this->impl->getFloatAttributes(name);
}

bool VDBPoints::hasAttribute(const std::string& name)
{
    return this->impl->hasAttribute(name);
}

std::vector<std::string> VDBPoints::getAttributeNames() const
{
    const auto names = this->impl->getAttributeNames();
    std::vector<std::string> results;
    for (const auto& n : names) {
        results.push_back(n);
    }
    return results;
}

std::vector<std::string> VDBPoints::getFloatAttributeNames() const
{
    const auto names = this->impl->getAttributeNames();
    std::vector<std::string> results;
    for (const auto& n : names) {
        if (n == "P") {
            continue;
        }
        results.push_back(n);
    }
    return results;

}
