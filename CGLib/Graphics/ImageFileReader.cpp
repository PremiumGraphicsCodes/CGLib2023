#include "ImageFileReader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../ThirdParty/stb/stb_image.h"

using namespace Crystal::Graphics;

bool ImageFileReader::read(const std::string& filepath)
{
	unsigned char* pixels;

	pixels = stbi_load("hoge.png", &width, &height, &bpp, 0);
	if (pixels == nullptr) {
		return false;
	}

	this->data.resize(width * height);
	for (int i = 0; i < this->data.size(); ++i) {
		this->data[i] = pixels[i];
	}

	stbi_image_free(pixels);
	return true;
}

Imageuc ImageFileReader::toImage() const
{
	return Imageuc(width, height, this->data);
}

