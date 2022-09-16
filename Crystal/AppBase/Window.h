#pragma once

#include <vector>
#include <memory>
#include "IMenu.h"

struct GLFWwindow;

namespace Crystal {
	namespace UI {
		class Canvas;
		class IRenderer;

		class Window
		{
		public:
			Window(const std::string& title, Canvas* canvas, IRenderer* renderer);

			bool init();

			void show();

			void add(IMenu* menu) { this->menus.push_back(menu); }

			void add(IWindow* panel) { this->panels.push_back(panel); }

		private:
			std::vector< IMenu* > menus;
			std::vector< IWindow* > panels;
			GLFWwindow* window;
			std::string title;
			IRenderer* renderer;
			//Canvas* canvas;
		};

	}
}