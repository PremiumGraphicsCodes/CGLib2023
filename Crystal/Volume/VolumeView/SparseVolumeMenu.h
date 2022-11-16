#pragma once

#include "CGLib/UI/IMenu.h"

namespace Crystal {
	namespace UI {
		class Panel;
		class World;
		class Renderer;

		class SparseVolumeMenu : public IMenu
		{
		public:
			SparseVolumeMenu(const std::string& name, Panel* control, World* world, Renderer* renderer);
		};

	}
}