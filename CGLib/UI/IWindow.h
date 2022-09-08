#pragma once

#include <string>
#include <list>

namespace Crystal {
	namespace UI {

class IWindow
{
protected:
	explicit IWindow(const std::string& name) :
		name(name)
	{}

	virtual ~IWindow() {
		for (auto c : children) {
			delete c;
		}
	};

public:
	void add(IWindow* child) { children.push_back(child); }

	void clear() { children.clear(); }

	void show() { onShow(); }

	virtual void onShow() = 0;

protected:
	std::string name;
	std::list<IWindow*> children;
};

	}
}