#pragma once

#include "Crystal/Renderer/Renderer/IRenderer.h"

namespace Crystal {
	namespace Renderer {

		class BRDFLUTRenderer : public IRenderer
		{
		public:
			void link() override;

			void render() override;

		private:
		};

	}
}