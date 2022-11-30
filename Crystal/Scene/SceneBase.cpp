#include "SceneBase.h"

using namespace Crystal::Scene;

SceneBase::SceneBase() :
	id(-1),
	parent(nullptr)
{}

SceneBase::SceneBase(const int id) :
	id(id),
	parent(nullptr)
{}

SceneBase::SceneBase(const int id, const std::string& name) :
	id(id),
	name(name),
	parent(nullptr)
{}

SceneBase::~SceneBase()
{
}

void SceneBase::clear()
{
	for (const auto& c : children) {
		c->clear();
	}
	children.clear();
}

void SceneBase::addScene(SceneBase* scene)
{
	scene->parent = this;
	this->children.push_back(scene);
}

SceneBase* SceneBase::findSceneById(int id)
{
	if (id == this->id) {
		return this;
	}
	for (auto c : children) {
		auto s = c->findSceneById(id);
		if (s != nullptr) {
			return s;
		}
	}
	return nullptr;
}

std::list<SceneBase*> SceneBase::findScenesByType(const std::type_info& type)
{
	std::list<SceneBase*> results;
	if (type == typeid(*this)) {
		results.push_back(this);
	}
	for (auto c : children) {
		auto s = c->findScenesByType(type);
		results.insert(results.end(), s.begin(), s.end());
	}
	return results;
}

void SceneBase::deleteSceneById(int id)
{
	for (auto c : children) {
		if (c->getId() == id) {
			children.remove(c);
			delete c;
			return;
		}
	}
}

SceneBase* SceneBase::findSceneByName(const std::string& name)
{
	if (name == this->name) {
		return this;
	}
	for (auto c : children) {
		if (c->findSceneByName(name) != nullptr) {
			return c;
		}
	}
	return nullptr;
}

SceneBase* SceneBase::getRoot()
{
	auto p = this;
	while (!p->isRoot()) {
		p = p->getParent();
	}
	return p;
}

/*
std::list<IScene*> IScene::findScenes(const SceneType type)
{
	std::list<IScene*> scenes;
	if (this->getType() == type) {
		scenes.push_back(this);
	}
	//scenes.push_back(this);
	for (auto c : children) {
		auto ss = c->findScenes(type);
		scenes.splice(scenes.end(), ss);
	}
	return scenes;
}
*/