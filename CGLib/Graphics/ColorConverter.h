#pragma once

#include "ColorHSV.h"

namespace Crystal {
	namespace Graphics {

class ColorConverter
{
	static ColorRGBf convertHSVtoRGBf(const ColorHSV& hsv)
	{
		return ColorRGBf();
	}

	static ColorRGBuc convertHSVToRGBuc(const ColorHSV& hsv)
	{
		return ColorRGBuc();
	}

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