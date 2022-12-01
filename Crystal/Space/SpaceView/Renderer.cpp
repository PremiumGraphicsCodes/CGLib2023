#include "Renderer.h"
#include "CGLib/Shader/ShaderBuilder.h"
#include "Crystal/Renderer/Renderer/PointShaderSource.h"

using namespace Crystal::Shader;
using namespace Crystal::UI;
using namespace Crystal::Renderer;

void Renderer::init()
{
	ShaderBuilder builder;
	builder.build(PointShaderSource::getVertexShaderSource(), PointShaderSource::getFragmentShaderSource());
	point.setShader(builder.getShader());
	point.link();
}