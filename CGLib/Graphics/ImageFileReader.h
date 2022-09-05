#pragma once

#include <string>
#include "Image.h"

namespace Crystal {
	namespace Graphics {

class ImageFileReader
{
public:
	bool read(const std::string& filepath);

	Graphics::Imageuc toImage() const;

private:
	int width;
	int height;
	int bpp;
	std::vector<unsigned char> data;
};

class HDRImageFileReader
{
public:
	bool read(const std::string& filepath);

	Graphics::Imagef toImage() const;

private:
	int width;
	int height;
	int bpp;
	std::vector<float> data;

};
	}
}