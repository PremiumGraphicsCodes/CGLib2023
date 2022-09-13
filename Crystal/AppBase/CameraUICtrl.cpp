#include "CameraUICtrl.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

CameraUICtrl::CameraUICtrl(Camera* camera) :
	prevPosition(0.0f, 0.0f),
	camera(camera)
{
}

void CameraUICtrl::onLeftButtonDown(const Vector2df& position)
{
	prevPosition = position;
	//	camera->move();
}

void CameraUICtrl::onLeftButtonUp(const Vector2df& position)
{

}

void CameraUICtrl::onLeftDragging(const Vector2df& position)
{
	const auto diff = (position - prevPosition) * 1.0f;
	camera->setEye(camera->getEye() + Vector3df(diff, 0.0f));
	camera->setTarget(camera->getTarget() + Vector3df(diff, 0.0));

	this->prevPosition = position;
}

void CameraUICtrl::onRightButtonDown(const Vector2df& position)
{
	prevPosition = position;
}

void CameraUICtrl::onRightButtonUp(const Vector2df& position)
{

}

void CameraUICtrl::onRightDragging(const Vector2df& position)
{
	const auto diff = prevPosition - position;
	const auto scale = 1.0;//glm::distance(bb.getMin(), bb.getMax()) * 0.1;

	const auto& matrix = camera->getRotationMatrix();
	const auto v = glm::transpose(Matrix3dd(matrix)) * Vector3dd(diff, 0.0);

	{
		const Vector3df t = v;
		const auto& eye = camera->getEye();
		const auto& target = camera->getTarget();
		const auto& up = camera->getUp();
		camera->lookAt(eye + t, target, up);
	}
	//camera->rotate(diff.y, diff.x);
	this->prevPosition = position;
}

void CameraUICtrl::onWheel(const float dx)
{
	/*
	const auto bs = world->getBoundingBox();
	const auto length = (float)glm::distance(bs.getMin(), bs.getMax()) * 0.1f;
	const auto camera = world->getCamera()->getCamera();
	const auto f = camera->getForward();
	camera->setEye(camera->getEye() + f * dx * length);
	camera->setTarget(camera->getTarget() + f * dx * length);
	//world->getCamera()->getCamera()->zoom(dx / 100.0f);
	*/
}