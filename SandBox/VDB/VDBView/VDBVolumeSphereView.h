#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/FloatView.h"

namespace Crystal {
	namespace UI {
		class World;

class VDBVolumeSphereView : public IOkCancelView
{
public:
	VDBVolumeSphereView(const std::string& name, World* world);

private:
	void onOk() override;

private:
	World* world;
	FloatView scaleView;
};

	}
}