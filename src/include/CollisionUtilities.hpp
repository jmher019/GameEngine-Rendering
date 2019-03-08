#ifndef PUGGO_COLLISION_UTILITIES_HPP
#define PUGGO_COLLISION_UTILITIES_HPP

#include <BoundingBoxComponent.hpp>
#include <BoundingCapsuleComponent.hpp>
#include <BoundingSphereComponent.hpp>
#include <Contact.hpp>
#include <GeometryConstants.hpp>
#include <GeometryUtilities.hpp>
#include <PhysicsComponent.hpp>
#include <TransformComponent.hpp>

namespace puggo {
    namespace CollisionUtilities {
        /*
        bool isSphereIntersectingSphere(
            const BoundingSphereComponent& sphere1,
            const TransformComponent& transformComponent1,
            const BoundingSphereComponent& sphere2,
            const TransformComponent& transformComponent2
        ) noexcept;

        bool isCapsuleIntersectingSphere(
            const BoundingCapsuleComponent& capsule,
            const TransformComponent& transformComponentCapsule,
            const BoundingSphereComponent& sphere,
            const TransformComponent& transformComponentSphere
        ) noexcept;

        bool isCapsuleIntersectingCapsule(
            const BoundingCapsuleComponent& capsule1,
            const TransformComponent& transformComponent1,
            const BoundingCapsuleComponent& capsule2,
            const TransformComponent& transformComponent2
        ) noexcept;

        bool isBoxIntersectingSphere(
            const BoundingBoxComponent& box,
            const TransformComponent& transformComponentBox,
            const BoundingSphereComponent& sphere,
            const TransformComponent& transformComponentSphere
        ) noexcept;

        bool isBoxIntersectingCapsule(
            const BoundingBoxComponent& box,
            const TransformComponent& transformComponentBox,
            const BoundingCapsuleComponent& capsule,
            const TransformComponent& transformComponentCapsule
        ) noexcept;

        bool isBoxIntersectingBox(
            const BoundingBoxComponent& box1,
            const TransformComponent& transformComponent1,
            const BoundingBoxComponent& box2,
            const TransformComponent& transformComponent2
        ) noexcept;

        bool isSphereEnclosingSphere(
            const BoundingSphereComponent& sphere1,
            const TransformComponent& transformComponent1,
            const BoundingSphereComponent& sphere2,
            const TransformComponent& transformComponent2
        ) noexcept;

        bool isSphereEnclosingCapsule(
            const BoundingSphereComponent& sphere,
            const TransformComponent& transformComponentSphere,
            const BoundingCapsuleComponent& capsule,
            const TransformComponent& transformComponentCapsule
        ) noexcept;

        bool isSphereEnclosingBox(
            const BoundingSphereComponent& sphere,
            const TransformComponent& transformComponentSphere,
            const BoundingBoxComponent& box,
            const TransformComponent& transformComponentBox
        ) noexcept;

        bool isCapsuleEnclosingSphere(
            const BoundingCapsuleComponent& capsule,
            const TransformComponent& transformComponentCapsule,
            const BoundingSphereComponent& sphere,
            const TransformComponent& transformComponentSphere
        ) noexcept;

        bool isCapsuleEnclosingCapsule(
            const BoundingCapsuleComponent& capsule1,
            const TransformComponent& transformComponent1,
            const BoundingCapsuleComponent& capsule2,
            const TransformComponent& transformComponent2
        ) noexcept;

        bool isCapsuleEnclosingBox(
            const BoundingCapsuleComponent& capsule,
            const TransformComponent& transformComponentCapsule,
            const BoundingBoxComponent& box,
            const TransformComponent& transformComponentBox
        ) noexcept;

        bool isBoxEnclosingSphere(
            const BoundingBoxComponent& box,
            const TransformComponent& transformComponentBox,
            const BoundingSphereComponent& sphere,
            const TransformComponent& transformComponentSphere
        ) noexcept;

        bool isBoxEnclosingCapsule(
            const BoundingBoxComponent& box,
            const TransformComponent& transformComponentBox,
            const BoundingCapsuleComponent& capsule,
            const TransformComponent& transformComponentCapsule
        ) noexcept;

        bool isBoxEnclosingBox(
            const BoundingBoxComponent& box1,
            const TransformComponent& transformComponent1,
            const BoundingBoxComponent& box2,
            const TransformComponent& transformComponent2
        ) noexcept;

        Contact findContactBetweenSphereAndSphere(
            const BoundingSphereComponent& sphere1,
            const TransformComponent& transformComponent1,
            const BoundingSphereComponent& sphere2,
            const TransformComponent& transformComponent2
        ) noexcept;

        Contact findContactBetweenSphereAndCapsule(
            const BoundingSphereComponent& sphere,
            const TransformComponent& transformComponentSphere,
            const BoundingCapsuleComponent& capsule,
            const TransformComponent& transformComponentCapsule
        ) noexcept;

        Contact findContactBetweenSphereAndBox(
            const BoundingSphereComponent& sphere,
            const TransformComponent& transformComponentSphere,
            const BoundingBoxComponent& box,
            const TransformComponent& transformComponentBox
        ) noexcept;

        Contact findContactBetweenCapsuleAndSphere(
            const BoundingCapsuleComponent& capsule,
            const TransformComponent& transformComponentCapsule,
            const BoundingSphereComponent& sphere,
            const TransformComponent& transformComponentSphere
        ) noexcept;

        Contact findContactBetweenCapsuleAndCapsule(
            const BoundingCapsuleComponent& capsule1,
            const TransformComponent& transformComponent1,
            const BoundingCapsuleComponent& capsule2,
            const TransformComponent& transformComponent2
        ) noexcept;

        Contact findContactBetweenCapsuleAndBox(
            const BoundingCapsuleComponent& capsule,
            const TransformComponent& transformComponentCapsule,
            const BoundingBoxComponent& box,
            const TransformComponent& transformComponentBox
        ) noexcept;

        Contact findContactBetweenBoxAndSphere(
            const BoundingBoxComponent& box,
            const TransformComponent& transformComponentBox,
            const BoundingSphereComponent& sphere,
            const TransformComponent& transformComponentSphere
        ) noexcept;

        Contact findContactBetweenBoxAndCapsule(
            const BoundingBoxComponent& box,
            const TransformComponent& transformComponentBox,
            const BoundingCapsuleComponent& capsule,
            const TransformComponent& transformComponentCapsule
        ) noexcept;

        Contact findContactBetweenBoxAndBox(
            const BoundingBoxComponent& box1,
            const TransformComponent& transformComponent1,
            const BoundingBoxComponent& box2,
            const TransformComponent& transformComponent2
        ) noexcept;

        bool areMovingSphereAndSphereIntersecting(
            const BoundingSphereComponent& sphere1,
            const TransformComponent& transformComponent1,
            const PhysicsComponent& physicsComponent1,
            const BoundingSphereComponent& sphere2,
            const TransformComponent& transformComponent2,
            const PhysicsComponent& physicsComponent2,
            const float& startTimePoint,
            const float& finalTimePoint,
            float& intersectionTimePoint
        ) noexcept;

        bool areMovingCapsuleAndSphereIntersecting(
            const BoundingCapsuleComponent& capsule,
            const TransformComponent& transformComponentCapsule,
            const PhysicsComponent& physicsComponentCapsule,
            const BoundingSphereComponent& sphere,
            const TransformComponent& transformComponentSphere,
            const PhysicsComponent& physicsComponentSphere,
            const float& startTimePoint,
            const float& finalTimePoint,
            float& intersectionTimePoint
        ) noexcept;

        bool areMovingCapsuleAndCapsuleIntersecting(
            const BoundingCapsuleComponent& capsule1,
            const TransformComponent& transformComponent1,
            const PhysicsComponent& physicsComponent1,
            const BoundingCapsuleComponent& capsule2,
            const TransformComponent& transformComponent2,
            const PhysicsComponent& physicsComponent2,
            const float& startTimePoint,
            const float& finalTimePoint,
            float& intersectionTimePoint
        ) noexcept;

        bool areMovingBoxAndSphereIntersecting(
            const BoundingBoxComponent& box,
            const TransformComponent& transformComponentBox,
            const PhysicsComponent& physicsComponentBox,
            const BoundingSphereComponent& sphere,
            const TransformComponent& transformComponentSphere,
            const PhysicsComponent& physicsComponentSphere,
            const float& startTimePoint,
            const float& finalTimePoint,
            float& intersectionTimePoint
        ) noexcept;

        bool areMovingBoxAndCapsuleIntersecting(
            const BoundingBoxComponent& box,
            const TransformComponent& transformComponentBox,
            const PhysicsComponent& physicsComponentBox,
            const BoundingCapsuleComponent& capsule,
            const TransformComponent& transformComponentCapsule,
            const PhysicsComponent& physicsComponentCapsule,
            const float& startTimePoint,
            const float& finalTimePoint,
            float& intersectionTimePoint
        ) noexcept;

        bool areMovingBoxAndBoxIntersecting(
            const BoundingBoxComponent& box1,
            const TransformComponent& transformComponent1,
            const PhysicsComponent& physicsComponent1,
            const BoundingBoxComponent& box2,
            const TransformComponent& transformComponent2,
            const PhysicsComponent& physicsComponent2,
            const float& startTimePoint,
            const float& finalTimePoint,
            float& intersectionTimePoint
        ) noexcept;
        */
    }
}

#endif // !PUGGO_COLLISION_UTILITIES_HPP
