#pragma once

#include "CGLib/Math/Vector3d.h"
#include "CGLib/Math/Box3d.h"
#include "CGLib/Util/UnCopyable.h"

#include <vector>
#include <memory>
#include <string>

namespace Crystal {
    namespace VDB {
        class VDBPointsImpl;

class VDBPoints : public UnCopyable
{
public:
    VDBPoints();

    ~VDBPoints();

    void create(const std::vector<Math::Vector3df>& positions);

    VDBPointsImpl* getImpl() const { return impl.get(); }

    Math::Box3df getBoundingBox() const;

    std::vector<Math::Vector3df> getPositions() const;

    void resetImpl();

    void addFloatAttribute(const std::string& name);

    void setFloatAttribute(const std::string& name, const std::vector<float>& values);

    std::vector<float> getFloatAttribute(const std::string& name);

    bool hasAttribute(const std::string& name);

    std::vector<std::string> getAttributeNames() const;

    std::vector<std::string> getFloatAttributeNames() const;

private:
    std::unique_ptr<VDBPointsImpl> impl;
};

    }
}