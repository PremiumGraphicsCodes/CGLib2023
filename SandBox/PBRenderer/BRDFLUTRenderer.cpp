#include "BRDFLUTRenderer.h"

#include "CGLib/Math/Box2d.h"
#include "CGLib/Shader/VertexAttribute.h"

using namespace Crystal::Math;
using namespace Crystal::Shader;
using namespace Crystal::Renderer;

namespace {
	constexpr auto positionLabel = "aPos";
	constexpr auto texCoordLabel = "aTexCoords";
	constexpr auto fragColorLabel = "FragColor";

	struct Attributes
	{
		GLuint position;
		GLuint texCoord;
	};
	Attributes attr;
}

void BRDFLUTRenderer::link()
{
	attr.position = shader->findAttribLocation(::positionLabel);
	attr.texCoord = shader->findAttribLocation(::texCoordLabel);
}

namespace {
	std::vector<float> toArray(const Box2d<float>& box)
	{
		const auto min = box.getMin();
		const auto max = box.getMax();
		return{
			min.x, max.y,
			min.x, min.y,
			max.x, min.y,
			max.x, max.y
		};
	}

	std::vector<float> getTexCoords()
	{
		return {
			0.0, 1.0,
			0.0, 0.0,
			1.0, 0.0,
			1.0, 1.0
		};
	}
}

void BRDFLUTRenderer::render()
{
	const Box2d<float> box(Vector2df(-1.0, -1.0), Vector2df(1.0, 1.0));
	const auto positions = ::toArray(box);
	const auto texCoords = getTexCoords();

	shader->bind();
	shader->bindOutput(::fragColorLabel, 0);

	VertexAttribute posAttr(attr.position);
	VertexAttribute texCoordAttr(attr.texCoord);

	posAttr.sendVertexAttribute2df(positions);
	texCoordAttr.sendVertexAttribute2df(texCoords);

	shader->drawQuads(positions.size() / 2);

	shader->unbind();
}