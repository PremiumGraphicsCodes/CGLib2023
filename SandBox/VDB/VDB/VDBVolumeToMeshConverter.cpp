#include "VDBVolumeToMeshConverter.h"
#include "VDBVolumeImpl.h"
#include "VDBMesh.h"
#include "VDBMeshImpl.h"
#include "openvdb/tools/VolumeToMesh.h"

using namespace Crystal::VDB;

VDBMesh* VDBVolumeToMeshConverter::toMesh(const VDBVolume& volume, const double threshold, const double adaptivity)
{
    VDBMesh* mesh = new VDBMesh();
    auto impl = mesh->getImpl();
    auto grid = volume.getImpl()->getPtr();
    std::vector<openvdb::Vec3I> triangles;
    std::vector<openvdb::Vec4I> quads;
    openvdb::tools::volumeToMesh(*grid, impl->points, triangles, quads, threshold, adaptivity);
    for (const auto& t : triangles) {
        VDBMeshImpl::TriangleFace face;
        face.indices = t;
        impl->triangles.push_back(face);
    }
    for (const auto& q : quads) {
        VDBMeshImpl::QuadFace face;
        face.indices = q;
        impl->quads.push_back(face);
    }
    impl->updateNormals();
    return mesh;
}