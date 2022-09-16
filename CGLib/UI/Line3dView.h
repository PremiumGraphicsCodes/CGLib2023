#pragma once

#include "IView.h"

#include "Vector3dView.h"

#include "../Math/Line3d.h"

namespace Crystal {
	namespace UI {

class Line3dView : public IView
{
public:
	explicit Line3dView(const std::string& name);

	Line3dView(const std::string& name, const Math::Line3df& value);

	Math::Line3df getValue() const;

	void setValue(const Math::Line3df& value);

private:
	Vector3dView startView;
	Vector3dView endView;
};

	}
}