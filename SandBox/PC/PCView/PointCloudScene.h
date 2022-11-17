#pragma once

#include "Crystal/Scene/SceneBase.h"
#include "PointCloudPresenter.h"
#include "Point.h"
#include <vector>
#include <memory>

namespace Crystal {
	namespace PC {

class PointCloud : private UnCopyable
{
public:
	void add(std::unique_ptr<Point>&& point) { this->points.push_back(std::move(point)); }

	const std::vector<std::unique_ptr<Point>>& getPoints() { return points; }

	Math::Box3df getBoundingBox() const;

private:
	std::vector<std::unique_ptr<Point>> points;
};


class PointCloudScene : public Scene::SceneBase
{
public:
	PointCloudScene();

	void setShape(std::unique_ptr<PointCloud>&& shape) { this->shape = std::move(shape); }

	PointCloud* getShape() { return shape.get(); }

	Math::Box3df getBoundingBox() const override;

private:
	std::unique_ptr<PointCloud> shape;
};

	}
}