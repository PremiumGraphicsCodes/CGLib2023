#pragma once

#include "IWindow.h"

#include "Vector3dView.h"

#include "../Math/Box3d.h"

namespace Crystal {
	namespace UI {

class Box3dView : public IWindow
{
public:
	explicit Box3dView(const std::string& name);

	Box3dView(const std::string& name, const Math::Box3df& value);

	Math::Box3df getValue() const;

	void setValue(const Math::Box3df& value);

private:
	Vector3dView minView;
	Vector3dView maxView;
};

	}
}