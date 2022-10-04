#pragma once

#include "IView.h"
#include "Vector3dView.h"
#include "FloatView.h"

#include "../Math/Circle3d.h"

namespace Crystal {
	namespace UI {

class Circle3dView : public IView
{
public:
	explicit Circle3dView(const std::string& name);

	Circle3dView(const std::string& name, const Math::Circle3df& value);

	Math::Circle3df getValue() const;

	void setValue(const Math::Circle3df& value);

private:
	Vector3dView center;
	Vector3dView normal;
	FloatView radius;
};

	}
}