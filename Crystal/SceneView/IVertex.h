#pragma once

#include "CGLib/Math/Vector3d.h"

namespace Crystal {
	namespace Shape {

		class IVertex
		{
		public:
			virtual ~IVertex() = default;

			virtual Math::Vector3df getPosition() const = 0;

		};

		struct Vertex : public IVertex
		{
		public:
			explicit Vertex(const Math::Vector3df& p) : pos(p) {
			}

			Math::Vector3df getPosition() const override {
				return pos;
			}

		private:
			Math::Vector3df pos;
		};


	}
}
