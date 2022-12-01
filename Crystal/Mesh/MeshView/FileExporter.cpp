#include "FileExporter.h"

#include "Crystal/File/File/OBJFileWriter.h"
#include "Crystal/File/File/STLFileWriter.h"

using namespace Crystal::Math;
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
	STLFile stl;
	stl.faceCount = this->faces.size();
	for (const auto& f : this->faces) {
		STLFace sf;
		const auto v0 = positions[ this->vertices[f.v0].positionIndex ];
		const auto v1 = positions[ this->vertices[f.v1].positionIndex ];
		const auto v2 = positions[ this->vertices[f.v2].positionIndex ];
		Triangle3df t({ v0, v1, v2 });
		sf.triangle = t;
		sf.normal = normals[this->vertices[f.v0].normalIndex];
		stl.faces.push_back(sf);
	}
	STLFileWriter writer;
	const bool isOk = writer.writeAscii(path, stl);
	return isOk;
}