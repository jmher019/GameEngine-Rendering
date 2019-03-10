#include <SceneObject.hpp>

using namespace puggo;

SceneObject::SceneObject(void):
    transformCompHandle(TransformComponentAllocator::create()) {}

SceneObject::SceneObject(const SceneObject& sceneObject) {
    // Copy transform component
    transformCompHandle = TransformComponentAllocator::create();
    TransformComponent& transformComp = TransformComponentAllocator::get(transformCompHandle);
    transformComp = TransformComponentAllocator::get(sceneObject.transformCompHandle);

    // Copy collision component
    if (BoundingBoxComponentAllocator::isValidHandle(sceneObject.boxCompHandle)) {
        setBoundingBoxComponent(BoundingBoxComponentAllocator::get(sceneObject.boxCompHandle));
    }
    else if (BoundingCapsuleComponentAllocator::isValidHandle(sceneObject.capsuleCompHandle)) {
        setBoundingCapsuleComponent(BoundingCapsuleComponentAllocator::get(sceneObject.capsuleCompHandle));
    }
    else if (BoundingSphereComponentAllocator::isValidHandle(sceneObject.sphereCompHandle)) {
        setBoundingSphereComponent(BoundingSphereComponentAllocator::get(sceneObject.sphereCompHandle));
    }

    // Mesh component
    meshCompHandle = sceneObject.meshCompHandle;

    // Light component
    if (PointLightComponentAllocator::isValidHandle(sceneObject.pointLightCompHandle)) {
        setPointLightComponent(PointLightComponentAllocator::get(sceneObject.pointLightCompHandle));
    }
    else if (DirectionalLightComponentAllocator::isValidHandle(sceneObject.directionalLightCompHandle)) {
        setDirectionalLightComponent(DirectionalLightComponentAllocator::get(sceneObject.directionalLightCompHandle));
    }
    else if (SpotLightComponentAllocator::isValidHandle(sceneObject.spotLightCompHandle)) {
        setSpotLightComponent(SpotLightComponentAllocator::get(sceneObject.spotLightCompHandle));
    }

    // Physics component
    if (PhysicsComponentAllocator::isValidHandle(sceneObject.physicsCompHandle)) {
        setPhysicsComponent(PhysicsComponentAllocator::get(sceneObject.physicsCompHandle));
    }
}

SceneObject::SceneObject(SceneObject&& sceneObject) noexcept {
    swap(this->transformCompHandle, sceneObject.transformCompHandle);
    swap(this->boxCompHandle, sceneObject.boxCompHandle);
    swap(this->capsuleCompHandle, sceneObject.capsuleCompHandle);
    swap(this->sphereCompHandle, sceneObject.sphereCompHandle);
    swap(this->meshCompHandle, sceneObject.meshCompHandle);
    swap(this->pointLightCompHandle, sceneObject.pointLightCompHandle);
    swap(this->directionalLightCompHandle, sceneObject.directionalLightCompHandle);
    swap(this->spotLightCompHandle, sceneObject.spotLightCompHandle);
    swap(this->physicsCompHandle, sceneObject.physicsCompHandle);
}

SceneObject::~SceneObject(void) {
    // Destroy transform component so that another scene object may be able to use it
    TransformComponentAllocator::destroy(transformCompHandle);

    // Destroy collision component so that another scene object may be able to use it
    if (BoundingBoxComponentAllocator::isValidHandle(boxCompHandle)) {
        BoundingBoxComponentAllocator::destroy(boxCompHandle);
    }
    else if (BoundingCapsuleComponentAllocator::isValidHandle(capsuleCompHandle)) {
        BoundingCapsuleComponentAllocator::destroy(capsuleCompHandle);
    }
    else if (BoundingSphereComponentAllocator::isValidHandle(sphereCompHandle)) {
        BoundingSphereComponentAllocator::destroy(sphereCompHandle);
    }

    // Mesh components are destroyed elsewhere so skip it

    // Destroy light component so that another scene object may be able to use it
    if (PointLightComponentAllocator::isValidHandle(pointLightCompHandle)) {
        PointLightComponentAllocator::destroy(pointLightCompHandle);
    }
    else if (DirectionalLightComponentAllocator::isValidHandle(directionalLightCompHandle)) {
        DirectionalLightComponentAllocator::destroy(directionalLightCompHandle);
    }
    else if (SpotLightComponentAllocator::isValidHandle(spotLightCompHandle)) {
        SpotLightComponentAllocator::destroy(spotLightCompHandle);
    }

    // Destroy the physics component so that another scene object may be able to use it
    if (PhysicsComponentAllocator::isValidHandle(physicsCompHandle)) {
        PhysicsComponentAllocator::destroy(physicsCompHandle);
    }
}

SceneObject& SceneObject::operator=(const SceneObject& sceneObject) {
    // Copy transform component
    TransformComponent& transformComp = TransformComponentAllocator::get(transformCompHandle);
    transformComp = TransformComponentAllocator::get(sceneObject.transformCompHandle);

    // Copy collision component
    if (BoundingBoxComponentAllocator::isValidHandle(sceneObject.boxCompHandle)) {
        setBoundingBoxComponent(BoundingBoxComponentAllocator::get(sceneObject.boxCompHandle));
    }
    else if (BoundingCapsuleComponentAllocator::isValidHandle(sceneObject.capsuleCompHandle)) {
        setBoundingCapsuleComponent(BoundingCapsuleComponentAllocator::get(sceneObject.capsuleCompHandle));
    }
    else if (BoundingSphereComponentAllocator::isValidHandle(sceneObject.sphereCompHandle)) {
        setBoundingSphereComponent(BoundingSphereComponentAllocator::get(sceneObject.sphereCompHandle));
    }

    // Mesh component
    meshCompHandle = sceneObject.meshCompHandle;

    // Light component
    if (PointLightComponentAllocator::isValidHandle(sceneObject.pointLightCompHandle)) {
        setPointLightComponent(PointLightComponentAllocator::get(sceneObject.pointLightCompHandle));
    }
    else if (DirectionalLightComponentAllocator::isValidHandle(sceneObject.directionalLightCompHandle)) {
        setDirectionalLightComponent(DirectionalLightComponentAllocator::get(sceneObject.directionalLightCompHandle));
    }
    else if (SpotLightComponentAllocator::isValidHandle(sceneObject.spotLightCompHandle)) {
        setSpotLightComponent(SpotLightComponentAllocator::get(sceneObject.spotLightCompHandle));
    }

    // Physics component
    if (PhysicsComponentAllocator::isValidHandle(sceneObject.physicsCompHandle)) {
        setPhysicsComponent(PhysicsComponentAllocator::get(sceneObject.physicsCompHandle));
    }

    return *this;
}

SceneObject& SceneObject::operator=(SceneObject&& sceneObject) noexcept {
    swap(this->transformCompHandle, sceneObject.transformCompHandle);
    swap(this->boxCompHandle, sceneObject.boxCompHandle);
    swap(this->capsuleCompHandle, sceneObject.capsuleCompHandle);
    swap(this->sphereCompHandle, sceneObject.sphereCompHandle);
    swap(this->meshCompHandle, sceneObject.meshCompHandle);
    swap(this->pointLightCompHandle, sceneObject.pointLightCompHandle);
    swap(this->directionalLightCompHandle, sceneObject.directionalLightCompHandle);
    swap(this->spotLightCompHandle, sceneObject.spotLightCompHandle);
    swap(this->physicsCompHandle, sceneObject.physicsCompHandle);

    return *this;
}

bool SceneObject::operator==(const SceneObject& sceneObject) const noexcept {
    return transformCompHandle == sceneObject.transformCompHandle
        && boxCompHandle == sceneObject.boxCompHandle
        && capsuleCompHandle == sceneObject.capsuleCompHandle
        && sphereCompHandle == sceneObject.sphereCompHandle
        && meshCompHandle == sceneObject.meshCompHandle
        && pointLightCompHandle == sceneObject.pointLightCompHandle
        && directionalLightCompHandle == sceneObject.directionalLightCompHandle
        && spotLightCompHandle == sceneObject.spotLightCompHandle
        && physicsCompHandle == sceneObject.physicsCompHandle;
}

const TransformComponentHandle& SceneObject::getTransformCompHandle(void) const noexcept {
    return transformCompHandle;
}

const BoundingBoxComponentHandle& SceneObject::getBoxCompHandle(void) const noexcept {
    return boxCompHandle;
}

const BoundingCapsuleComponentHandle& SceneObject::getCapsuleCompHandle(void) const noexcept {
    return capsuleCompHandle;
}

const BoundingSphereComponentHandle& SceneObject::getSphereCompHandle(void) const noexcept {
    return sphereCompHandle;
}

const MeshComponentHandle& SceneObject::getMeshCompHandle(void) const noexcept {
    return meshCompHandle;
}

const PointLightComponentHandle& SceneObject::getPointLightCompHandle(void) const noexcept {
    return pointLightCompHandle;
}

const DirectionalLightComponentHandle& SceneObject::getDirectionalLightCompHandle(void) const noexcept {
    return directionalLightCompHandle;
}

const SpotLightComponentHandle& SceneObject::getSpotLightCompHandle(void) const noexcept {
    return spotLightCompHandle;
}

const PhysicsComponentHandle& SceneObject::getPhysicsCompHandle(void) const noexcept {
    return physicsCompHandle;
}

void SceneObject::setTransformCompHandle(const TransformComponentHandle& transformCompHandle) noexcept {
    if (TransformComponentAllocator::isValidHandle(this->transformCompHandle)) {
        TransformComponentAllocator::destroy(this->transformCompHandle);
    }

    this->transformCompHandle = transformCompHandle;
}

void SceneObject::setBoxCompHandle(const BoundingBoxComponentHandle& boxCompHandle) noexcept {
    if (BoundingBoxComponentAllocator::isValidHandle(this->boxCompHandle)) {
        BoundingBoxComponentAllocator::destroy(this->boxCompHandle);
    }
    else if (BoundingCapsuleComponentAllocator::isValidHandle(this->capsuleCompHandle)) {
        BoundingCapsuleComponentAllocator::destroy(this->capsuleCompHandle);
    }
    else if (BoundingSphereComponentAllocator::isValidHandle(this->sphereCompHandle)) {
        BoundingSphereComponentAllocator::destroy(this->sphereCompHandle);
    }

    this->boxCompHandle = boxCompHandle;
}

void SceneObject::setCapsuleCompHandle(const BoundingCapsuleComponentHandle& capsuleCompHandle) noexcept {
    if (BoundingBoxComponentAllocator::isValidHandle(this->boxCompHandle)) {
        BoundingBoxComponentAllocator::destroy(this->boxCompHandle);
    }
    else if (BoundingCapsuleComponentAllocator::isValidHandle(this->capsuleCompHandle)) {
        BoundingCapsuleComponentAllocator::destroy(this->capsuleCompHandle);
    }
    else if (BoundingSphereComponentAllocator::isValidHandle(this->sphereCompHandle)) {
        BoundingSphereComponentAllocator::destroy(this->sphereCompHandle);
    }

    this->capsuleCompHandle = capsuleCompHandle;
}

void SceneObject::setSphereCompHandle(const BoundingSphereComponentHandle& sphereCompHandle) noexcept {
    if (BoundingBoxComponentAllocator::isValidHandle(this->boxCompHandle)) {
        BoundingBoxComponentAllocator::destroy(this->boxCompHandle);
    }
    else if (BoundingCapsuleComponentAllocator::isValidHandle(this->capsuleCompHandle)) {
        BoundingCapsuleComponentAllocator::destroy(this->capsuleCompHandle);
    }
    else if (BoundingSphereComponentAllocator::isValidHandle(this->sphereCompHandle)) {
        BoundingSphereComponentAllocator::destroy(this->sphereCompHandle);
    }

    this->sphereCompHandle = sphereCompHandle;
}

void SceneObject::setMeshCompHandle(const MeshComponentHandle& meshCompHandle) noexcept {
    // Mesh components are destroyed elsewhere
    this->meshCompHandle = meshCompHandle;
}

void SceneObject::setPointLightCompHandle(const PointLightComponentHandle& pointLightCompHandle) noexcept {
    if (PointLightComponentAllocator::isValidHandle(this->pointLightCompHandle)) {
        PointLightComponentAllocator::destroy(this->pointLightCompHandle);
    }
    else if (DirectionalLightComponentAllocator::isValidHandle(this->directionalLightCompHandle)) {
        DirectionalLightComponentAllocator::destroy(this->directionalLightCompHandle);
    }
    else if (SpotLightComponentAllocator::isValidHandle(this->spotLightCompHandle)) {
        SpotLightComponentAllocator::destroy(this->spotLightCompHandle);
    }
    
    this->pointLightCompHandle = pointLightCompHandle;
}

void SceneObject::setDirectionalLightCompHandle(const DirectionalLightComponentHandle& directionalLightCompHandle) noexcept {
    if (PointLightComponentAllocator::isValidHandle(this->pointLightCompHandle)) {
        PointLightComponentAllocator::destroy(this->pointLightCompHandle);
    }
    else if (DirectionalLightComponentAllocator::isValidHandle(this->directionalLightCompHandle)) {
        DirectionalLightComponentAllocator::destroy(this->directionalLightCompHandle);
    }
    else if (SpotLightComponentAllocator::isValidHandle(this->spotLightCompHandle)) {
        SpotLightComponentAllocator::destroy(this->spotLightCompHandle);
    }

    this->directionalLightCompHandle = directionalLightCompHandle;
}

void SceneObject::setSpotLightCompHandle(const SpotLightComponentHandle& spotLightCompHandle) noexcept {
    if (PointLightComponentAllocator::isValidHandle(this->pointLightCompHandle)) {
        PointLightComponentAllocator::destroy(this->pointLightCompHandle);
    }
    else if (DirectionalLightComponentAllocator::isValidHandle(this->directionalLightCompHandle)) {
        DirectionalLightComponentAllocator::destroy(this->directionalLightCompHandle);
    }
    else if (SpotLightComponentAllocator::isValidHandle(this->spotLightCompHandle)) {
        SpotLightComponentAllocator::destroy(this->spotLightCompHandle);
    }

    this->spotLightCompHandle = spotLightCompHandle;
}

void SceneObject::setPhyicsCompHandle(const PhysicsComponentHandle& physicsCompHandle) noexcept {
    if (PhysicsComponentAllocator::isValidHandle(this->physicsCompHandle)) {
        PhysicsComponentAllocator::destroy(this->physicsCompHandle);
    }

    this->physicsCompHandle = physicsCompHandle;
}

TransformComponent* SceneObject::getTransformComponent(void) const noexcept {
    if (TransformComponentAllocator::isValidHandle(getTransformCompHandle())) {
        return &TransformComponentAllocator::get(getTransformCompHandle());
    }

    return nullptr;
}

BoundingBoxComponent* SceneObject::getBoundingBoxComponent(void) const noexcept {
    if (BoundingBoxComponentAllocator::isValidHandle(getBoxCompHandle())) {
        return &BoundingBoxComponentAllocator::get(getBoxCompHandle());
    }

    return nullptr;
}

BoundingCapsuleComponent* SceneObject::getBoundingCapsuleComponent(void) const noexcept {
    if (BoundingCapsuleComponentAllocator::isValidHandle(getCapsuleCompHandle())) {
        return &BoundingCapsuleComponentAllocator::get(getCapsuleCompHandle());
    }

    return nullptr;
}

BoundingSphereComponent* SceneObject::getBoundingSphereComponent(void) const noexcept {
    if (BoundingSphereComponentAllocator::isValidHandle(getSphereCompHandle())) {
        return &BoundingSphereComponentAllocator::get(getSphereCompHandle());
    }

    return nullptr;
}

MeshComponent* SceneObject::getMeshComponent(void) const noexcept {
    if (MeshComponentAllocator::isValidHandle(getMeshCompHandle())) {
        return &MeshComponentAllocator::get(getMeshCompHandle());
    }

    return nullptr;
}

PointLightComponent* SceneObject::getPointLightComponent(void) const noexcept {
    if (PointLightComponentAllocator::isValidHandle(getPointLightCompHandle())) {
        return &PointLightComponentAllocator::get(getPointLightCompHandle());
    }

    return nullptr;
}

DirectionalLightComponent* SceneObject::getDirectionalLightComponent(void) const noexcept {
    if (DirectionalLightComponentAllocator::isValidHandle(getDirectionalLightCompHandle())) {
        return &DirectionalLightComponentAllocator::get(getDirectionalLightCompHandle());
    }

    return nullptr;
}

SpotLightComponent* SceneObject::getSpotLightComponent(void) const noexcept {
    if (SpotLightComponentAllocator::isValidHandle(getSpotLightCompHandle())) {
        return &SpotLightComponentAllocator::get(getSpotLightCompHandle());
    }

    return nullptr;
}

PhysicsComponent* SceneObject::getPhysicsComponent(void) const noexcept {
    if (PhysicsComponentAllocator::isValidHandle(getPhysicsCompHandle())) {
        return &PhysicsComponentAllocator::get(getPhysicsCompHandle());
    }

    return nullptr;
}

void SceneObject::setTransformComponent(const TransformComponent& transformComponent) noexcept {
    if (!TransformComponentAllocator::isValidHandle(getTransformCompHandle())) {
        transformCompHandle = TransformComponentAllocator::create();
    }
    
    TransformComponentAllocator::get(getTransformCompHandle()) = transformComponent;
}

void SceneObject::setBoundingBoxComponent(const BoundingBoxComponent& boundingBoxComponent) noexcept {
    if (!BoundingBoxComponentAllocator::isValidHandle(getBoxCompHandle())) {
        boxCompHandle = BoundingBoxComponentAllocator::create();
    }

    BoundingBoxComponentAllocator::get(getBoxCompHandle()) = boundingBoxComponent;
}

void SceneObject::setBoundingCapsuleComponent(const BoundingCapsuleComponent& boundingCapsuleComponent) noexcept {
    if (!BoundingCapsuleComponentAllocator::isValidHandle(getCapsuleCompHandle())) {
        capsuleCompHandle = BoundingCapsuleComponentAllocator::create();
    }

    BoundingCapsuleComponentAllocator::get(getCapsuleCompHandle()) = boundingCapsuleComponent;
}

void SceneObject::setBoundingSphereComponent(const BoundingSphereComponent& boundingSphereComponent) noexcept {
    if (!BoundingSphereComponentAllocator::isValidHandle(getSphereCompHandle())) {
        sphereCompHandle = BoundingSphereComponentAllocator::create();
    }

    BoundingSphereComponentAllocator::get(getSphereCompHandle()) = boundingSphereComponent;
}

void SceneObject::setPointLightComponent(const PointLightComponent& pointLightComponent) noexcept {
    if (!PointLightComponentAllocator::isValidHandle(getPointLightCompHandle())) {
        pointLightCompHandle = PointLightComponentAllocator::create();
    }

    PointLightComponentAllocator::get(getPointLightCompHandle()) = pointLightComponent;
}

void SceneObject::setDirectionalLightComponent(const DirectionalLightComponent& directionalLightComponent) noexcept {
    if (!DirectionalLightComponentAllocator::isValidHandle(getDirectionalLightCompHandle())) {
        directionalLightCompHandle = DirectionalLightComponentAllocator::create();
    }

    DirectionalLightComponentAllocator::get(getDirectionalLightCompHandle()) = directionalLightComponent;
}

void SceneObject::setSpotLightComponent(const SpotLightComponent& spotLightComponent) noexcept {
    if (!SpotLightComponentAllocator::isValidHandle(getSpotLightCompHandle())) {
        spotLightCompHandle = SpotLightComponentAllocator::create();
    }

    SpotLightComponentAllocator::get(getSpotLightCompHandle()) = spotLightComponent;
}

void SceneObject::setPhysicsComponent(const PhysicsComponent& physicsComponent) noexcept {
    if (!PhysicsComponentAllocator::isValidHandle(getPhysicsCompHandle())) {
        physicsCompHandle = PhysicsComponentAllocator::create();
    }

    PhysicsComponentAllocator::get(getPhysicsCompHandle()) = physicsComponent;
}