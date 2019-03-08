#ifndef PUGGO_GPU_MESH_COMPONENT_INTERFACE_HPP
#define PUGGO_GPU_MESH_COMPONENT_INTERFACE_HPP

#include <deque>
#include <numeric>
#include <string>
#include <memory>
#include <algorithm>

#include <GPUShaderInterface.hpp>
#include <VertexAttribDescription.hpp>
#include <ComponentAllocators.hpp>

namespace puggo {
    class GPUMeshComponentInterface {
    public:
        GPUMeshComponentInterface(void) = delete;
        GPUMeshComponentInterface(const GPUMeshComponentInterface&) = delete;
        GPUMeshComponentInterface(GPUMeshComponentInterface&&) = delete;
        GPUMeshComponentInterface& operator=(const GPUMeshComponentInterface&) = delete;
        GPUMeshComponentInterface& operator=(GPUMeshComponentInterface&&) = delete;

        static MeshComponentHandle createMeshComponent(
            const uint32_t& shader,
            const uint32_t& vertexCount,
            const vector<VertexAttribDescription>& descriptionArr,
            void* data
        );
        static MeshComponentHandle createDynamicMeshComponent(
            const uint32_t& shader,
            const uint32_t& vertexCount,
            const vector<VertexAttribDescription>& descriptionArr
        );
        static void updateDynamicMeshComponent(
            const MeshComponentHandle& handle,
            void* data,
            const uint32_t& sizeInBytes
        );
        static void destroyMeshComponent(const MeshComponentHandle& handle);
        static void clearAllMeshComponents(void);
        static void draw(
            const MeshComponentHandle& handle,
            const GLenum& mode
        );
        static void draw(
            const MeshComponentHandle& handle,
            const GLenum& mode,
            const uint32_t& vertexCount
        );

    private:
        static vector<MeshComponentHandle> loadedMeshComps;
    };
}

#endif // !PUGGO_GPU_MESH_COMPONENT_INTERFACE_HPP
