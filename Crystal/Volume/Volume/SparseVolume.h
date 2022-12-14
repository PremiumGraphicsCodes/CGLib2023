#pragma once

#include "CGLib/Math/Box3d.h"
//#include "IParticle.h"
#include "CGLib/Util/UnCopyable.h"

#include <map>
#include <vector>
#include <list>
#include <array>

namespace Crystal {
	namespace Volume {

/*
template<typename T>
class NodeAttributeBase
{
virtual ~NodeAttributeBase()
{}
T value;
};
*/

class INodeAttribute
{
public:
	virtual ~INodeAttribute() {};
};

template<typename T>
class SparseVolumeNode
{
public:
	SparseVolumeNode(const Math::Vector3df& position, const std::array<int, 3>& index) :
		position(position),
		value(0.0),
		index(index),
		attr(nullptr)
	{}

	Math::Vector3df getPosition() const { return position; }

	T getValue() const { return value; }

	void setValue(const T v) { this->value = v; }

	std::array<int, 3> getIndex() const { return index; }

	void setAttribute(INodeAttribute* attr) { this->attr = attr; }

	INodeAttribute* getAttribute() { return attr; }

private:
	Math::Vector3df position;
	T value;
	const std::array<int, 3> index;
	INodeAttribute* attr;
};

template<typename T>
class SparseVolume : private UnCopyable
{
public:
	SparseVolume()
	{
		table.resize(100);
	}

	SparseVolume(const Math::Vector3df& cellLength, const size_t tableSize) :
		cellLength(cellLength)
	{
		table.resize(tableSize);
	}

	~SparseVolume()
	{
		clear();
	}

	void clear();

	SparseVolumeNode<T>* createNode(const std::array<int, 3>& index);

	Math::Vector3df getPositionAt(const std::array<int, 3>& index) const;

	SparseVolumeNode<T>* findNode(const std::array<int, 3>& index) const;

	void addValue(const std::array<int, 3>& index, const T value);

	T getValueAt(const std::array<int, 3>& index) const;

	bool exists(const std::array<int, 3>& index) const;

	Math::Vector3dd getCellLength() const;

	std::list<SparseVolumeNode<T>*> getNodes() const;

	Math::Box3df getBoundingBox() const;

	std::array<int, 3> toIndex(const Math::Vector3df& pos) const;

private:

	int toHash(const Math::Vector3df& pos) const;

	int toHash(const std::array<int, 3>& index) const;

	Math::Vector3df cellLength;
	std::vector<std::list<SparseVolumeNode<T>*>> table;
};

using SparseVolumef = SparseVolume<float>;
using SparseVolumed = SparseVolume<double>;

	}
}