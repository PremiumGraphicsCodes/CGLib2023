#include "VDBMesh.h"

#include "VDBMeshImpl.h"
#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::VDB;

VDBMesh::VDBMesh()
{
	impl = std::make_unique<VDBMeshImpl>();
}

VDBMesh::~VDBMesh()
{

}

void VDBMesh::addVertex(const Vector3df& position)
{
	impl->points.push_back(Converter::toVDB(position));
}

Vector3df VDBMesh::getVertex(const int index)
{
	return Converter::fromVDB(impl->points[index]);
}

std::vector<Vector3df> VDBMesh::getVerticesf() const
{
	return Converter::fromVDBf<Vector3df>(impl->points);
}

std::vector<Vector3dd> VDBMesh::getVerticesd() const
{
	return Converter::fromVDBf<Vector3dd>(impl->points);
}

void VDBMesh::addTriangle(const std::array<unsigned int, 3>& indices)
{
	VDBMeshImpl::TriangleFace triangle;
	triangle.indices = Converter::toVDB(indices);
	//triangle.normal = Converter::toVDB(normal);
	impl->triangles.push_back(triangle);
}

std::vector<VDBMesh::TriangleFace> VDBMesh::getTriangleFaces() const
{
	std::vector<VDBMesh::TriangleFace> faces;
	for (const auto& t : impl->triangles) {
		VDBMesh::TriangleFace face;
		face.indices = Converter::fromVDB(t.indices);
		face.normal = Converter::fromVDB(t.normal);
		faces.emplace_back(face);
	}
	return faces;
}

void VDBMesh::addQuad(const std::array<unsigned int, 4>& indices)
{
	VDBMeshImpl::QuadFace quad;
	quad.indices = Converter::toVDB(indices);
	//quad.normal = Converter::toVDB(normal);
	impl->quads.push_back(quad);
}

std::vector<VDBMesh::QuadFace> VDBMesh::getQuadFaces() const
{
	std::vector<VDBMesh::QuadFace> faces;
	for (const auto& q : impl->quads) {
		VDBMesh::QuadFace face;
		face.indices = Converter::fromVDB(q.indices);
		face.normal = Converter::fromVDB(q.normal);
		faces.emplace_back(face);
	}
	return faces;
}

std::vector<VDBMesh::Face> VDBMesh::getAllFaces() const
{
	std::vector<VDBMesh::Face> faces;
	for (const auto& t : impl->triangles) {
		VDBMesh::Face f;
		f.indices = { t.indices[0], t.indices[1], t.indices[2] };
		f.normal = Converter::fromVDB(t.normal);
		faces.emplace_back(f);
	}
	for (const auto& t : impl->quads) {
		VDBMesh::Face f;
		f.indices = { t.indices[0], t.indices[1], t.indices[2], t.indices[3] };
		f.normal = Converter::fromVDB(t.normal);
		faces.emplace_back(f);
	}
	return faces;
}

Box3df VDBMesh::getBoundingBox() const
{
	if (impl->points.empty()) {
		return Box3df::createDegeneratedBox();
	}
	auto vertices = this->getVerticesd();

	Math::Box3df box(vertices[0]);
	for (auto v : vertices) {
		box.add(v);
	}
	return box;
}

void VDBMesh::updateNormals()
{
	impl->updateNormals();
}

void VDBMesh::scale(const double scale)
{
	for (auto& p : impl->points) {
		p *= scale;
	}
}