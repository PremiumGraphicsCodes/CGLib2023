#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Box3dView.h"
#include "CGLib/UI/FloatView.h"
#include "CGLib/UI/IntView.h"
#include "CGLib/UI/ColorMapView.h"

namespace Crystal {
	namespace UI {
		class World;
		class Renderer;

class CurvatureEstimatorView : public IOkCancelView
{
public:
	CurvatureEstimatorView(const std::string& name, World* world, Renderer* renderer);

	void onOk() override;

private:
	FloatView searchRadiusView;
	IntView pcIdView;
	ColorMapView colorMapView;
	World* world;
	Renderer* renderer;
};

	}
}