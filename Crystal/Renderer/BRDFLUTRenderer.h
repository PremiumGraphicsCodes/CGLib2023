#pragma once

#include "IRenderer.h"

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