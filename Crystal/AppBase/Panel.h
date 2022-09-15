#pragma once

#include "CGLib/UI/IWindow.h"
#include <list>

namespace Crystal {
	namespace UI {

class Panel : public IWindow
{
public:
	explicit Panel(const std::string& name) :
		IWindow(name)
	{}

	void onShow() override;

private:
};

	}
}