#include "PBSPHFlamePresenter.h"
#include "PBSPHFluidScene.h"

#include "CGLib/Graphics/ColorHSV.h"
#include "CGLib/Graphics/ColorConverter.h"

using namespace Crystal::Graphics;
using namespace Crystal::Scene;
using namespace Crystal::Physics;

namespace {
	ColorTable createDefaultTable(const int resolution)
	{
		ColorTable table(270);
		for (int i = 0; i < 270; ++i) {
			ColorHSV hsv(i * 1.0f, 1.0, 1.0);
			const auto rgb = ColorConverter::convertHSVtoRGBf(hsv);
			const ColorRGBAf c(rgb, 0.0);
			table.setColor(269 - i, c);
		}
		return table;
	}
}


void PBSPHFlamePresenter::build()
{
	vbo.position.create();
	vbo.size.create();
	vbo.color.create();

	const ColorTable table = ::createDefaultTable(270);
	this->colorMap = ColorMap(300.0, 700.0, table);
}

void PBSPHFlamePresenter::send()
{
	Shader::VertexBuffer<float> position;
	Shader::VertexBuffer<float> color;
	Shader::VertexBuffer<float> size;

	const auto& particles = model->getFluid()->getParticles();
	for (auto& p : particles) {
		position.add(p->getPosition());
		const auto c = this->colorMap.getInterpolatedColor(p->getTemperature());
		color.add(c);
		size.add(100);
	}

	vbo.position.send(position);
	vbo.color.send(color);
	vbo.size.send(size);

	count = static_cast<int>(particles.size());
}

void PBSPHFlamePresenter::render(const Camera& camera)
{
	view->buffer.position = &vbo.position;
	view->buffer.size = &vbo.size;
	view->buffer.color = &vbo.color;
	view->buffer.count = count;
	view->buffer.modelViewMatrix = camera.getModelViewMatrix();
	view->buffer.projectionMatrix = camera.getProjectionMatrix();

	view->render();
}