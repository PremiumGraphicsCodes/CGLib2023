#include "CameraMenu.h"
#include "Canvas.h"
#include "MenuItem.h"

using namespace Crystal::UI;

CameraMenu::CameraMenu(const std::string& name) :
	IMenu(name)
{
	add(new MenuItem("Fit", [&] { onFit(); }));
	add(new MenuItem("XY", [&] { onXY(); }));
	add(new MenuItem("YZ", [&] { onYZ(); }));
	add(new MenuItem("ZX", [&] { onZX(); }));
}

void CameraMenu::onFit()
{
	/*
	const auto boundingBox = world->getBoundingBox();
		auto camera = world->getCamera()->getCamera();
		const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
		camera->setNear(dist * 0.1f);
		camera->setFar(dist * 10.0f);
		camera->lookAt(boundingBox.getCenter() - Vector3dd(0, 0, dist * 0.5), boundingBox.getCenter(), Vector3dd(0, 1, 0));
		//world->getCamera()->getPresenter()->updateView();
		return true;
		*/
}

void CameraMenu::onXY()
{
	/*
	const auto boundingBox = world->getBoundingBox();
	auto camera = world->getCamera()->getCamera();
	const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->lookAt(boundingBox.getCenter() - Vector3dd(0, 0, dist * 2.0), boundingBox.getCenter(), Vector3dd(0, 1, 0));
	*/
}

void CameraMenu::onYZ()
{
	/*
		const auto boundingBox = world->getBoundingBox();
	auto camera = world->getCamera()->getCamera();
	const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->lookAt(boundingBox.getCenter() - Vector3dd(dist * 2.0, 0, 0), boundingBox.getCenter(), Vector3dd(0, 0, 1));
	*/

}

void CameraMenu::onZX()
{
	/*
	const auto boundingBox = world->getBoundingBox();
	auto camera = world->getCamera()->getCamera();
	const auto& dist = static_cast<float>(glm::distance(boundingBox.getMin(), boundingBox.getMax()));
	camera->setNear(dist * 0.1f);
	camera->setFar(dist * 10.0f);
	camera->lookAt(boundingBox.getCenter() - Vector3dd(0, dist * 2.0, 0), boundingBox.getCenter(), Vector3dd(1, 0, 0));
	*/
}