#pragma once
#include "World.h"
#include "Crystal/AppBase/RendererBase.h"

namespace Crystal{
	namespace UI {
		class Renderer : public RendererBase
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
