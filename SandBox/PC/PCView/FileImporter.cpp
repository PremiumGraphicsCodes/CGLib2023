#include "FileImporter.h"

#include "Crystal/File/File/PLYFileReader.h"
#include "../PC/PCDFileReader.h"
#include "../PC/TXTFileReader.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::PC;

bool FileImporter::import(const std::filesystem::path& path)
{
	const auto ext = path.extension();
	if (ext == ".ply") {
		return importPLY(path);
	}
	else if (ext == ".pcd") {
		return importPCD(path);
	}
	else if (ext == ".txt") {
		return importTXT(path);
	}
	return false;
}

bool FileImporter::importPCD(const std::filesystem::path& path)
{
	PCDFileReader reader;
	const auto isOk = reader.read(path);
	if (!isOk) {
		return false;
	}
	this->pointCloud = std::make_unique<PointCloud>();
	const auto positions = reader.getPCD().data.positions;
	for (const auto& p : positions) {
		const ColorRGBAf c(1, 1, 1, 1);
		this->pointCloud->add(std::make_unique<Point>(p, c));
	}
	return true;
}

bool FileImporter::importPLY(const std::filesystem::path& path)
{
	PLYFileReader reader;
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
}

bool FileImporter::importTXT(const std::filesystem::path& path)
{
	TXTFileReader reader;
	const auto isOk = reader.read(path);
	if (!isOk) {
		return false;
	}
	this->pointCloud = std::make_unique<PointCloud>();
	const auto points = reader.getPositions();
	for (const auto& p : points) {
		const ColorRGBAf c(1, 1, 1, 1);
		this->pointCloud->add(std::make_unique<Point>(p, c));
	}
	return true;
}
