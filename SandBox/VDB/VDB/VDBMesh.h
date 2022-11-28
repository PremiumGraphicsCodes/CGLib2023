#pragma once

#include "CGLib/Math/Vector3d.h"
#include "CGLib/Math/Box3d.h"
#include "CGLib/Util/UnCopyable.h"

#include <memory>
#include <array>
#include <vector>

namespace Crystal {
	namespace VDB {
		class VDBMeshImpl;

class VDBMesh : private UnCopyable
{
public:
	struct TriangleFace
	{
		std::array<unsigned int, 3> indices;
		Math::Vector3df normal;
	};

	struct QuadFace
	{
		std::array<unsigned int, 4> indices;
		Math::Vector3df normal;
	};

	struct Face
	{
		std::vector<unsigned int> indices;
		Math::Vector3df normal;
	};

	VDBMesh();

	~VDBMesh();

	void addVertex(const Math::Vector3df& position);

	Math::Vector3df getVertex(const int index);

	std::vector<Math::Vector3df> getVerticesf() const;

	std::vector<Math::Vector3dd> getVerticesd() const;

	void addTriangle(const std::array<unsigned int, 3>& indices);

	std::vector<TriangleFace> getTriangleFaces() const;

	void addQuad(const std::array<unsigned int, 4>& indices);

	std::vector<QuadFace> getQuadFaces() const;

	std::vector<Face> getAllFaces() const;

	Math::Box3df getBoundingBox() const;

	void updateNormals();

	VDBMeshImpl* getImpl() const { return impl.get(); }

	void scale(const double scale);

private:
	std::unique_ptr<VDBMeshImpl> impl;
};

	}
}