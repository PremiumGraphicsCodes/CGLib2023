#pragma once

#include <vector>
#include <memory>
#include "CGLib/UI/IMenu.h"

struct GLFWwindow;

namespace Crystal {
	namespace UI {
		class WorldBase;
		class Canvas;
		class IRenderer;

class Window
{
public:
	Window(const std::string& title, WorldBase* world, Canvas* canvas, IRenderer* renderer);

	bool init();

	void show();

	void add(IMenu* menu) { this->menus.push_back(menu); }

	void add(IWindow* panel) { this->panels.push_back(panel); }

private:
	std::string title;
	std::vector< IMenu* > menus;
	std::vector< IWindow* > panels;
	GLFWwindow* window;
	WorldBase* world;
	IRenderer* renderer;
	//Canvas* canvas;
};

	}
}