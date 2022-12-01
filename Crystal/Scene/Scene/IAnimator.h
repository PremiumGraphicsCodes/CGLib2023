#pragma once

namespace Crystal {
	namespace Scene {

class IAnimator
{
public:
	~IAnimator() {};

	virtual void step() = 0;
};

	}
}