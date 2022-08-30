#pragma once

#include "Vector3d.h"
//#include "IVolume3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Box3d// : public IVolume3d<T>
{
public:
	Box3d();

	explicit Box3d(const Vector3d<T>& point);

	Box3d(const Vector3d<T>& pointX, const Vector3d<T>& pointY);

	static Box3d<T> createDegeneratedBox();

	void add(const Vector3d<T>& v);

	void add(const Box3d<T>& b);

	Vector3d<T> getMax() const { return max; }

	Vector3d<T> getMin() const { return min; }

private:
	Vector3d<T> min;
	Vector3d<T> max;
};

using Box3df = Box3d<float>;
using Box3dd = Box3d<double>;

	}
}