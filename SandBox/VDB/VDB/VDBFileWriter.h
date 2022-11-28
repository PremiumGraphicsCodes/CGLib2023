#pragma once

#include <string>
#include <vector>
#include "CGLib/Math/Vector3d.h"

namespace Crystal {
    namespace VDB {
        class VDBPoints;
        class VDBVolume;

class VDBFileWriter
{
public:
    ~VDBFileWriter();

    bool open(const std::string& filePath);

    void close();

    void writePoints(const std::string& name, VDBPoints* positions) const;

    void writeVolumes(const std::vector<VDBVolume*>& volumes) const;

private:
};

    }
}