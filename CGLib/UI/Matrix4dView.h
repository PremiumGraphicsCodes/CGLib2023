#pragma once

#include "IView.h"

#include "../Math/Matrix4d.h"
#include "Float4View.h"

namespace Crystal {
	namespace UI {

class Matrix4dView : public IView
{
public:
	explicit Matrix4dView(const std::string& name);

	Matrix4dView(const std::string& name, const Math::Matrix4df& value);

	void setValue(const Math::Matrix4df& value);

	Math::Matrix4df getValue() const;

private:
	Float4View row1View;
	Float4View row2View;
	Float4View row3View;
	Float4View row4View;
};

	}
}