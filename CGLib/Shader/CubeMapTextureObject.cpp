#include "CubeMapTextureObject.h"

#include "glew.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void CubeMapTextureObject::create()
{
	glGenTextures(1, &handle);
}

void CubeMapTextureObject::send(const std::array<Imagef, 6>& images)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, handle);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, images[0].getWidth(), images[0].getHeight(), 0, GL_RGBA, GL_FLOAT, images[0].getValues().data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, images[1].getWidth(), images[1].getHeight(), 0, GL_RGBA, GL_FLOAT, images[1].getValues().data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, images[2].getWidth(), images[2].getHeight(), 0, GL_RGBA, GL_FLOAT, images[2].getValues().data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, images[3].getWidth(), images[3].getHeight(), 0, GL_RGBA, GL_FLOAT, images[3].getValues().data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, images[4].getWidth(), images[4].getHeight(), 0, GL_RGBA, GL_FLOAT, images[4].getValues().data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, images[5].getWidth(), images[5].getHeight(), 0, GL_RGBA, GL_FLOAT, images[5].getValues().data());

	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	//glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMapTextureObject::send(const std::array<Imageuc, 6>& images)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, handle);

	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, images[0].getWidth(), images[0].getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, images[0].getValues().data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, images[1].getWidth(), images[1].getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, images[1].getValues().data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, images[2].getWidth(), images[2].getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, images[2].getValues().data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, images[3].getWidth(), images[3].getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, images[3].getValues().data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, images[4].getWidth(), images[4].getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, images[4].getValues().data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, images[5].getWidth(), images[5].getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, images[5].getValues().data());

	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	//glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}



void CubeMapTextureObject::bind() const
{
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, handle);
}

void CubeMapTextureObject::unbind() const
{
	glDisable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMapTextureObject::setPositiveX(const Imagef& image)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, handle);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_FLOAT, image.getValues().data());
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

/*
void CubeMapTextureObject::setPositiveX(const Image& image)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, handle);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getValues().data());
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
*/

void CubeMapTextureObject::setNegativeX(const Imagef& image)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, handle);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_FLOAT, image.getValues().data());
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMapTextureObject::setPositiveY(const Imagef& image)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, handle);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_FLOAT, image.getValues().data());
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMapTextureObject::setNegativeY(const Imagef& image)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, handle);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_FLOAT, image.getValues().data());
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMapTextureObject::setPositiveZ(const Imagef& image)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, handle);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_FLOAT, image.getValues().data());
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMapTextureObject::setNegativeZ(const Imagef& image)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, handle);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_FLOAT, image.getValues().data());
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMapTextureObject::remove()
{
	glDeleteTextures(1, &handle);
}

void CubeMapTextureObject::setParameter(const GLenum type, const GLuint value)
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, handle);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, type, value);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	assert(GL_NO_ERROR == glGetError());
}