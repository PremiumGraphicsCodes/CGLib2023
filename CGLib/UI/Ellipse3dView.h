#pragma once

#include "IView.h"
#include "Vector3dView.h"
#include "FloatView.h"

#include "../Math/Ellipse3d.h"

namespace Crystal {
	namespace UI {

class Ellipse3dView : public IView
{
public:
	explicit Ellipse3dView(const std::string& name);

	Ellipse3dView(const std::string& name, const Math::Ellipse3df& value);

	Math::Ellipse3df getValue() const;

	void setValue(const Math::Ellipse3df& value);

private:
	Vector3dView centerView;
	Vector3dView uvecView;
	Vector3dView vvecView;
};

	}
}