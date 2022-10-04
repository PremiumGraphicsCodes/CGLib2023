#pragma once

#include "IView.h"
#include "Vector3dView.h"

#include "../Math/Cylinder3d.h"

namespace Crystal {
	namespace UI {

class Cylinder3dView : public IView
{
public:
	explicit Cylinder3dView(const std::string& name);

	Cylinder3dView(const std::string& name, const Math::Cylinder3df& value);

	Math::Cylinder3df getValue() const;

	void setValue(const Math::Cylinder3df& value);

private:
	Vector3dView bottomView;
	Vector3dView uvecView;
	Vector3dView vvecView;
	Vector3dView wvecView;
};

	}
}