#include "Image.h"

using namespace Crystal::Graphics;

template<typename T>
Image<T>::Image() :
	width(0),
	height(0)
{}

template<typename T>
Image<T>::Image(const int width, const int height) :
	width(width),
	height(height),
	values(width* height * 4)
{}

template<typename T>
Image<T>::Image(const int width, const int height, const std::vector<T>& values) :
	width(width),
	height(height),
	values(values)
{
	assert((width * height * 4) == values.size());
}

template<typename T>
void Image<T>::setColor(const int i, const int j, const ColorRGBA<T>& c)
{
	const auto index = getIndex1d(i, j);
	values[index] = c.r;
	values[index + 1] = c.g;
	values[index + 2] = c.b;
	values[index + 3] = c.a;
}

template<typename T>
ColorRGBA<T> Image<T>::getColor(const int x, const int y) const
{
	const auto index = getIndex1d(x, y);
	const auto r = values[index];
	const auto g = values[index + 1];
	const auto b = values[index + 2];
	const auto a = values[index + 3];
	return ColorRGBAuc(r, g, b, a);
}

template class Image<float>;
template class Image<unsigned char>;