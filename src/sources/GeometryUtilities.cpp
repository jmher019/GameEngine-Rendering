#include <GeometryUtilities.hpp>

using namespace puggo;

bool GeometryUtilities::isSegmentIntersectingTriangle(
    const Segment& segment,
    const Triangle& triangle,
    vec3& intersectionPoint
) {
    const vec3 n = triangle.computeNormal();
    const float d = dot(triangle.getVertex1(), n);

    const vec3 lVec = segment.getEnd() - segment.getStart();
    const float len2 = dot(lVec, lVec);

    // if the line degenerates to a point
    if (len2 < GeometryConstants::EPSILON) {
        intersectionPoint = segment.getStart();
        return triangle.isWithinTriangle(intersectionPoint);
    }

    const float t = dot(triangle.getVertex1() - segment.getStart(), n) / dot(lVec, n);

    if (t < 0.f || t > 1.f) {
        return false;
    }

    intersectionPoint = t * lVec + segment.getStart();
    return triangle.isWithinTriangle(intersectionPoint);
}

void GeometryUtilities::computeClosestPointsBetweenSegmentAndTriangle(
    const Segment& segment,
    const Triangle& triangle,
    vec3& segmentPoint,
    vec3& trianglePoint
) {
    if (isSegmentIntersectingTriangle(segment, triangle, segmentPoint)) {
        trianglePoint = segmentPoint;
        return;
    }

    // There can only be at most 5 pairs
    pair<vec3, vec3> pairs[5];
    size_t index = 0;

    // closest point between l and v1 -> v2 segment
    pairs[index] = make_pair(vec3(), vec3());
    segment.computeClosestPointsBetweenSegment(
        Segment(triangle.getVertex1(), triangle.getVertex2()),
        pairs[index].first,
        pairs[index].second
    );


    // closest point between l and v2 -> v3 segment
    pairs[++index] = make_pair(vec3(), vec3());
    segment.computeClosestPointsBetweenSegment(
        Segment(triangle.getVertex2(), triangle.getVertex3()),
        pairs[index].first,
        pairs[index].second
    );

    // closest point between l and v3 -> v1 segment
    pairs[++index] = make_pair(vec3(), vec3());
    segment.computeClosestPointsBetweenSegment(
        Segment(triangle.getVertex3(), triangle.getVertex1()),
        pairs[index].first,
        pairs[index].second
    );

    // closest point from the first vertex in l to the plane containing the triangle
    const vec3 n = triangle.computeNormal();
    const float d = dot(triangle.getVertex1(), n);
    const Plane plane(n, d);
    const vec3 pc = plane.computeClosestPointOnPlane(segment.getStart());
    // check if that point is within the triangle
    if (triangle.isWithinTriangle(pc)) {
        pairs[++index] = make_pair(segment.getStart(), pc);
    }

    // closest point from the second vertex in l to the plane containing the triangle
    const vec3 qc = plane.computeClosestPointOnPlane(segment.getEnd());
    // check if that point is within the triangle
    if (triangle.isWithinTriangle(qc)) {
        pairs[++index] = make_pair(segment.getStart(), qc);
    }

    pair<vec3, vec3>& result = pairs[0];
    vec3 diff = result.second - result.first;
    float dist2 = dot(diff, diff);
    vec3 segmentCenter = 0.5f * (segment.getEnd() - segment.getStart()) + segment.getStart();
    vec3 diffTrianglePointAndSegmentCenter = result.second - segmentCenter;
    float distToSegmentCenter2 = dot(diffTrianglePointAndSegmentCenter, diffTrianglePointAndSegmentCenter);

    for (size_t i = 1; i <= index; i++) {
        diff = pairs[i].second - pairs[i].first;
        float currDist2 = dot(diff, diff);
        diffTrianglePointAndSegmentCenter = pairs[i].second - segmentCenter;
        float currDistToSegmentCenter2 = dot(diffTrianglePointAndSegmentCenter, diffTrianglePointAndSegmentCenter);
        if (dist2 > currDist2 || distToSegmentCenter2 > currDistToSegmentCenter2) {
            dist2 = currDist2;
            distToSegmentCenter2 = currDistToSegmentCenter2;
            result = pairs[i];
        }
    }

    segmentPoint = result.first;
    trianglePoint = result.second;
}

vec3 GeometryUtilities::computeClosestPointBetweenPointAndBox(
    const vec3& target,
    const vec3& boxCenter,
    const vec3& boxXUnitVector,
    const vec3& boxYUnitVector,
    const vec3& boxZUnitVector,
    const vec3& boxActualHalfExtents
) {
    const vec3 d = target - boxCenter;
    // Start result at center of box; kame steps from there
    vec3 result = boxCenter;

    // project d onto the transformed x-axis to get the distance
    // along the axis of d from the box center
    float distX = dot(d, boxXUnitVector);
    if (distX > boxActualHalfExtents.x) {
        distX = boxActualHalfExtents.x;
    }
    else if (distX < -boxActualHalfExtents.x) {
        distX = -boxActualHalfExtents.x;
    }

    result += distX * boxXUnitVector;

    // project d onto the transformed y-axis to get the distance
    // along the axis of d from the box center
    float distY = dot(d, boxYUnitVector);
    if (distY > boxActualHalfExtents.y) {
        distY = boxActualHalfExtents.y;
    }
    else if (distY < -boxActualHalfExtents.y) {
        distY = -boxActualHalfExtents.y;
    }

    result += distY * boxYUnitVector;

    // project d onto the transformed z-axis to get the distance
    // along the axis of d from the box center
    float distZ = dot(d, boxZUnitVector);
    if (distZ > boxActualHalfExtents.z) {
        distZ = boxActualHalfExtents.z;
    }
    else if (distZ < -boxActualHalfExtents.z) {
        distZ = -boxActualHalfExtents.z;
    }

    result += distZ * boxZUnitVector;
    return result;
}

Contact GeometryUtilities::computeContactBetweenVertexAndBox(
    const vec3& testPoint,
    const vec3& obbCenter,
    const vec3& obbXAxis,
    const vec3& obbYAxis,
    const vec3& obbZAxis,
    const vec3& obbActualHalfExtents
) noexcept {
    Contact invalidContact = {
        vec3(),
        vec3(),
        0.f,
        ContactValidity::INVALID
    };

    vec3 planeNormal(0.f, 0.f, 0.f);

    const vec3 d = testPoint - obbCenter;
    // Start result at center of box; kame steps from there
    vec3 result = obbCenter;

    // project d onto the transformed x-axis to get the distance
    // along the axis of d from the box center
    float distX = dot(d, obbXAxis);
    planeNormal = obbXAxis * (distX < 0.f ? -1.f : 1.f);
    float minDepth = obbActualHalfExtents.x - glm::abs(distX);
    if (minDepth < 0.f) {
        return invalidContact;
    }

    if (distX > obbActualHalfExtents.x) {
        distX = obbActualHalfExtents.x;
    }
    else if (distX < -obbActualHalfExtents.x) {
        distX = -obbActualHalfExtents.x;
    }

    result += distX * obbXAxis;

    // project d onto the transformed y-axis to get the distance
    // along the axis of d from the box center
    float distY = dot(d, obbYAxis);
    float depth = obbActualHalfExtents.y - glm::abs(distY);
    if (depth < 0.f) {
        return invalidContact;
    }

    if (depth < minDepth) {
        minDepth = depth;
        planeNormal = obbYAxis * (distY < 0.f ? -1.f : 1.f);
    }

    if (distY > obbActualHalfExtents.y) {
        distY = obbActualHalfExtents.y;
    }
    else if (distY < -obbActualHalfExtents.y) {
        distY = -obbActualHalfExtents.y;
    }

    result += distY * obbYAxis;

    // project d onto the transformed z-axis to get the distance
    // along the axis of d from the box center
    float distZ = dot(d, obbZAxis);
    depth = obbActualHalfExtents.z - glm::abs(distZ);
    if (depth < 0.f) {
        return invalidContact;
    }

    if (depth < minDepth) {
        minDepth = depth;
        planeNormal = obbZAxis * (distZ < 0.f ? -1.f : 1.f);
    }

    if (distZ > obbActualHalfExtents.z) {
        distZ = obbActualHalfExtents.z;
    }
    else if (distZ < -obbActualHalfExtents.z) {
        distZ = -obbActualHalfExtents.z;
    }

    result += distZ * obbZAxis;
    return {
        result,
        planeNormal,
        minDepth,
        ContactValidity::VALID
    };
}