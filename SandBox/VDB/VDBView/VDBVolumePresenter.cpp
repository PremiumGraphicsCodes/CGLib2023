#include "VDBVolumePresenter.h"
#include "VDBVolumeScene.h"

#include "../VDB/VDBVolume.h"

#include "CGLib/Graphics/ColorTable.h"
#include "CGLib/Graphics/ColorHSV.h"
#include "CGLib/Graphics/ColorConverter.h"

using namespace Crystal::Graphics;
using namespace Crystal::VDB;

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

void VDBVolumePresenter::build()
{
	vbo.position.create();
	vbo.size.create();
	vbo.color.create();

	this->colorMap = ColorMap(0.0f, 1.0f, ::createDefaultTable(270));
}

void VDBVolumePresenter::send()
{
	Shader::VertexBuffer<float> position;
	Shader::VertexBuffer<float> color;
	Shader::VertexBuffer<float> size;

	const auto nodes = model->getShape()->getActiveNodes();

	for (const auto& n : nodes) {
		position.add(n.position);
		const auto c = this->colorMap.getColor(n.value);
		color.add(c);
		size.add(10.0f);
	}

	vbo.position.send(position);
	vbo.color.send(color);
	vbo.size.send(size);

	count = static_cast<int>(nodes.size());
}

void VDBVolumePresenter::render(const Camera& camera)
{
	view->buffer.position = &vbo.position;
	view->buffer.size = &vbo.size;
	view->buffer.color = &vbo.color;
	view->buffer.count = count;
	view->buffer.modelViewMatrix = camera.getModelViewMatrix();
	view->buffer.projectionMatrix = camera.getProjectionMatrix();

	view->render();
}
