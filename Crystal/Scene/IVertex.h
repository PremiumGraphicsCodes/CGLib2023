#pragma once

namespace Crystal {
	namespace Scene {

class IVertex
{
public:
	virtual ~IVertex() = default;

	virtual Math::Vector3df getPosition() const = 0;

};

	}
}
