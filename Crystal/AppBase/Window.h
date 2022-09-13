#pragma once

#include <vector>
#include <memory>
#include "IMenu.h"

struct GLFWwindow;

namespace Crystal {
	namespace UI {
		class Canvas;

		class Window
		{
		public:
			Window(const std::string& title, Canvas* canvas);

			bool init();

			void show();

			void add(IMenu* menu) { this->menus.push_back(menu); }

			void add(IWindow* panel) { this->panels.push_back(panel); }

		protected:
			virtual void onInit() {};

			virtual void onRender() {};

			GLFWwindow* getGLFWWindow() const { return window; }

		private:
			std::vector< IMenu* > menus;
			std::vector< IWindow* > panels;
			GLFWwindow* window;
			std::string title;
			Canvas* canvas;
		};

	}
}