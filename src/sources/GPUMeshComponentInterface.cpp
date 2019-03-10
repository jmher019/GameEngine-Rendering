#include <GPUMeshComponentInterface.hpp>

using namespace puggo;

vector<MeshComponentHandle> GPUMeshComponentInterface::loadedMeshComps;

MeshComponentHandle GPUMeshComponentInterface::createMeshComponent(
    const uint32_t& shader,
    const uint32_t& vertexCount,
    const vector<VertexAttribDescription>& descriptionArr,
    void* data
) {
    assert(data != nullptr);

    GLuint totalVertexSize = accumulate(descriptionArr.begin(), descriptionArr.end(), static_cast<uint32_t>(0), [](uint32_t& sum, const VertexAttribDescription& desc) { return sum + desc.size; });
    GLuint totalArraySize = vertexCount * totalVertexSize;

    GLuint VAO;
    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, totalArraySize, data, GL_STATIC_DRAW);

    for (uint32_t i = 0; i < descriptionArr.size(); i++) {
        const VertexAttribDescription& desc = descriptionArr[i];
        glEnableVertexAttribArray(desc.index);
        glVertexAttribPointer(desc.index, desc.size, desc.type, desc.normalized, desc.stride, desc.offset);
    }

    glBindVertexArray(0);

    const MeshComponentHandle handle = MeshComponentAllocator::create();
    MeshComponentAllocator::get(handle) = {
        VAO,
        VBO,
        vertexCount,
        shader
    };
    loadedMeshComps.push_back(handle);

    return handle;
}

MeshComponentHandle GPUMeshComponentInterface::createDynamicMeshComponent(
    const uint32_t& shader,
    const uint32_t& vertexCount,
    const vector<VertexAttribDescription>& descriptionArr
) {
    GLuint totalVertexSize = accumulate(descriptionArr.begin(), descriptionArr.end(), static_cast<uint32_t>(0), [](uint32_t& sum, const VertexAttribDescription& desc) { return sum + desc.size; });
    GLuint totalArraySize = vertexCount * totalVertexSize;

    GLuint VAO;
    GLuint VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, totalArraySize, nullptr, GL_DYNAMIC_DRAW);

    for (uint32_t i = 0; i < descriptionArr.size(); i++) {
        const VertexAttribDescription& desc = descriptionArr[i];
        glEnableVertexAttribArray(desc.index);
        glVertexAttribPointer(desc.index, desc.size, desc.type, desc.normalized, desc.stride, desc.offset);
    }

    glBindVertexArray(0);

    const MeshComponentHandle handle = MeshComponentAllocator::create();
    MeshComponentAllocator::get(handle) = {
        VAO,
        VBO,
        vertexCount,
        shader
    };
    loadedMeshComps.push_back(handle);

    return handle;
}

void GPUMeshComponentInterface::updateDynamicMeshComponent(
    const MeshComponentHandle& handle,
    void* data,
    const uint32_t& sizeInBytes
) {
    if (!MeshComponentAllocator::isValidHandle(handle)) {
        return;
    }

    const MeshComponent& meshComponent = MeshComponentAllocator::get(handle);
    glBindVertexArray(meshComponent.getVAO());
    glBindBuffer(GL_ARRAY_BUFFER, meshComponent.getVBO());
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeInBytes, data);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GPUMeshComponentInterface::destroyMeshComponent(const MeshComponentHandle& handle) {
    if (!MeshComponentAllocator::isValidHandle(handle)) {
        return;
    }

    const MeshComponent& meshComponent = MeshComponentAllocator::get(handle);
    glDeleteVertexArrays(1, &meshComponent.getVAO());
    glDeleteBuffers(1, &meshComponent.getVBO());

    vector<MeshComponentHandle>::iterator it = find(loadedMeshComps.begin(), loadedMeshComps.end(), handle);

    if (it != loadedMeshComps.end()) {
        loadedMeshComps.erase(it);
    }

    MeshComponentAllocator::destroy(handle);
}

void GPUMeshComponentInterface::clearAllMeshComponents(void) {
    for (vector<MeshComponentHandle>::iterator it = loadedMeshComps.begin(); it != loadedMeshComps.end(); ++it) {
        destroyMeshComponent(*it);
    }

    loadedMeshComps.clear();
}

void GPUMeshComponentInterface::draw(
    const MeshComponentHandle& handle,
    const GLenum& mode
) {
    const MeshComponent& meshComponent = MeshComponentAllocator::get(handle);
    glBindVertexArray(meshComponent.getVAO());
    glDrawArrays(mode, 0, meshComponent.getVertexCount());
    glBindVertexArray(0);
}

void GPUMeshComponentInterface::draw(
    const MeshComponentHandle& handle,
    const GLenum& mode,
    const uint32_t& vertexCount
) {
    const MeshComponent& meshComponent = MeshComponentAllocator::get(handle);
    glBindVertexArray(meshComponent.getVAO());
    glDrawArrays(mode, 0, vertexCount);
    glBindVertexArray(0);
}