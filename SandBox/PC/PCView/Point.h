#pragma once

#include "CGLib/Graphics/ColorRGBA.h"

namespace Crystal {
	namespace PC {

struct Point //: public IPoint
{
public:
	explicit Point(const Math::Vector3df& p) :
		color(1,1,1,1)
	{
		this->pos = p;
	}

	Point(const Math::Vector3df& p, const Graphics::ColorRGBAf& color) :
		color(color)
	{
		this->pos = p;
	}


	Math::Vector3df getPosition() const {
		return pos;
	}

	void setColor(const Graphics::ColorRGBAf& color) { this->color = color; }

	Graphics::ColorRGBAf getColor() const { return color; }

private:
	Math::Vector3df pos;
	Graphics::ColorRGBAf color;
};

	}
}