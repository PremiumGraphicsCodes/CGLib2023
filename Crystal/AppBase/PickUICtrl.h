#pragma once

#include <memory>
#include "IUICtrl.h"

//#include "CGLib/Shader/FrameBufferObject.h"
#include "CGLib/Shader/TextureObject.h"

namespace Crystal {
	namespace UI {

class PickUICtrl : public IUICtrl
{
public:
	explicit PickUICtrl(Shader::TextureObject* texture);

	~PickUICtrl() {}

	void onLeftButtonDown(const Math::Vector2df& position) override;

private:
	//Shader::FrameBufferObject* fbo;
	Shader::TextureObject* texture;
};

	}
}