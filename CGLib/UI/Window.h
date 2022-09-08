#pragma once

#include <vector>
#include <memory>
#include "IMenu.h"

struct GLFWwindow;

namespace Crystal {
	namespace UI {

class Window
{
public:
	Window(const std::string& title);

	bool init();

	void show();

	void add(IMenu* menu) { this->menus.push_back(menu); }

	void add(IWindow* panel) { this->panels.push_back(panel); }

	GLFWwindow* getGLFWWindow() const { return window; }

protected:
	virtual void onInit() {};

	virtual void onRender() {};

private:
	std::vector< IMenu* > menus;
	std::vector< IWindow* > panels;
	GLFWwindow* window;
	std::string title;
};

	}
}