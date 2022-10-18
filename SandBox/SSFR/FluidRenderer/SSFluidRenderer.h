#pragma once

#include "Crystal/Renderer/IRenderer.h"

namespace Crystal {
	namespace Renderer {

		class SSFluidRenderer : public IRenderer
		{
		public:
			struct Buffer
			{
				Shader::VertexBufferObject* position;
				Shader::VertexBufferObject* size;
				Shader::VertexBufferObject* uvec;
				Shader::VertexBufferObject* vvec;
				Shader::VertexBufferObject* wvec;
				Math::Matrix4dd projectionMatrix;
				Math::Matrix4dd modelViewMatrix;
				int count = 0;
			};

			void link() override;

			void render() override;

			Buffer buffer;
		private:
		};

	}
}