#include "Renderer.h"
#include "World.h"

using namespace Crystal::UI;

void Renderer::init()
{
	polygon.build();
	ibl.build();
	pbLight.build();

	this->active = &polygon;
}

void Renderer::setTarget(const Target target)
{
	switch (target) {
		case Target::IBL:
		{
			this->active = &ibl;
			break;
		}
		case Target::DFPolygon:
		{
			this->active = &polygon;
			break;
		}
		case Target::PBLight:
		{
			this->active = &pbLight;
			break;
		}
		default:
		{
			assert(false);
		}
	}
}

void Renderer::render(const int width, const int height)
{
	const auto camera = world->getCamera();
	this->active->render(*camera, width, height);
}
