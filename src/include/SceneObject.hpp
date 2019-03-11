#ifndef PUGGO_SCENE_OBJECT_HPP
#define PUGGO_SCENE_OBJECT_HPP

#include <ComponentAllocators.hpp>

namespace puggo {
    class SceneObject {
    public:
        SceneObject(void);
        SceneObject(const SceneObject& sceneObject);
        SceneObject(SceneObject&& sceneObject) noexcept;
        ~SceneObject(void);

        SceneObject& operator=(const SceneObject& sceneObject);
        SceneObject& operator=(SceneObject&& sceneObject) noexcept;
        bool operator==(const SceneObject& other) const noexcept;

        const TransformComponentHandle& getTransformCompHandle(void) const noexcept;
        const BoundingBoxComponentHandle& getBoxCompHandle(void) const noexcept;
        const BoundingCapsuleComponentHandle& getCapsuleCompHandle(void) const noexcept;
        const BoundingSphereComponentHandle& getSphereCompHandle(void) const noexcept;
        const MeshComponentHandle& getMeshCompHandle(void) const noexcept;
        const PointLightComponentHandle& getPointLightCompHandle(void) const noexcept;
        const DirectionalLightComponentHandle& getDirectionalLightCompHandle(void) const noexcept;
        const SpotLightComponentHandle& getSpotLightCompHandle(void) const noexcept;
        const PhysicsComponentHandle& getPhysicsCompHandle(void) const noexcept;

        void setMeshCompHandle(const MeshComponentHandle& meshCompHandle) noexcept;

        TransformComponent* getTransformComponent(void) const noexcept;
        BoundingBoxComponent* getBoundingBoxComponent(void) const noexcept;
        BoundingCapsuleComponent* getBoundingCapsuleComponent(void) const noexcept;
        BoundingSphereComponent* getBoundingSphereComponent(void) const noexcept;
        MeshComponent* getMeshComponent(void) const noexcept;
        PointLightComponent* getPointLightComponent(void) const noexcept;
        DirectionalLightComponent* getDirectionalLightComponent(void) const noexcept;
        SpotLightComponent* getSpotLightComponent(void) const noexcept;
        PhysicsComponent* getPhysicsComponent(void) const noexcept;

        void setTransformComponent(const TransformComponent& transformComponent) noexcept;
        void setBoundingBoxComponent(const BoundingBoxComponent& boundingBoxComponent) noexcept;
        void setBoundingCapsuleComponent(const BoundingCapsuleComponent& boundingCapsuleComponent) noexcept;
        void setBoundingSphereComponent(const BoundingSphereComponent& boundingSphereComponent) noexcept;
        void setPointLightComponent(const PointLightComponent& pointLightComponent) noexcept;
        void setDirectionalLightComponent(const DirectionalLightComponent& directionalLightComponent) noexcept;
        void setSpotLightComponent(const SpotLightComponent& spotLightComponent) noexcept;
        void setPhysicsComponent(const PhysicsComponent& physicsComponent) noexcept;

    protected:
        // Initialize handles with unlikely values
        // TODO: create a handle impossible state

        // Every SceneObject must have a unique transform component handle
        TransformComponentHandle transformCompHandle = { 262143, 16383 };

        // Collision Info. Can only have 1 of these 3 at any moment
        // If a Scene object has a collision component, it must be unique
        BoundingBoxComponentHandle boxCompHandle = { 262143, 16383 };
        BoundingCapsuleComponentHandle capsuleCompHandle = { 262143, 16383 };
        BoundingSphereComponentHandle sphereCompHandle = { 262143, 16383 };

        // Mesh info
        // If a Scene object has a mesh component, it can be shared with others
        MeshComponentHandle meshCompHandle = { 1023, 4194303 };

        // Light info. Can only have 1 of these 3 at any moment
        // If a Scene object has a light component, it must be unique
        PointLightComponentHandle pointLightCompHandle = { 1023, 4194303 };
        DirectionalLightComponentHandle directionalLightCompHandle = { 1023, 4194303 };
        SpotLightComponentHandle spotLightCompHandle = { 1023, 4194303 };

        // Physics info
        // If a Scene object has a physics component, it must be unique
        PhysicsComponentHandle physicsCompHandle = { 262143, 16383 };
    };
}

#endif // !PUGGO_SCENE_OBJECT_HPP
