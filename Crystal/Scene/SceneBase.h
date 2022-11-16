#pragma once

#include <list>
#include <string>

#include "IPresenter.h"

#include "CGLib/Math/Box3d.h"
#include "CGLib/Util/UnCopyable.h"

namespace Crystal {
	namespace Scene {

class SceneBase : private UnCopyable
{
public:
	SceneBase();

	explicit SceneBase(const int id);

	SceneBase(const int id, const std::string& name);

	virtual ~SceneBase();

	void clear();

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	void setId(const int id) { this->id = id; }

	int getId() const { return id; }

	//void setVisible(const bool b) { this->_isVisible = b; }

	//virtual SceneType getType() const = 0;

	void addScene(SceneBase* scene);

	SceneBase* findSceneById(int id);

	SceneBase* findSceneByName(const std::string& name);

	void deleteSceneById(int id);

	template<class T>
	T findSceneById(int id) { return static_cast<T>(findSceneById(id)); }

	template<class T>
	T findSceneByName(const std::string& name) { return static_cast<T>(findSceneByName(name)); }

	//std::list<IScene*> findScenes(SceneType type);

	virtual Math::Box3df getBoundingBox() const { return Math::Box3df::createDegeneratedBox(); }

	bool isRoot() const { return parent == nullptr; }

	SceneBase* getParent() const { return parent; }

	SceneBase* getRoot();

	std::list<SceneBase*> getChildren() const { return children; }

	bool isLeaf() const { return children.empty(); }

	void addPresenter(IPresenter* presenter) { this->presenters.push_back(presenter); }

	std::list<IPresenter*> getPresenters() { return presenters; }

	//virtual void step() {};

protected:
	std::string name;
	int id;
	std::list<SceneBase*> children;
	std::list<IPresenter*> presenters;
	SceneBase* parent;
};

	}
}