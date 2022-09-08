#include "../UI/Window.h"

#include <iostream>

using namespace Crystal::UI;

int main() {
	Window window("Hello");
	window.init();

	window.show();
}