#pragma once

#include "ColorRGB.h"
#include <cassert>

namespace Crystal {
	namespace Graphics {

class ColorHSV
{
public:
	ColorHSV() :
		h(0.0),
		s(0.0),
		v(0.0)
	{}

	ColorHSV(const float h, const float s, const float v) :
		h(h),
		s(s),
		v(v)
	{}

	float getH() const { return h; }

	float getS() const { return s; }

	float getV() const { return v; }

	void setH(const float h) { this->h = h; }

	void setS(const float s) { this->s = s; }

	void setV(const float v) { this->v = v; }

private:
	float h;
	float s;
	float v;
};

	}
}