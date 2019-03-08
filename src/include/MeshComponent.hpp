#ifndef PUGGO_MESH_COMPONENT_HPP
#define PUGGO_MESH_COMPONENT_HPP

#include <GenericComponentAllocator.hpp>

namespace puggo {
    class MeshComponent {
    public:
        MeshComponent(
            const uint32_t& VAO,
            const uint32_t& VBO,
            const uint32_t& vertexCount,
            const uint32_t& shader
        );
        MeshComponent(const MeshComponent& meshComponent) noexcept;
        MeshComponent(MeshComponent&& meshComponent) noexcept;

        MeshComponent& operator=(const MeshComponent& meshComponent) noexcept;
        MeshComponent& operator=(MeshComponent&& meshComponent) noexcept;
        bool operator==(const MeshComponent& meshComponent) noexcept;

        const uint32_t& getVAO(void) const noexcept;
        const uint32_t& getVBO(void) const noexcept;
        const uint32_t& getVertexCount(void) const noexcept;
        const uint32_t& getShader(void) const noexcept;

    private:
        uint32_t VAO = 0;
        uint32_t VBO = 0;
        uint32_t vertexCount = 0;
        uint32_t shader = 0;
    };
}

#endif // !PUGGO_MESH_COMPONENT_HPP
