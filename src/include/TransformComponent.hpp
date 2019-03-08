#ifndef PUGGO_TRANSFORM_COMPONENT_HPP
#define PUGGO_TRANSFORM_COMPONENT_HPP

#include <Transform.hpp>

using namespace std;

namespace puggo {
    class TransformComponent {
    public:
        TransformComponent(void);
        TransformComponent(const TransformComponent& component);
        TransformComponent(TransformComponent&& component) noexcept;
        
        TransformComponent& operator=(const TransformComponent& component);
        TransformComponent& operator=(TransformComponent&& component) noexcept;
        bool operator==(const TransformComponent& component) noexcept;

        const Transform& getLocalTransform(void) const;
        const Transform& getGlobalTransform(void) const;

        void translate(const vec3& t);
        void translate(const float& tX, const float& tY, const float& tZ);
        void rotate(const vec3& degrees);
        void rotate(const float& degreesX, const float& degreesY, const float& degreesZ);
        void generalRotate(const float& degrees, const vec3& axis);
        void orbit(const vec3& degrees);
        void orbit(const float& degreesX, const float& degreesY, const float& degreesZ);
        void generalOrbit(const float& degrees, const vec3& axis);
        void scale(const vec3& s);
        void scale(const float& sX, const float& sY, const float& sZ);
        void updateGlobalTransform(const Transform& parentTransform);
    
    private:
        Transform localTransform;
        Transform globalTransform;
    };
}

#endif // !PUGGO_TRANSFORMABLE_COMPONENT_HPP
