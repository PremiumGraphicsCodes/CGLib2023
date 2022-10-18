#pragma once

namespace Crystal {
	namespace UI {

class IRenderer
{
public:
	~IRenderer() = default;

	virtual void init() = 0;

	virtual void render(const int width, const int height) = 0;
};

	}
}