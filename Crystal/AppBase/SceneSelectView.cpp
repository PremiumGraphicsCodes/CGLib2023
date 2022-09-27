#include "SceneSelectView.h"

using namespace Crystal::UI;
using namespace Crystal::Scene;

SceneSelectView::SceneSelectView(const std::string& name, WorldBase* model, RendererBase* canvas) :
	IView(name),
	idView("Id", 0)
{
	add(&idView);
}