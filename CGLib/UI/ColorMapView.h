#pragma once

#include "IView.h"
#include "imgui.h"
#include "FloatView.h"
#include "IntView.h"
#include "../Graphics/ColorMap.h"

namespace Crystal {
	namespace UI {

class ColorMapView : public IView
{
public:
	explicit ColorMapView(const std::string& name);

	void onShow() override;

	Graphics::ColorMap getValue() const { return value; }

private:
	Graphics::ColorMap value;
	IntView resolution;
	FloatView minValue;
	FloatView maxValue;
};

	}
}