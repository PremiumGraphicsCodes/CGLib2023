#include "Sphere3dView.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

Sphere3dView::Sphere3dView(const std::string& name) :
	IView(name),
	center("Center", Math::Vector3dd(0, 0, 0)),
	radius("Radius", 1.0)
{
	add(&center);
	add(&radius);
}

Sphere3df Sphere3dView::getValue() const
{
	return Math::Sphere3df(center.getValue(), radius.getValue());
}

void Sphere3dView::setValue(const Sphere3df& value)
{
	this->center.setValue(value.getCenter());
	this->radius.setValue(value.getRadius());
}