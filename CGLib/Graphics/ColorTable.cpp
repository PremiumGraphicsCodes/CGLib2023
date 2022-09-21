#include "ColorTable.h"

using namespace Crystal::Graphics;

ColorTable::ColorTable(const int resolution) :
	colors(resolution)
{
}

int ColorTable::getResolution() const
{
	return static_cast<int>(colors.size());
}

void ColorTable::setColor(const int index, const ColorRGBAf& color)
{
	colors[index] = color;
}

ColorRGBAf ColorTable::getColor(const int i) const
{
	if (i >= colors.size()) {
		return colors.back();
	}
	return colors[i];
}
