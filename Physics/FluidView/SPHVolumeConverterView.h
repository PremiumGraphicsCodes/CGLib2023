#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/FloatView.h"
#include "CGLib/UI/ColorMapView.h"

namespace Crystal {
	namespace Physics {
		class KFFluidScene;
	}
	namespace UI {
		class World;
		class Renderer;

class SPHVolumeConverterView : public IOkCancelView
{
public:
	SPHVolumeConverterView(const std::string& name, World* model, Renderer* renderer);

private:
	void onOk() override;

private:
	FloatView particleRadiusView;
	FloatView thresholdView;
	FloatView cellLengthView;
	ColorMapView colorMapView;
	World* world;
	Renderer* renderer;
};

	}
}