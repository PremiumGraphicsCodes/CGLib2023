#pragma once

#include <string>
#include <list>
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace UI {

class IWindow : private UnCopyable
{
protected:
	explicit IWindow(const std::string& name) :
		name(name)
	{}

	virtual ~IWindow() {};

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