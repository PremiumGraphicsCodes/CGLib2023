#include "FileExporter.h"

#include "Crystal/File/File/OBJFileWriter.h"

using namespace Crystal::IO;
using namespace Crystal::Mesh;

void FileExporter::add(const PolygonMesh& mesh)
{
	this->vertices = mesh.getVertices();
	this->faces = mesh.getFaces();
	this->positions = mesh.getPositions();
	this->normals = mesh.getNormals();
	this->texCoords = mesh.getTexCoords();
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
	OBJFile file;
	file.positions = this->positions;
	file.normals = this->normals;
	file.texCoords = this->texCoords;

	OBJGroup group;
	for (const auto f : faces) {
		OBJFace objFace;
		objFace.positionIndices.push_back(this->vertices[f.v0].positionIndex +1);
		objFace.normalIndices.push_back(this->vertices[f.v0].normalIndex + 1);
		objFace.texCoordIndices.push_back(this->vertices[f.v0].texCoordIndex + 1);

		objFace.positionIndices.push_back(this->vertices[f.v1].positionIndex + 1);
		objFace.normalIndices.push_back(this->vertices[f.v1].normalIndex + 1);
		objFace.texCoordIndices.push_back(this->vertices[f.v1].texCoordIndex + 1);

		objFace.positionIndices.push_back(this->vertices[f.v2].positionIndex + 1);
		objFace.normalIndices.push_back(this->vertices[f.v2].normalIndex + 1);
		objFace.texCoordIndices.push_back(this->vertices[f.v2].texCoordIndex + 1);

		group.faces.push_back(objFace);
	}

	file.groups.push_back(group);

	OBJFileWriter writer;
	const bool isOk = writer.write(path, file);
	return isOk;
}

bool FileExporter::exportSTL(const std::filesystem::path& path)
{
	return false;
}