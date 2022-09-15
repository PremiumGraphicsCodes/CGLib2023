#pragma once

#include "IWindow.h"

namespace Crystal {
	namespace UI {

class Panel : public IWindow
{
public:
	explicit Panel(const std::string& name) :
		IWindow(name)
	{}

	//virtual ~Panel() = default;

	void onShow() override;

private:
};

	}
}