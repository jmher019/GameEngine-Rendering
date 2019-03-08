#ifndef PUGGO_CONTACT_HPP
#define PUGGO_CONTACT_HPP

#include <glm/glm.hpp>

using namespace glm;

namespace puggo {
    enum class ContactValidity {
        INVALID,
        VALID
    };

    struct Contact {
        vec3 contactPoint;
        vec3 contactNormal;
        float penetration;
        ContactValidity validity;
    };
}

#endif // !PUGGO_CONTACT_HPP
