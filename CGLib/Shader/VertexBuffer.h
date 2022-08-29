#pragma once

#include "../Math/Vector3d.h"
#include <vector>

namespace Crystal {
	namespace Shader {

template<typename T>
class VertexBuffer
{
public:
	void add(const Math::Vector3df& v) {
		data.push_back(v.x);
		data.push_back(v.y);
		data.push_back(v.z);
	}

	std::vector<T> getData() const { return data; }

private:
	std::vector<T> data;
};
	}
}