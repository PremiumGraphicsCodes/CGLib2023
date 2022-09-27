
#pragma once

#include "IView.h"
#include "Vector3dView.h"
#include "../Math/Ray3d.h"

namespace Crystal {
	namespace UI {

class Ray3dView : public IView
{
public:
	explicit Ray3dView(const std::string& name);

	Ray3dView(const std::string& name, const Math::Ray3df& value);

	Math::Ray3df getValue() const;

	void setValue(const Math::Ray3df& value);

private:
	Vector3dView originView;
	Vector3dView directionView;
};

	}
}