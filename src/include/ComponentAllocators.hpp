#ifndef PUGGO_COMPONENT_ALLOCATORS_HPP
#define PUGGO_COMPONENT_ALLOCATORS_HPP

#include <GenericComponentAllocator.hpp>

#include <BoundingBoxComponent.hpp>
#include <BoundingCapsuleComponent.hpp>
#include <BoundingSphereComponent.hpp>
#include <ColorComponent.hpp>
#include <DirectionalLightComponent.hpp>
#include <MeshComponent.hpp>
#include <PhysicsComponent.hpp>
#include <PointLightComponent.hpp>
#include <SizeComponent.hpp>
#include <SpotLightComponent.hpp>
#include <TextComponent.hpp>
#include <TransformComponent.hpp>
#include <Transform2DComponent.hpp>
#include <ZIndexComponent.hpp>

namespace puggo {
    // SceneObject Specific Components
    using TransformComponentHandle = GenericHandle<18, 14>;
    using TransformComponentAllocator = GenericComponentAllocator<TransformComponent, 18, 14, TransformComponentHandle>;

    using BoundingBoxComponentHandle = GenericHandle<18, 14>;
    using BoundingBoxComponentAllocator = GenericComponentAllocator<BoundingBoxComponent, 18, 14, BoundingBoxComponentHandle>;

    using BoundingCapsuleComponentHandle = GenericHandle<18, 14>;
    using BoundingCapsuleComponentAllocator = GenericComponentAllocator<BoundingCapsuleComponent, 18, 14, BoundingCapsuleComponentHandle>;

    using BoundingSphereComponentHandle = GenericHandle<18, 14>;
    using BoundingSphereComponentAllocator = GenericComponentAllocator<BoundingSphereComponent, 18, 14, BoundingSphereComponentHandle>;

    /*using AnimationComponentHandle = GenericHandle<10, 22>;
    using AnimationComponentAllocator = GenericComponentAllocator<AnimationComponent, 10, 22, AnimationComponentHandle>;*/

    using PointLightComponentHandle = GenericHandle<10, 22>;
    using PointLightComponentAllocator = GenericComponentAllocator<PointLightComponent, 10, 22, PointLightComponentHandle>;

    using DirectionalLightComponentHandle = GenericHandle<10, 22>;
    using DirectionalLightComponentAllocator = GenericComponentAllocator<DirectionalLightComponent, 10, 22, DirectionalLightComponentHandle>;

    using SpotLightComponentHandle = GenericHandle<10, 22>;
    using SpotLightComponentAllocator = GenericComponentAllocator<SpotLightComponent, 10, 22, SpotLightComponentHandle>;

    using PhysicsComponentHandle = GenericHandle<18, 14>;
    using PhysicsComponentAllocator = GenericComponentAllocator<PhysicsComponent, 18, 14, PhysicsComponentHandle>;
    
    // SceneObject/UIObject Components
    using MeshComponentHandle = GenericHandle<10, 22>;
    using MeshComponentAllocator = GenericComponentAllocator<MeshComponent, 10, 22, MeshComponentHandle>;
    
    // UIObject Specific Components
    using ColorComponentHandle = GenericHandle<18, 14>;
    using ColorComponentAllocator = GenericComponentAllocator<ColorComponent, 18, 14, ColorComponentHandle>;

    using SizeComponentHandle = GenericHandle<18, 14>;
    using SizeComponentAllocator = GenericComponentAllocator<SizeComponent, 18, 14, SizeComponentHandle>;

    using TextComponentHandle = GenericHandle<18, 14>;
    using TextComponentAllocator = GenericComponentAllocator<TextComponent, 18, 14, TextComponentHandle>;

    using Transform2DComponentHandle = GenericHandle<18, 14>;
    using Transform2DComponentAllocator = GenericComponentAllocator<Transform2DComponent, 18, 14, Transform2DComponentHandle>;

    using ZIndexComponentHandle = GenericHandle<18, 14>;
    using ZIndexComponentAllocator = GenericComponentAllocator<ZIndexComponent, 18, 14, ZIndexComponentHandle>;
}

#endif // !PUGGO_COMPONENT_ALLOCATORS_HPP
