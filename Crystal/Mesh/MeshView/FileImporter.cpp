#include "FileImporter.h"

#include "../Mesh/OBJFileReader.h"
#include "../Mesh/STLFileReader.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Mesh;
using namespace Crystal::IO;

bool FileImporter::import(const std::filesystem::path& path)
{
	const auto ext = path.extension();
	if (ext == ".obj") {
		return importOBJ(path);
	}
	else if (ext == ".stl") {
		return importSTL(path);
	}
	return false;
}

bool FileImporter::importOBJ(const std::filesystem::path& path)
{
	OBJFileReader reader;
	const auto isOk = reader.read(path);
	if (!isOk) {
		return false;
	}
	/*
	this->pointCloud = std::make_unique<PointCloud>();
	const auto positions = reader.getPCD().data.positions;
	for (const auto& p : positions) {
		const ColorRGBAf c(1, 1, 1, 1);
		this->pointCloud->add(std::make_unique<Point>(p, c));
	}
	return true;
	*/
	return false;
}

bool FileImporter::importSTL(const std::filesystem::path& path)
{
	/*
	STLFileReader reader;
	const auto isOk = reader.read(path);
	if (!isOk) {
		return false;
	}
	this->pointCloud = std::make_unique<PointCloud>();
	const auto vs = reader.getPLY().vertices;
	for (const auto& v : vs) {
		const auto x = v.getValueAs<float>(0);
		const auto y = v.getValueAs<float>(1);
		const auto z = v.getValueAs<float>(2);
		const Vector3df p(x, y, z);
		const ColorRGBAf c(1, 1, 1, 1);
		this->pointCloud->add(std::make_unique<Point>(p, c));
	}
	return true;
	*/
	return false;
}