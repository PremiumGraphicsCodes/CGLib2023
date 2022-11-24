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

	/*
	for (auto iter = grid->cbeginValueOn(); iter; ++iter) {
		//auto c = iter.getCoord();
		auto coord = transform.indexToWorld(iter.getCoord());
		auto value = *iter;
		const auto c = colorMap.getColor((float)value);
		//position.add(
		//pb.add(Converter::fromVDB(coord), c, 1.0f);
	}
	//this->view->send(pb);

	//count = static_cast<int>(particles.size());
	*/
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
