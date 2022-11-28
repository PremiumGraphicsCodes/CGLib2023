#pragma once

#include "VDBVolume.h"

namespace Crystal {
	namespace VDB {

class VDBResampler
{
public:
	void setSource(VDBVolume* src) { this->src = src; }

	void box();

	void point();

	void quadratic();

private:
	VDBVolume* src = nullptr;
};

	}
}