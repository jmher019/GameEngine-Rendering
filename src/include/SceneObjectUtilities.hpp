#ifndef PUGGO_SCENE_OBJECT_UTILITIES_HPP
#define PUGGO_SCENE_OBJECT_UTILITIES_HPP

#include <SceneObject.hpp>

namespace puggo {
    namespace SceneObjectUtilities {
        SceneObject createSphere(const float& radius);
        SceneObject createCapsule(const float& radius, const float& capsuleCylinderLength);
        SceneObject createBox(const vec3& halfExtents);
        SceneObject createStaticMesh(const MeshComponentHandle& handle);
        SceneObject createRigidbodySphere(
            const float& radius,
            const float& mass,
            const vec3& initialVelocity
        );
        SceneObject createRigidbodyCapsule(
            const float& radius,
            const float& capsuleCylinderLength,
            const float& mass,
            const vec3& initialVelocity
        );
        SceneObject createRigidbodyBox(
            const vec3& halfExtents,
            const float& mass,
            const vec3& initialVelocity
        );
        SceneObject createPointLight(
            const vec3& ambient,
            const vec3& diffuse,
            const vec3& specular,
            const float& constant,
            const float& linear,
            const float& quadratic
        );
        SceneObject createDirectionalLight(
            const vec3& ambient,
            const vec3& diffuse,
            const vec3& specular,
            const vec3& direction
        );
        SceneObject createSpotLight(
            const vec3& ambient,
            const vec3& diffuse,
            const vec3& specular,
            const vec3& direction,
            const float& cutOff
        );
        void addSphereCollision(
            SceneObject& sceneObject,
            const float& radius
        );
        void addCapsuleCollision(
            SceneObject& sceneObject,
            const float& radius,
            const float& capsuleCylinderLength
        );
        void addBoxCollision(
            SceneObject& sceneObject,
            const vec3& halfExtents
        );
        void addMesh(
            SceneObject& sceneObject,
            const MeshComponentHandle& meshComponentHandle
        );
        void addPointLight(
            SceneObject& sceneObject,
            const vec3& ambient,
            const vec3& diffuse,
            const vec3& specular,
            const float& constant,
            const float& linear,
            const float& quadratic
        );
        void addDirectionalLight(
            SceneObject& sceneObject,
            const vec3& ambient,
            const vec3& diffuse,
            const vec3& specular,
            const vec3& direction
        );
        void addSpotLight(
            SceneObject& sceneObject,
            const vec3& ambient,
            const vec3& diffuse,
            const vec3& specular,
            const vec3& direction,
            const float& cutOff
        );
        void addPhysics(
            SceneObject& sceneObject,
            const float& mass,
            const vec3& initialVelocity
        );
    }
}

#endif // !PUGGO_SCENE_OBJECT_UTILITIES_HPP
