#pragma once

#include "../Math/glm.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
using ColorRGB = glm::vec<3, T>;

using ColorRGBf = ColorRGB<float>;
using ColorRGBuc = ColorRGB<glm::u8>;

static ColorRGBuc toColorRGBuc(const ColorRGBf& color)
{
	const auto r = static_cast<unsigned char>(color.r * 255);
	const auto g = static_cast<unsigned char>(color.g * 255);
	const auto b = static_cast<unsigned char>(color.b * 255);
	return ColorRGBuc(r, g, b);
}

	}
}