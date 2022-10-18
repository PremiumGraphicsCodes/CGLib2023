#include "Renderer.h"

using namespace Crystal::UI;

void Renderer::init()
{
	polygon.build();
	ibl.build();
	pbLight.build();
}
