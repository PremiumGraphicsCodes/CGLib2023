#pragma once

#include <vector>
#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class Image
{
public:
	Image();

	Image(const int width, const int height);

	Image(const int width, const int height, const std::vector< T >& values);

	void setColor(const int i, const int j, const ColorRGBA<T>& c);

	ColorRGBA<T> getColor(const int x, const int y) const;

	std::vector<T> getValues() const { return values; }

	int getWidth() const { return width; }

	int getHeight() const { return height; }

private:
	int getIndex1d(const int x, const int y) const { return (y * width + x) * 4; }

	int width;
	int height;
	std::vector<T> values;
};

using Imageuc = Image<unsigned char>;
using Imagef = Image<float>;

	}
}