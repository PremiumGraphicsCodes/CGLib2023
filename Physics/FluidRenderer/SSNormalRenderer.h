#pragma once

#include "Crystal/Renderer/IRenderer.h"

namespace Crystal {
	namespace Renderer {

		class SSNormalRenderer : public IRenderer
		{
		public:
			void link() override;

			void render() override;

		private:
		};

	}
}