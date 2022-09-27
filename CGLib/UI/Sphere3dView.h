#pragma once

#include "IView.h"
#include "Vector3dView.h"
#include "FloatView.h"

#include "../Math/Sphere3d.h"

namespace Crystal {
	namespace UI {

class Sphere3dView : public IView
{
public:
	explicit Sphere3dView(const std::string& name);

	Sphere3dView(const std::string& name, const Math::Sphere3df& value);

	Math::Sphere3df getValue() const;

	void setValue(const Math::Sphere3df& value);

private:
	Vector3dView center;
	FloatView radius;
};
	}
}