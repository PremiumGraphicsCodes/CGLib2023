#pragma once

#include <string>
#include <vector>

#include "CGLib/Math/Vector3d.h"

namespace Crystal {
    namespace VDB {
        class VDBPoints;
        class VDBVolume;

class VDBFileReader
{
public:
    VDBFileReader() {}

    ~VDBFileReader();

    bool open(const std::string& filename);

    void close();

    void readMetaData();

    std::vector<std::string> getPointNames() const { return pointNames; }

    std::vector<std::string> getGridNames() const { return floatGridNames; }

    VDBPoints* readPositions(const std::string& pointName, const float radius);

    VDBVolume* readVolume(const std::string& volumeName);

private:
    std::vector<std::string> pointNames;
    std::vector<std::string> floatGridNames;
};

    }
}