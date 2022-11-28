#pragma once

#include "CGLib/UI/IOkCancelView.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;

class VDBMeshBoxView : public IOkCancelView
{
public:
	VDBMeshBoxView(const std::string& name, World* model, Renderer* canvas);

private:
	void onOk() override;
	
	World* world;
};

	}
}