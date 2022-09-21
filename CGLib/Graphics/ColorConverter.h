#pragma once

#include "ColorHSV.h"

namespace Crystal {
	namespace Graphics {

class ColorConverter
{
public:
	static ColorRGBf convertHSVtoRGBf(const ColorHSV& hsv);

	static ColorRGBuc convertHSVToRGBuc(const ColorHSV& hsv);

	static ColorHSV conertRGBToHSV(const ColorRGBf& rgb)
	{
		return ColorHSV();
	}

	static ColorHSV convertRGBToHSV(const ColorRGBuc& rgb)
	{
		return ColorHSV();
	}
	//static convertRGBtoHSV()
};
	}
}