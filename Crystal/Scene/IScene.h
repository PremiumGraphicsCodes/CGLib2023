#pragma once

#include <list>
#include <string>

#include "CGLib/Math/Box3d.h"
#include "CGLib/Graphics/Camera.h"

#include "IPresenter.h"
#include "CGLib/Util/UnCopyable.h"

namespace Crystal {
	namespace Scene {

class IScene : private UnCopyable
{
public:
	IScene();

	explicit IScene(const int id);

	IScene(const int id, const std::string& name);

	virtual ~IScene();

	void clear();

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	void setId(const int id) { this->id = id; }

	int getId() const { return id; }

	//void setVisible(const bool b) { this->_isVisible = b; }

	//virtual SceneType getType() const = 0;

	void addScene(IScene* scene);

	IScene* findSceneById(int id);

	IScene* findSceneByName(const std::string& name);

	void deleteSceneById(int id);

	template<class T>
	T findSceneById(int id) { return static_cast<T>(findSceneById(id)); }

	template<class T>
	T findSceneByName(const std::string& name) { return static_cast<T>(findSceneByName(name)); }

	//std::list<IScene*> findScenes(SceneType type);

	virtual Math::Box3df getBoundingBox() const { return Math::Box3df::createDegeneratedBox(); }

	bool isRoot() const { return parent == nullptr; }

	IScene* getParent() const { return parent; }

	IScene* getRoot();

	std::list<IScene*> getChildren() const { return children; }

	bool isLeaf() const { return children.empty(); }

	virtual IPresenter* getPresenter() { return nullptr; }

protected:
	std::string name;
	int id;
	std::list<IScene*> children;
	IScene* parent;
};

	}
}