#pragma once

#include "CGLib/UI/IOkCancelView.h"
#include "CGLib/UI/Box3dView.h"
#include "CGLib/UI/IntView.h"

namespace Crystal {
	namespace UI {
		class Renderer;

class PSBoxView : public IOkCancelView
{
public:
	explicit PSBoxView(const std::string& name, Renderer* renderer);

	void onOk() override;

private:
	Box3dView boxView;
	IntView countView;
	Renderer* renderer;
};

	}
}