#pragma once

#include "IView.h"
#include "Vector3dView.h"

#include "../Math/Ellipsoid3d.h"

namespace Crystal {
	namespace UI {

class Ellipsoid3dView : public IView
{
public:
	explicit Ellipsoid3dView(const std::string& name);

	Ellipsoid3dView(const std::string& name, const Math::Ellipsoid3df& value);

	Math::Ellipsoid3df getValue() const;

	void setValue(const Math::Ellipsoid3df& value);

private:
	Vector3dView centerView;
	Vector3dView uvecView;
	Vector3dView vvecView;
	Vector3dView wvecView;
};

	}
}