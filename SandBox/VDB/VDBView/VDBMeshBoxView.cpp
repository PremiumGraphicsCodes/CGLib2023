#include "VDBMeshBoxView.h"

#include "../VDB/VDBMesh.h"
#include "World.h"

using namespace Crystal::Math;
using namespace Crystal::UI;
using namespace Crystal::VDB;

VDBMeshBoxView::VDBMeshBoxView(const std::string& name, World* world, Renderer* renderer) :
	IOkCancelView(name),
	world(world)
{
}

void VDBMeshBoxView::onOk()
{
	auto mesh = std::make_unique<VDBMesh>();
	// cube vertices

	mesh->addVertex(Vector3dd(2, 2, 2)); // 0       6--------7
	mesh->addVertex(Vector3dd(5, 2, 2)); // 1      /|       /|
	mesh->addVertex(Vector3dd(2, 5, 2)); // 2     2--------3 |
	mesh->addVertex(Vector3dd(5, 5, 2)); // 3     | |      | |
	mesh->addVertex(Vector3dd(2, 2, 5)); // 4     | 4------|-5
	mesh->addVertex(Vector3dd(5, 2, 5)); // 5     |/       |/
	mesh->addVertex(Vector3dd(2, 5, 5)); // 6     0--------1
	mesh->addVertex(Vector3dd(5, 5, 5)); // 7

	// cube faces
	mesh->addQuad({ 0, 1, 3, 2 }); // front
	mesh->addQuad({ 5, 4, 6, 7 }); // back
	mesh->addQuad({ 0, 2, 6, 4 }); // left
	mesh->addQuad({ 1, 5, 7, 3 }); // right
	mesh->addQuad({ 2, 3, 7, 6 }); // top
	mesh->addQuad({ 0, 4, 5, 1 }); // bottom

	mesh->updateNormals();

	world->add(std::move(mesh));
}