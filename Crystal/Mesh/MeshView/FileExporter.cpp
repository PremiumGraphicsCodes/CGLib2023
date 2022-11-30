#include "FileExporter.h"

#include "../Mesh/OBJFileWriter.h"

using namespace Crystal::IO;
using namespace Crystal::Mesh;

void FileExporter::add(const std::unique_ptr<PolygonMesh>& mesh)
{
	/*
	const auto& vertices = mesh->getVertices();
	for (const auto& v : vertices) {
		positions.push_back(v->position);
		normals.push_back(v->normal);
		texCoords.push_back(v->texCoord);
	}
	*/
}

bool FileExporter::export_(const std::filesystem::path& path)
{
	const auto ext = path.extension();
	if (ext == ".obj") {
		return exportOBJ(path);
	}
	else if (ext == ".stl") {
		return exportSTL(path);
	}
	return false;
}

bool FileExporter::exportOBJ(const std::filesystem::path& path)
{
	//OBJFile file;
	//file.positions.push_back()

	//OBJFileWriter writer;
	//writer.write()
	return false;
}

bool FileExporter::exportSTL(const std::filesystem::path& path)
{
	return false;
}