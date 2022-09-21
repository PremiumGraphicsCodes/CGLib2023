#pragma once

#include "CGLib/UI/IView.h"

#include "CGLib/UI/IntView.h"
#include "CGLib/UI/Button.h"

#include "WorldBase.h"
#include "RendererBase.h"

namespace Crystal {
	namespace UI {

class SceneSelectView : public IView
{
public:
	SceneSelectView(const std::string& name, WorldBase* model, RendererBase* renderer);

	int getId() const { return idView.getValue(); }

private:
	IntView idView;
	//Button pickButton;
	//Scene::SceneType type;

private:
	//void onPick(Scene::World* model, Canvas* canvas);
};

	}
}