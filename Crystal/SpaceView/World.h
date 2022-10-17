#pragma once

namespace Crystal {
	namespace UI {

		class World : public Crystal::UI::WorldBase
		{
		public:
		};

		class Renderer : public Crystal::UI::RendererBase
		{
		public:
			explicit Renderer(World* world) :
				RendererBase(world)
			{}

			void onInit() override
			{

			}

		private:

		};
	}
}