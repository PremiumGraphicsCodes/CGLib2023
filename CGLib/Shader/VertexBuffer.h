#pragma once

#include "../Math/Vector2d.h"
#include "../Math/Vector3d.h"
#include "../Graphics/ColorRGBA.h"
#include <vector>

namespace Crystal {
	namespace Shader {

template<typename T>
class VertexBuffer
{
public:
	void add(const T v) {
		data.push_back(v);
	}

	void add(const Math::Vector2df& v) {
		data.push_back(v.x);
		data.push_back(v.y);
	}

	void add(const Math::Vector3df& v) {
		data.push_back(v.x);
		data.push_back(v.y);
		data.push_back(v.z);
	}

	void add(const Graphics::ColorRGBAf& c) {
		data.push_back(c.r);
		data.push_back(c.g);
		data.push_back(c.b);
		data.push_back(c.a);
	}

	std::vector<T> getData() const { return data; }

private:
	std::vector<T> data;
};
	}
}