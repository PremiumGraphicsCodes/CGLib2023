#pragma once

#include "Crystal/AppBase/IRenderer.h"

namespace Crystal {
	namespace UI {

		class World : public Crystal::UI::WorldBase
		{
		public:
		};

		class Renderer : public IRenderer
		{
		public:
			explicit Renderer(World* world) :
				world(world)
			{}

			void init() override
			{

			}

			void render(const int width, const int height) override
			{
			}

		private:
			World* world;
		};
	}
}