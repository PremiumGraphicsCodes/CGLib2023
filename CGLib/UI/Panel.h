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

	void setChild(IWindow* window) {
		this->children.clear();
		this->children.push_back(window);
	}

	void onShow() override;

private:
};

	}
}