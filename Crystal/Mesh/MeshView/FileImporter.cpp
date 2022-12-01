#include "FileImporter.h"

#include "Crystal/File/File/OBJFileReader.h"
#include "Crystal/File/File/STLFileReader.h"

#include "../Mesh/PolygonMesh.h"
#include "../Mesh/PolygonMeshBuilder.h"

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
	/*
	OBJFileReader reader;
	const auto isOk = reader.read(path);
	if (!isOk) {
		return false;
	}

	this->mesh = std::make_unique<PolygonMesh>();
	const auto obj = reader.getOBJ();
	const auto positions = obj.positions;
	const auto normals = obj.normals;
	const auto texCoords = obj.texCoords;
	const auto groups = obj.groups;
	for (const auto& p : positions) {
		this->mesh->addPosition(p);
	}
	for (const auto& n : normals) {
		this->mesh->addNormal(n);
	}
	for (const auto& t : texCoords) {
		this->mesh->addTexCoord(t);
	}
	for (const auto& g : groups) {
		const auto faces = g.faces;
		for (const auto& f : faces) {
			const auto& vs = f.positionIndices;
			const auto& ns = f.normalIndices;
			const auto& ts = f.texCoordIndices;
			//this->mesh->addVertex()
		}
	}
	*/
	return false;
}

bool FileImporter::importSTL(const std::filesystem::path& path)
{
	STLFileReader reader;
	const auto isOk = reader.readAscii(path);
	if (!isOk) {
		return false;
	}

	PolygonMeshBuilder builder;
	const auto stl = reader.getSTL();
	assert(stl.faceCount == stl.faces.size());
	for (const auto& f : stl.faces) {
		const auto vertices = f.triangle.getVertices();
		const auto p0 = builder.createPosition(vertices[0]);
		const auto p1 = builder.createPosition(vertices[1]);
		const auto p2 = builder.createPosition(vertices[2]);
		builder.createFace(p0, p1, p2);
		//const auto n0 = builder.createNormal(f.normal);
		//const auto t0 = builder.createTexCoord(Vector2df(0, 0));
		//const auto v0 = builder.createVertex(p0, n0, t0);
	}
	this->mesh = builder.build();
	return true;
}