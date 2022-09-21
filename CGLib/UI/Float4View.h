#pragma once

#include "IWindow.h"

#include "../Math/Vector4d.h"
#include <array>

namespace Crystal {
	namespace UI {

class Float4View : public IWindow
{
public:
	explicit Float4View(const std::string& name);

	Float4View(const std::string& name, const Math::Vector4df& value);

	void onShow() override;

	Math::Vector4df getValue() const { return value; }

	void setValue(const Math::Vector4df& value) { this->value = value; }

private:
	Math::Vector4dd value;
};

	}
}