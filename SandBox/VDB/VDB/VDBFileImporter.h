#pragma once

#include <string>

namespace Crystal {
	namespace VDB {
		class VDBPoints;
		class VDBMesh;

class VDBFileImporter
{
public:
	//VDBScene* read(const std::string& filePath, const Format format);

	VDBPoints* readPLY(const std::string& filePath);

	VDBPoints* readPCD(const std::string& filePath);

	VDBMesh* readOBJ(const std::string& filePath);

	VDBMesh* readSTL(const std::string& filePath);
};

	}
}