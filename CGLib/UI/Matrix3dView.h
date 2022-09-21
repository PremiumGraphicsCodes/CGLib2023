#pragma once

#include "IWindow.h"

#include "../Math/Matrix3d.h"

namespace Crystal {
	namespace UI {

class Matrix3dView : public IWindow
{
public:
	explicit Matrix3dView(const std::string& name);

	Matrix3dView(const std::string& name, const Math::Matrix3df& value);

	void onShow() override;

	void setValue(const Math::Matrix3df& value);

	Math::Matrix3df getValue() const;

private:
	Math::Matrix3df value;
};

	}
}