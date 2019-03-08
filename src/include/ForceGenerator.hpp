#ifndef PUGGO_FORCE_GENERATOR_HPP
#define PUGGO_FORCE_GENERATOR_HPP

#include <SceneObject.hpp>

namespace puggo {
    struct CenterMassForceGenerator {
        vec3 force;
        float duration;
        bool existsIndefinitely;
    };

    struct PositionForceGenerator {
        vec3 force;
        vec3 position;
        float range;
        float duration;
        bool existsIndefinitely;
    };

    struct SpringForceGenerator {
        vec3 position;
        float springConstant;
        float duration;
        bool existsIndefinitely;
    };

    struct AnchoredSpringForceGenerator {
        vec3 anchor;
        float restLength;
        float springConstant;
        float duration;
        bool existsIndefinitely;
    };

    void updateForce(const CenterMassForceGenerator& generator, const SceneObject& sceneObject);
    void updateForce(const PositionForceGenerator& generator, const SceneObject& sceneObject);
    void updateForce(const SpringForceGenerator& generator, const SceneObject& sceneObject);
    void updateForce(const AnchoredSpringForceGenerator& generator, const SceneObject& sceneObject);
}

#endif // !PUGGO_FORCE_GENERATOR_HPP
