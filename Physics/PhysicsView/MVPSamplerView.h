#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/IView.h"

#include "World.h"
#include "Renderer.h"

namespace Crystal {
	namespace UI {

class MVPSamplerView : public IView
{
public:
	MVPSamplerView(const std::string& name, World* model, Renderer* renderer);

private:
	void onSplit();

	void onMerge();

	World* world;
	Renderer* renderer;
	Button splitButton;
	Button mergeButton;
};

	}
}