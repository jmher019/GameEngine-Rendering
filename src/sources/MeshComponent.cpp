#include <MeshComponent.hpp>

using namespace puggo;

MeshComponent::MeshComponent(
    const uint32_t& VAO,
    const uint32_t& VBO,
    const uint32_t& vertexCount,
    const uint32_t& shader
):
    VAO(VAO),
    VBO(VBO),
    vertexCount(vertexCount),
    shader(shader) {
}

MeshComponent::MeshComponent(const MeshComponent& meshComponent) noexcept:
    VAO(meshComponent.VAO),
    VBO(meshComponent.VBO),
    vertexCount(meshComponent.vertexCount),
    shader(meshComponent.shader) {
}

MeshComponent::MeshComponent(MeshComponent&& meshComponent) noexcept:
    VAO(move(meshComponent.VAO)),
    VBO(move(meshComponent.VBO)),
    vertexCount(move(meshComponent.vertexCount)),
    shader(move(meshComponent.shader)) {
}

MeshComponent& MeshComponent::operator=(const MeshComponent& meshComponent) noexcept {
    VAO = meshComponent.VAO;
    VBO = meshComponent.VBO;
    vertexCount = meshComponent.vertexCount;
    shader = meshComponent.shader;

    return *this;
}

MeshComponent& MeshComponent::operator=(MeshComponent&& meshComponent) noexcept {
    VAO = move(meshComponent.VAO);
    VBO = move(meshComponent.VBO);
    vertexCount = move(meshComponent.vertexCount);
    shader = move(meshComponent.shader);

    return *this;
}

bool MeshComponent::operator==(const MeshComponent& meshComponent) noexcept {
    return VAO == meshComponent.VAO &&
        VBO == meshComponent.VBO &&
        vertexCount == meshComponent.vertexCount &&
        shader == meshComponent.shader;
}

const uint32_t& MeshComponent::getVAO(void) const noexcept {
    return VAO;
}

const uint32_t& MeshComponent::getVBO(void) const noexcept {
    return VBO;
}

const uint32_t& MeshComponent::getVertexCount(void) const noexcept {
    return vertexCount;
}

const uint32_t& MeshComponent::getShader(void) const noexcept {
    return shader;
}