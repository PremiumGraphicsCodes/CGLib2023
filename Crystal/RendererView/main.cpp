#include <stdio.h>
#include <iostream>

#include "PointShader.h"
#include "LineShader.h"
#include "TriangleShader.h"
#include "TexShader.h"

#include "PBLightShader.h"
#include "SkyBoxShader.h"
#include "DFPolygonShader.h"
#include "IBLShader.h"


#include "CGLib/Math/Vector2d.h"

#include "Crystal/AppBase/IRenderer.h"
#include "Crystal/AppBase/MenuItem.h"
#include "Crystal/AppBase/CameraUICtrl.h"
#include "Crystal/AppBase/Canvas.h"
#include "Crystal/AppBase/Window.h"


using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Renderer;

namespace {

	class Renderer : public Crystal::UI::IRenderer
	{
	public:
		Renderer() :
			camera(Vector3df(0, 0, 1), Vector3df(0, 0, 0), Vector3df(0, 1, 0), 0.1, 10.0)
		{}

		void init() override
		{
			pointRenderer.build();
			lineRenderer.build();
			triangleRenderer.build();
			texRenderer.build();
			pbLightRenderer.build();
			skyBoxRenderer.build();
			dfRenderer.build();
			iblRenderer.build();

			activeRenderer = &pointRenderer;
		}

		void render(const int width, const int height) override
		{
			glClearColor(0, 0, 0, 0);
			glClear(GL_COLOR_BUFFER_BIT);


			activeRenderer->render(camera, width, height);

		}

		Camera camera;

		PointShader pointRenderer;
		LineShader lineRenderer;
		TriangleShader triangleRenderer;
		TexShader texRenderer;

		PBLightShader pbLightRenderer;
		SkyBoxShader skyBoxRenderer;
		DFPolygonShader dfRenderer;
		IBLShader iblRenderer;
		IScreenShader* activeRenderer = &pbLightRenderer;

	};

	class RendererMenu : public Crystal::UI::IMenu
	{
	public:
		explicit RendererMenu(const std::string& name, Renderer* renderer) :
			IMenu(name)
		{
			add(new Crystal::UI::MenuItem("Point", [&renderer]() { renderer->activeRenderer = &renderer->pointRenderer; }));
			add(new Crystal::UI::MenuItem("Line", [&renderer]() { renderer->activeRenderer = &renderer->lineRenderer; }));
			add(new Crystal::UI::MenuItem("Triangle", [&renderer]() { renderer->activeRenderer = &renderer->triangleRenderer; }));
			add(new Crystal::UI::MenuItem("Tex", [&renderer]() { renderer->activeRenderer = &renderer->texRenderer; }));
			add(new Crystal::UI::MenuItem("SkyBox", [&renderer]() { renderer->activeRenderer = &renderer->skyBoxRenderer; }));
			add(new Crystal::UI::MenuItem("PBLight", [&renderer]() { renderer->activeRenderer = &renderer->pbLightRenderer; }));
			add(new Crystal::UI::MenuItem("DFPolygon", [&renderer]() { renderer->activeRenderer = &renderer->dfRenderer; }));
			add(new Crystal::UI::MenuItem("IBL", [&renderer]() { renderer->activeRenderer = &renderer->iblRenderer; }));
		}
	};
}


int main() {
	Renderer renderer;
	auto uiCtrl = std::make_unique<Crystal::UI::CameraUICtrl>(&renderer.camera);

	Crystal::UI::Canvas canvas(std::move(uiCtrl), &renderer);
	Crystal::UI::Window app("Hello", &canvas);
	app.init();
	app.add(new RendererMenu("Renderer", &renderer));

	app.show();
}