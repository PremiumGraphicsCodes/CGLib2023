#pragma once

#include "IWindow.h"
#include "Button.h"

namespace Crystal {
	namespace UI {

class IOkCancelView : public IWindow
{
public:
	IOkCancelView(const std::string& name) :
		IWindow(name),
		ok("Ok"),
		cancel("Cancel")
	{
		ok.setFunction([=]() { onOk(); });
		cancel.setFunction([=]() { onCancel(); });
	}

	virtual ~IOkCancelView() {}

protected:
	virtual void onShow() {
		for (auto c : children) {
			c->show();
		}
		ok.show();
		cancel.show();
	}

	virtual void onOk() = 0;

	virtual void onCancel() {};

private:
	Button ok;
	Button cancel;
};

	}
}