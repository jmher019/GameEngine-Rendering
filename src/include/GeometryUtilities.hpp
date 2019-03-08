#ifndef PUGGO_GEOMETRY_UTILITIES_HPP
#define PUGGO_GEOMETRY_UTILITIES_HPP

#include <vector>

#include <Contact.hpp>
#include <GeometryConstants.hpp>
#include <Segment.hpp>
#include <Plane.hpp>
#include <Triangle.hpp>

namespace puggo {
    namespace GeometryUtilities {
        bool isSegmentIntersectingTriangle(
            const Segment& segment,
            const Triangle& triangle,
            vec3& intersectionPoint
        );

        void computeClosestPointsBetweenSegmentAndTriangle(
            const Segment& segment,
            const Triangle& triangle,
            vec3& segmentPoint,
            vec3& trianglePoint
        );

        vec3 computeClosestPointBetweenPointAndBox(
            const vec3& target,
            const vec3& boxCenter,
            const vec3& boxXUnitVector,
            const vec3& boxYUnitVector,
            const vec3& boxZUnitVector,
            const vec3& boxActualHalfExtents
        );

        Contact computeContactBetweenVertexAndBox(
            const vec3& testPoint,
            const vec3& obbCenter,
            const vec3& obbXAxis,
            const vec3& obbYAxis,
            const vec3& obbZAxis,
            const vec3& obbActualHalfExtents
        ) noexcept;
    };
}

#endif // !PUGGO_GEOMETRY_UTILITIES_HPP
