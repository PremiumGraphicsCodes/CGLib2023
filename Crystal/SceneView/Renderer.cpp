#include "Renderer.h"

#include "CGLib/Graphics/ColorRGBA.h"
#include "CGLib/Shader/ShaderBuilder.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Shader;
using namespace Crystal::UI;
using namespace Crystal::Renderer;

void Renderer::build()
{
	ShaderBuilder builder;
	builder.buildFromFile("../GLSL/Point.vs", "../GLSL/Point.fs");
	point.setShader(builder.getShader());
	point.link();
}
