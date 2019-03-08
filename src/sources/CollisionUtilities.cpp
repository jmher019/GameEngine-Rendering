#include <CollisionUtilities.hpp>

/*using namespace puggo;

bool CollisionUtilities::isSphereIntersectingSphere(
    const BoundingSphereComponent& sphere1,
    const TransformComponent& transformComponent1,
    const BoundingSphereComponent& sphere2,
    const TransformComponent& transformComponent2
) noexcept {
    const Transform& transform1 = transformComponent1.getGlobalTransform();
    const Transform& transform2 = transformComponent2.getGlobalTransform();

    const vec3 center1 = sphere1.getCenter(transform1);
    const vec3 center2 = sphere2.getCenter(transform2);
    const vec3 offset = center1 - center2;
    const float dist2 = dot(offset, offset);
    const float radiusSum = sphere1.getActualRadius(transform1) + sphere2.getActualRadius(transform2);

    return dist2 - radiusSum * radiusSum <= GeometryConstants::EPSILON;
}

bool CollisionUtilities::isCapsuleIntersectingSphere(
    const BoundingCapsuleComponent& capsule,
    const TransformComponent& transformComponentCapsule,
    const BoundingSphereComponent& sphere,
    const TransformComponent& transformComponentSphere
) noexcept {
    const Transform& transformCapsule = transformComponentCapsule.getGlobalTransform();
    const Transform& transformSphere = transformComponentSphere.getGlobalTransform();

    const Segment segment = capsule.getActualSegment(transformCapsule);
    const float radius = capsule.getActualRadius(transformCapsule);

    const vec3 sphereCenter = sphere.getCenter(transformSphere);
    const vec3 capsuleLinePoint = segment.computeClosestPointOnSegment(sphereCenter);
    const vec3 offset = capsuleLinePoint - sphereCenter;
    const float radiusSum = radius + sphere.getActualRadius(transformSphere);
    const float dist2 = dot(offset, offset);

    return dist2 - radiusSum * radiusSum <= GeometryConstants::EPSILON;
}

bool CollisionUtilities::isCapsuleIntersectingCapsule(
    const BoundingCapsuleComponent& capsule1,
    const TransformComponent& transformComponent1,
    const BoundingCapsuleComponent& capsule2,
    const TransformComponent& transformComponent2
) noexcept {
    const Transform& transform1 = transformComponent1.getGlobalTransform();
    const Transform& transform2 = transformComponent2.getGlobalTransform();

    const Segment segment1 = capsule1.getActualSegment(transform1);
    const Segment segment2 = capsule2.getActualSegment(transform2);

    vec3 c1, c2;
    segment1.computeClosestPointsBetweenSegment(segment2, c1, c2);
    const vec3 offset = c2 - c1;
    const float radiusSum = capsule1.getActualRadius(transform1) + capsule2.getActualRadius(transform2);

    return dot(offset, offset) - radiusSum * radiusSum <= GeometryConstants::EPSILON;
}

bool CollisionUtilities::isBoxIntersectingSphere(
    const BoundingBoxComponent& box,
    const TransformComponent& transformComponentBox,
    const BoundingSphereComponent& sphere,
    const TransformComponent& transformComponentSphere
) noexcept {
    const Transform& transformBox = transformComponentBox.getGlobalTransform();
    const Transform& transformSphere = transformComponentSphere.getGlobalTransform();

    const vec3 center = sphere.getCenter(transformSphere);
    const vec3 closestPoint = GeometryUtilities::computeClosestPointBetweenPointAndBox(
        center,
        box.getCenter(transformBox),
        transformBox.getXUnitVector(),
        transformBox.getYUnitVector(),
        transformBox.getZUnitVector(),
        box.getActualHalfExtents(transformBox)
    );
    const vec3 diff = closestPoint - center;
    const float dist2 = dot(diff, diff);
    const float radius = sphere.getActualRadius(transformSphere);

    return dist2 - radius * radius <= GeometryConstants::EPSILON;
}

bool CollisionUtilities::isBoxIntersectingCapsule(
    const BoundingBoxComponent& box,
    const TransformComponent& transformComponentBox,
    const BoundingCapsuleComponent& capsule,
    const TransformComponent& transformComponentCapsule
) noexcept {
    const Transform& transformBox = transformComponentBox.getGlobalTransform();
    const Transform& transformCapsule = transformComponentCapsule.getGlobalTransform();

    vector<Triangle> triangles = box.getTriangles(transformBox);
    vec3 closestPointSegment, closestPointTriangle;
    const Segment segment = capsule.getActualSegment(transformCapsule);
    const vec3 bCenter = capsule.getCenter(transformCapsule);
    GeometryUtilities::computeClosestPointsBetweenSegmentAndTriangle(segment, triangles[0], closestPointSegment, closestPointTriangle);
    vec3 offset = closestPointTriangle - closestPointSegment;
    float dist2 = dot(offset, offset);
    for (size_t i = 1; i < triangles.size(); i++) {
        GeometryUtilities::computeClosestPointsBetweenSegmentAndTriangle(segment, triangles[i], closestPointSegment, closestPointTriangle);
        offset = closestPointTriangle - closestPointSegment;
        float currDist2 = dot(offset, offset);
        if (currDist2 < dist2) {
            dist2 = currDist2;
        }
    }

    const float radius = move(capsule.getActualRadius(transformCapsule));
    return dist2 - radius * radius <= GeometryConstants::EPSILON;
}

bool CollisionUtilities::isBoxIntersectingBox(
    const BoundingBoxComponent& box1,
    const TransformComponent& transformComponent1,
    const BoundingBoxComponent& box2,
    const TransformComponent& transformComponent2
) noexcept {
    const Transform& transformBox1 = transformComponent1.getGlobalTransform();
    const Transform& transformBox2 = transformComponent2.getGlobalTransform();

    float ra, rb;
    vec3 axis1[3] = {
        transformBox1.getXUnitVector(),
        transformBox1.getYUnitVector(),
        transformBox1.getZUnitVector()
    };

    vec3 axis2[3] = {
        transformBox2.getXUnitVector(),
        transformBox2.getYUnitVector(),
        transformBox2.getZUnitVector()
    };

    mat3 R, absR;
    const vec3 halfExtents2 = box2.getActualHalfExtents(transformBox2);

    // compute rotation matrix expressing b in a's coordinate frame
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            R[i][j] = dot(axis1[i], axis2[j]);
        }
    }

    // compute translation vector t
    const vec3 center1 = box1.getCenter(transformBox1);
    const vec3 center2 = box2.getCenter(transformBox2);
    vec3 t = center2 - center1;
    // bring translation into a's coordinate frame
    t = vec3(dot(t, axis1[0]), dot(t, axis1[1]), dot(t, axis1[2]));

    // Compute common subexpressions. Add in an epsilon term to counteract arithmetic errors
    // when two edges are parallel and their cross product is (near) null
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            absR[i][j] = glm::abs(R[i][j]) + GeometryConstants::EPSILON;
        }
    }

    // Test axes L = A0, L = A1, L = A2
    const vec3 halfExtents1 = box1.getActualHalfExtents(transformBox1);
    for (int i = 0; i < 3; i++) {
        ra = halfExtents1[i];
        rb = halfExtents2[0] * absR[0][i] + halfExtents2[1] * absR[1][i] + halfExtents2[2] * absR[2][i];
        if (fabs(t[i]) > ra + rb) {
            return false;
        }
    }

    // Test axes L = B0, L = B1, L = B2
    for (int i = 0; i < 3; i++) {
        ra = halfExtents1[0] * absR[i][0] + halfExtents1[1] * absR[i][1] + halfExtents1[2] * absR[i][2];
        rb = halfExtents2[i];
        if (fabs(t[0] * R[i][0] + t[1] * R[i][1] + t[2] * R[i][2]) > ra + rb) {
            return false;
        }
    }

    // Test axis L = A0 x B0
    ra = halfExtents1[1] * absR[0][2] + halfExtents1[2] * absR[0][1];
    rb = halfExtents2[1] * absR[2][0] + halfExtents2[2] * absR[1][0];
    if (fabs(t[2] * R[0][1] - t[1] * R[0][2]) > ra + rb) {
        return false;
    }

    // Test axis L = A0 x B1
    ra = halfExtents1[1] * absR[1][2] + halfExtents1[2] * absR[1][1];
    rb = halfExtents2[1] * absR[2][0] + halfExtents2[2] * absR[0][0];
    if (fabs(t[2] * R[1][1] - t[1] * R[1][2]) > ra + rb) {
        return false;
    }

    // Test axis L = A0 X B2
    ra = halfExtents1[1] * absR[2][2] + halfExtents1[2] * absR[2][1];
    rb = halfExtents2[0] * absR[1][0] + halfExtents2[1] * absR[0][0];
    if (fabs(t[2] * R[2][1] - t[1] * R[2][2]) > ra + rb) {
        return false;
    }

    // Test axis L = A1 X B0
    ra = halfExtents1[0] * absR[0][2] + halfExtents1[2] * absR[0][0];
    rb = halfExtents2[1] * absR[2][1] + halfExtents2[2] * absR[1][1];
    if (fabs(t[0] * R[0][2] - t[2] * R[0][0]) > ra + rb) {
        return false;
    }

    // Test axis L = A1 X B1
    ra = halfExtents1[0] * absR[1][2] + halfExtents1[2] * absR[1][0];
    rb = halfExtents2[0] * absR[2][1] + halfExtents2[2] * absR[0][1];
    if (fabs(t[0] * R[1][2] - t[2] * R[1][0]) > ra + rb) {
        return false;
    }

    // Test axis L = A1 X B2
    ra = halfExtents1[0] * absR[2][2] + halfExtents1[2] * absR[2][0];
    rb = halfExtents2[0] * absR[1][1] + halfExtents2[1] * absR[0][1];
    if (fabs(t[0] * R[2][2] - t[2] * R[2][0]) > ra + rb) {
        return false;
    }

    // Test axis L = A2 X B0
    ra = halfExtents1[0] * absR[0][1] + halfExtents1[1] * absR[0][0];
    rb = halfExtents2[1] * absR[2][2] + halfExtents2[2] * absR[1][2];
    if (fabs(t[1] * R[0][0] - t[0] * R[0][1]) > ra + rb) {
        return false;
    }

    // Test axis L = A2 X B1
    ra = halfExtents1[0] * absR[1][1] + halfExtents1[1] * absR[1][0];
    rb = halfExtents2[0] * absR[2][2] + halfExtents2[2] * absR[0][2];
    if (fabs(t[1] * R[1][0] - t[0] * R[1][1]) > ra + rb) {
        return false;
    }

    // Test axis L = A2 X B2
    ra = halfExtents1[0] * absR[2][1] + halfExtents1[1] * absR[2][0];
    rb = halfExtents2[0] * absR[1][2] + halfExtents2[1] * absR[0][2];
    if (fabs(t[1] * R[2][0] - t[0] * R[2][1]) > ra + rb) {
        return false;
    }

    return true;
}

bool CollisionUtilities::isSphereEnclosingSphere(
    const BoundingSphereComponent& sphere1,
    const TransformComponent& transformComponent1,
    const BoundingSphereComponent& sphere2,
    const TransformComponent& transformComponent2
) noexcept {
    const Transform& transform1 = transformComponent1.getGlobalTransform();
    const Transform& transform2 = transformComponent2.getGlobalTransform();
    
    const float radius = sphere1.getActualRadius(transform1);
    const vec3 diff = sphere1.getCenter(transform1) - sphere2.getCenter(transform2);
    const float fullDist = length(diff) + radius;
    const float& bRadius = sphere2.getActualRadius(transform2);

    return fullDist - bRadius <= GeometryConstants::EPSILON;
}

bool CollisionUtilities::isSphereEnclosingCapsule(
    const BoundingSphereComponent& sphere,
    const TransformComponent& transformComponentSphere,
    const BoundingCapsuleComponent& capsule,
    const TransformComponent& transformComponentCapsule
) noexcept {
    const Transform& transformSphere = transformComponentSphere.getGlobalTransform();
    const Transform& transformCapsule = transformComponentCapsule.getGlobalTransform();

    const Segment segment = capsule.getActualSegment(transformCapsule);
    const float capsuleRadius = capsule.getActualRadius(transformCapsule);

    const vec3 spehereCenter = sphere.getCenter(transformSphere);
    const vec3 diff1 = segment.getStart() - spehereCenter;
    const vec3 diff2 = segment.getEnd() - spehereCenter;
    const float fullDist1 = length(diff1) + capsuleRadius;
    const float fullDist2 = length(diff2) + capsuleRadius;
    const float sphereRadius = sphere.getActualRadius(transformSphere);

    return fullDist1 - sphereRadius <= GeometryConstants::EPSILON && fullDist2 - sphereRadius <= GeometryConstants::EPSILON;
}

bool CollisionUtilities::isSphereEnclosingBox(
    const BoundingSphereComponent& sphere,
    const TransformComponent& transformComponentSphere,
    const BoundingBoxComponent& box,
    const TransformComponent& transformComponentBox
) noexcept {
    const Transform& transformSphere = transformComponentSphere.getGlobalTransform();
    const Transform& transformBox = transformComponentBox.getGlobalTransform();

    const vec3 center = box.getCenter(transformBox);
    const vec3 halfExtents = box.getActualHalfExtents(transformBox);
    const vec3 xLen = transformBox.getXUnitVector() * halfExtents.x;
    const vec3 yLen = transformBox.getYUnitVector() * halfExtents.y;
    const vec3 zLen = transformBox.getZUnitVector() * halfExtents.z;

    constexpr size_t NUM_TEST_POINTS = 8;
    const vec3 testPoints[NUM_TEST_POINTS] = {
        -xLen - yLen - zLen,
        -xLen - yLen + zLen,
        xLen - yLen - zLen,
        xLen - yLen + zLen,
        xLen + yLen + zLen,
        xLen + yLen - zLen,
        -xLen + yLen + zLen,
        -xLen + yLen - zLen
    };

    const vec3 t = center - sphere.getCenter(transformSphere);
    const float sphereRadius = sphere.getActualRadius(transformSphere);
    const float sphereRadius2 = sphereRadius * sphereRadius;
    for (size_t i = 0; i < NUM_TEST_POINTS; ++i) {
        const vec3& diff = testPoints[i] + t;

        if (dot(diff, diff) - sphereRadius2 > GeometryConstants::EPSILON) {
            return false;
        }
    }

    return true;
}

bool CollisionUtilities::isCapsuleEnclosingSphere(
    const BoundingCapsuleComponent& capsule,
    const TransformComponent& transformComponentCapsule,
    const BoundingSphereComponent& sphere,
    const TransformComponent& transformComponentSphere
) noexcept {
    const Transform& transformCapsule = transformComponentCapsule.getGlobalTransform();
    const Transform& transformSphere = transformComponentSphere.getGlobalTransform();

    const Segment segment = capsule.getActualSegment(transformCapsule);
    const float radius = capsule.getActualRadius(transformCapsule);

    const vec3 sphereCenter = sphere.getCenter(transformSphere);
    const vec3 diff = segment.computeClosestPointOnSegment(sphereCenter) - sphereCenter;
    const float fullDist = length(diff) + sphere.getActualRadius(transformSphere);

    return fullDist - radius <= GeometryConstants::EPSILON;
}

bool CollisionUtilities::isCapsuleEnclosingCapsule(
    const BoundingCapsuleComponent& capsule1,
    const TransformComponent& transformComponent1,
    const BoundingCapsuleComponent& capsule2,
    const TransformComponent& transformComponent2
) noexcept {
    const Transform& transform1 = transformComponent1.getGlobalTransform();
    const Transform& transform2 = transformComponent2.getGlobalTransform();

    const Segment segment1 = capsule1.getActualSegment(transform1);
    const float radius1 = capsule1.getActualRadius(transform1);

    const Segment segment2 = capsule2.getActualSegment(transform2);
    const float radius2 = capsule2.getActualRadius(transform2);

    const vec3 diff1 = segment1.computeClosestPointOnSegment(segment2.getStart()) - segment2.getStart();
    const vec3 diff2 = segment1.computeClosestPointOnSegment(segment2.getEnd()) - segment2.getEnd();
    const float fullDist1 = length(diff1) + radius2;
    const float fullDist2 = length(diff2) + radius2;

    return fullDist1 - radius1 <= GeometryConstants::EPSILON && fullDist2 - radius1 <= GeometryConstants::EPSILON;
}

bool CollisionUtilities::isCapsuleEnclosingBox(
    const BoundingCapsuleComponent& capsule,
    const TransformComponent& transformComponentCapsule,
    const BoundingBoxComponent& box,
    const TransformComponent& transformComponentBox
) noexcept {
    const Transform& transformCapsule = transformComponentCapsule.getGlobalTransform();
    const Transform& transformBox = transformComponentBox.getGlobalTransform();

    const vec3 center = box.getCenter(transformBox);
    const vec3 halfExtents = box.getActualHalfExtents(transformBox);
    const vec3 xLen = transformBox.getXUnitVector() * halfExtents.x;
    const vec3 yLen = transformBox.getYUnitVector() * halfExtents.y;
    const vec3 zLen = transformBox.getZUnitVector() * halfExtents.z;

    constexpr size_t NUM_TEST_POINTS = 8;
    const vec3 testPoints[NUM_TEST_POINTS] = {
        center - xLen - yLen - zLen,
        center - xLen - yLen + zLen,
        center + xLen - yLen - zLen,
        center + xLen - yLen + zLen,
        center + xLen + yLen + zLen,
        center + xLen + yLen - zLen,
        center - xLen + yLen + zLen,
        center - xLen + yLen - zLen
    };

    const Segment segment = capsule.getActualSegment(transformCapsule);
    const float radius = capsule.getActualRadius(transformCapsule);
    const float radius2 = radius * radius;
    for (size_t i = 0; i < NUM_TEST_POINTS; ++i) {
        const vec3& diff = segment.computeClosestPointOnSegment(testPoints[i]) - testPoints[i];

        if (dot(diff, diff) - radius2 > GeometryConstants::EPSILON) {
            return false;
        }
    }

    return true;
}

bool CollisionUtilities::isBoxEnclosingSphere(
    const BoundingBoxComponent& box,
    const TransformComponent& transformComponentBox,
    const BoundingSphereComponent& sphere,
    const TransformComponent& transformComponentSphere
) noexcept {
    const Transform& transformBox = transformComponentBox.getGlobalTransform();
    const Transform& transformSphere = transformComponentSphere.getGlobalTransform();

    vec3 axis1[3] = {
        transformBox.getXUnitVector(),
        transformBox.getYUnitVector(),
        transformBox.getZUnitVector()
    };

    mat4 sphereModel = Transform(transformSphere.getTranslationAndRotation()).getMatrix();
    vec3 axis2[3] = {
        normalize(vec3(sphereModel * vec4(1.f, 0.f, 0.f, 0.f))),
        normalize(vec3(sphereModel * vec4(0.f, 1.f, 0.f, 0.f))),
        normalize(vec3(sphereModel * vec4(0.f, 0.f, 1.f, 0.f)))
    };

    // compute rotation matrix expressing b in a's coordinate frame
    mat3 R;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            R[i][j] = dot(axis1[i], axis2[j]);
        }
    }

    // compute translation vector t
    vec3 t = sphere.getCenter(transformSphere) - box.getCenter(transformBox);
    // bring translation into a's coordinate frame
    t = vec3(dot(t, axis1[0]), dot(t, axis1[1]), dot(t, axis1[2]));

    const float& radius = sphere.getActualRadius(transformSphere);
    constexpr size_t NUM_TEST_POINTS = 8;
    const vec3 testPoints[NUM_TEST_POINTS] = {
        vec3(-radius, -radius, -radius),
        vec3(-radius, -radius, radius),
        vec3(radius, -radius, -radius),
        vec3(radius, -radius, radius),
        vec3(radius, radius, radius),
        vec3(radius, radius, -radius),
        vec3(-radius, radius, radius),
        vec3(-radius, radius, -radius)
    };

    const vec3 halfExtents = box.getActualHalfExtents(transformBox);
    for (size_t i = 0; i < NUM_TEST_POINTS; ++i) {
        const vec3 pt = t + R * testPoints[i];

        if (
                pt.x - halfExtents.x > GeometryConstants::EPSILON ||
                pt.x + halfExtents.x < -GeometryConstants::EPSILON ||
                pt.y - halfExtents.y > GeometryConstants::EPSILON ||
                pt.y + halfExtents.y < -GeometryConstants::EPSILON ||
                pt.z - halfExtents.z > GeometryConstants::EPSILON ||
                pt.z + halfExtents.z < -GeometryConstants::EPSILON
            ) {
            return false;
        }
    }

    return true;
}

bool CollisionUtilities::isBoxEnclosingCapsule(
    const BoundingBoxComponent& box,
    const TransformComponent& transformComponentBox,
    const BoundingCapsuleComponent& capsule,
    const TransformComponent& transformComponentCapsule
) noexcept {
    const Transform& transformBox = transformComponentBox.getGlobalTransform();
    const Transform& transformCapsule = transformComponentCapsule.getGlobalTransform();

    vec3 axis1[3] = {
        transformBox.getXUnitVector(),
        transformBox.getYUnitVector(),
        transformBox.getZUnitVector()
    };

    mat4 bModel = Transform(transformCapsule.getTranslationAndRotation()).getMatrix();
    vec3 axis2[3] = {
        normalize(vec3(bModel * vec4(1.f, 0.f, 0.f, 0.f))),
        normalize(vec3(bModel * vec4(0.f, 1.f, 0.f, 0.f))),
        normalize(vec3(bModel * vec4(0.f, 0.f, 1.f, 0.f)))
    };

    // compute rotation matrix expressing b in a's coordinate frame
    mat3 R;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            R[i][j] = dot(axis1[i], axis2[j]);
        }
    }

    // compute translation vector t
    const Segment segment = capsule.getActualSegment(transformCapsule);
    vec3 t1 = segment.getStart() - box.getCenter(transformBox);
    vec3 t2 = segment.getEnd() - box.getCenter(transformBox);
    // bring translation into a's coordinate frame
    t1 = vec3(dot(t1, axis1[0]), dot(t1, axis1[1]), dot(t1, axis1[2]));
    t2 = vec3(dot(t2, axis1[0]), dot(t2, axis1[1]), dot(t2, axis1[2]));

    const vec3& point1 = segment.getStart();
    const vec3& point2 = segment.getEnd();

    const float radius = capsule.getActualRadius(transformCapsule);
    constexpr size_t NUM_TEST_POINTS = 8;
    const vec3 testPoints[NUM_TEST_POINTS] = {
        vec3(-radius, -radius, -radius),
        vec3(-radius, -radius, radius),
        vec3(radius, -radius, -radius),
        vec3(radius, -radius, radius),
        vec3(radius, radius, radius),
        vec3(radius, radius, -radius),
        vec3(-radius, radius, radius),
        vec3(-radius, radius, -radius)
    };

    const vec3 halfExtents = box.getActualHalfExtents(transformBox);
    for (size_t i = 0; i < NUM_TEST_POINTS; ++i) {
        const vec3 pt = t1 + R * testPoints[i];

        if (
                pt.x - halfExtents.x > GeometryConstants::EPSILON ||
                pt.x + halfExtents.x < -GeometryConstants::EPSILON ||
                pt.y - halfExtents.y > GeometryConstants::EPSILON ||
                pt.y + halfExtents.y < -GeometryConstants::EPSILON ||
                pt.z - halfExtents.z > GeometryConstants::EPSILON ||
                pt.z + halfExtents.z < -GeometryConstants::EPSILON
            ) {
            return false;
        }
    }

    for (size_t i = 0; i < NUM_TEST_POINTS; ++i) {
        const vec3 pt = t2 + R * testPoints[i];

        if (
                pt.x - halfExtents.x > GeometryConstants::EPSILON ||
                pt.x + halfExtents.x < -GeometryConstants::EPSILON ||
                pt.y - halfExtents.y > GeometryConstants::EPSILON ||
                pt.y + halfExtents.y < -GeometryConstants::EPSILON ||
                pt.z - halfExtents.z > GeometryConstants::EPSILON ||
                pt.z + halfExtents.z < -GeometryConstants::EPSILON
            ) {
            return false;
        }
    }

    return true;
}

bool CollisionUtilities::isBoxEnclosingBox(
    const BoundingBoxComponent& box1,
    const TransformComponent& transformComponent1,
    const BoundingBoxComponent& box2,
    const TransformComponent& transformComponent2
) noexcept {
    const Transform& transformBox1 = transformComponent1.getGlobalTransform();
    const Transform& transformBox2 = transformComponent2.getGlobalTransform();

    vec3 axis1[3] = {
        transformBox1.getXUnitVector(),
        transformBox1.getYUnitVector(),
        transformBox1.getZUnitVector()
    };

    vec3 axis2[3] = {
        transformBox2.getXUnitVector(),
        transformBox2.getYUnitVector(),
        transformBox2.getZUnitVector()
    };

    // compute rotation matrix expressing b in a's coordinate frame
    mat3 R;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            R[i][j] = dot(axis1[i], axis2[j]);
        }
    }

    // compute translation vector t
    vec3 t = box2.getCenter(transformBox2) - box1.getCenter(transformBox1);
    // bring translation into a's coordinate frame
    t = vec3(dot(t, axis1[0]), dot(t, axis1[1]), dot(t, axis1[2]));

    const vec3 bHalfExtents = box2.getActualHalfExtents(transformBox2);
    constexpr size_t NUM_TEST_POINTS = 8;
    const vec3 testPoints[NUM_TEST_POINTS] = {
        vec3(-bHalfExtents.x, -bHalfExtents.y, -bHalfExtents.z),
        vec3(-bHalfExtents.x, -bHalfExtents.y, bHalfExtents.z),
        vec3(bHalfExtents.x, -bHalfExtents.y, -bHalfExtents.z),
        vec3(bHalfExtents.x, -bHalfExtents.y, bHalfExtents.z),
        vec3(bHalfExtents.x, bHalfExtents.y, bHalfExtents.z),
        vec3(bHalfExtents.x, bHalfExtents.y, -bHalfExtents.z),
        vec3(-bHalfExtents.x, bHalfExtents.y, bHalfExtents.z),
        vec3(-bHalfExtents.x, bHalfExtents.y, -bHalfExtents.z)
    };

    const vec3 halfExtents = box1.getActualHalfExtents(transformBox1);
    for (size_t i = 0; i < NUM_TEST_POINTS; ++i) {
        const vec3 pt = t + R * testPoints[i];

        if (pt.x - halfExtents.x > GeometryConstants::EPSILON ||
            pt.x + halfExtents.x < -GeometryConstants::EPSILON ||
            pt.y - halfExtents.y > GeometryConstants::EPSILON ||
            pt.y + halfExtents.y < -GeometryConstants::EPSILON ||
            pt.z - halfExtents.z > GeometryConstants::EPSILON ||
            pt.z + halfExtents.z < -GeometryConstants::EPSILON) {
            return false;
        }
    }

    return true;
}

Contact CollisionUtilities::findContactBetweenSphereAndSphere(
    const BoundingSphereComponent& sphere1,
    const TransformComponent& transformComponent1,
    const BoundingSphereComponent& sphere2,
    const TransformComponent& transformComponent2
) noexcept {
    const Transform& transform1 = transformComponent1.getGlobalTransform();
    const Transform& transform2 = transformComponent2.getGlobalTransform();

    const vec3 center1 = sphere1.getCenter(transform1);
    const vec3 center2 = sphere2.getCenter(transform2);
    const vec3 offset = center1 - center2;
    const float dist = glm::sqrt(dot(offset, offset));
    const float radiusSum = sphere1.getActualRadius(transform1) + sphere2.getActualRadius(transform2);

    return {
        center1 + offset * 0.5f,
        offset / dist,
        radiusSum - dist,
        ContactValidity::VALID
    };
}

Contact CollisionUtilities::findContactBetweenSphereAndCapsule(
    const BoundingSphereComponent& sphere,
    const TransformComponent& transformComponentSphere,
    const BoundingCapsuleComponent& capsule,
    const TransformComponent& transformComponentCapsule
) noexcept {
    const Transform& transformSphere = transformComponentSphere.getGlobalTransform();
    const Transform& transformCapsule = transformComponentCapsule.getGlobalTransform();

    const Segment segment = capsule.getActualSegment(transformCapsule);
    const float capsuleRadius = capsule.getActualRadius(transformCapsule);

    const vec3 sphereCenter = sphere.getCenter(transformSphere);
    const vec3 capsuleLinePoint = segment.computeClosestPointOnSegment(sphereCenter);
    const vec3 offset = capsuleLinePoint - sphereCenter;
    const float radiusSum = capsuleRadius + sphere.getActualRadius(transformSphere);
    const float dist = glm::sqrt(dot(offset, offset));

    return {
        capsuleLinePoint - offset * 0.5f,
        -offset / dist,
        radiusSum - dist,
        ContactValidity::VALID
    };
}

Contact CollisionUtilities::findContactBetweenSphereAndBox(
    const BoundingSphereComponent& sphere,
    const TransformComponent& transformComponentSphere,
    const BoundingBoxComponent& box,
    const TransformComponent& transformComponentBox
) noexcept {
    const Transform& transformSphere = transformComponentSphere.getGlobalTransform();
    const Transform& transformBox = transformComponentBox.getGlobalTransform();

    const vec3 sphereCenter = sphere.getCenter(transformSphere);
    const vec3 boxCenter = box.getCenter(transformBox);
    const vec3 boxXAxis = transformBox.getXUnitVector();
    const vec3 boxYAxis = transformBox.getYUnitVector();
    const vec3 boxZAxis = transformBox.getZUnitVector();
    const vec3 boxHalfExtents = box.getActualHalfExtents(transformBox);
    const vec3 closestPoint = GeometryUtilities::computeClosestPointBetweenPointAndBox(
        sphereCenter,
        boxCenter,
        boxXAxis,
        boxYAxis,
        boxZAxis,
        boxHalfExtents
    );

    Contact contact = GeometryUtilities::computeContactBetweenVertexAndBox(
        closestPoint,
        boxCenter,
        boxXAxis,
        boxYAxis,
        boxZAxis,
        boxHalfExtents
    );
    contact.contactNormal = -contact.contactNormal;
    return contact;
}

Contact CollisionUtilities::findContactBetweenCapsuleAndSphere(
    const BoundingCapsuleComponent& capsule,
    const TransformComponent& transformComponentCapsule,
    const BoundingSphereComponent& sphere,
    const TransformComponent& transformComponentSphere
) noexcept {
    Contact contact = CollisionUtilities::findContactBetweenSphereAndCapsule(sphere, transformComponentSphere, capsule, transformComponentCapsule);
    contact.contactNormal = -contact.contactNormal;
    return contact;
}

Contact CollisionUtilities::findContactBetweenCapsuleAndCapsule(
    const BoundingCapsuleComponent& capsule1,
    const TransformComponent& transformComponent1,
    const BoundingCapsuleComponent& capsule2,
    const TransformComponent& transformComponent2
) noexcept {
    const Transform& transform1 = transformComponent1.getGlobalTransform();
    const Transform& transform2 = transformComponent2.getGlobalTransform();

    const Segment segment1 = capsule1.getActualSegment(transform1);
    const float radius1 = capsule1.getActualRadius(transform1);

    const Segment segment2 = capsule2.getActualSegment(transform2);

    vec3 c1, c2;
    segment1.computeClosestPointsBetweenSegment(segment2, c1, c2);
    const vec3 offset = c1 - c2;
    const float dist = glm::length(offset);
    const float radiusSum = radius1 + capsule2.getActualRadius(transform2);

    return {
        c1 + offset * 0.5f,
        offset / dist,
        radiusSum - dist,
        ContactValidity::VALID
    };
}

Contact CollisionUtilities::findContactBetweenCapsuleAndBox(
    const BoundingCapsuleComponent& capsule,
    const TransformComponent& transformComponentCapsule,
    const BoundingBoxComponent& box,
    const TransformComponent& transformComponentBox
) noexcept {
    const Transform& transformCapsule = transformComponentCapsule.getGlobalTransform();
    const Transform& transformBox = transformComponentBox.getGlobalTransform();

    vector<Triangle> triangles = box.getTriangles(transformBox);
    vec3 closestPointSegment, closestPointTriangle;
    const Segment segment = capsule.getActualSegment(transformCapsule);
    const vec3 capsuleCenter = capsule.getCenter(transformCapsule);
    GeometryUtilities::computeClosestPointsBetweenSegmentAndTriangle(
        segment,
        triangles[0],
        closestPointSegment,
        closestPointTriangle
    );
    float dist2 = glm::length(closestPointTriangle - closestPointSegment);
    for (size_t i = 1; i < triangles.size(); i++) {
        vec3 c1, c2;
        GeometryUtilities::computeClosestPointsBetweenSegmentAndTriangle(
            segment,
            triangles[0],
            c1,
            c2
        );
        float currDist2 = glm::length(c2 - c1);
        if (currDist2 < dist2) {
            dist2 = currDist2;
            closestPointTriangle = c2;
        }
    }

    Contact contact = GeometryUtilities::computeContactBetweenVertexAndBox(
        closestPointTriangle,
        box.getCenter(transformBox),
        transformBox.getXUnitVector(),
        transformBox.getYUnitVector(),
        transformBox.getZUnitVector(),
        box.getActualHalfExtents(transformBox)
    );
    contact.contactNormal = -contact.contactNormal;
    return contact;
}

Contact CollisionUtilities::findContactBetweenBoxAndSphere(
    const BoundingBoxComponent& box,
    const TransformComponent& transformComponentBox,
    const BoundingSphereComponent& sphere,
    const TransformComponent& transformComponentSphere
) noexcept {
    Contact contact = CollisionUtilities::findContactBetweenSphereAndBox(sphere, transformComponentSphere, box, transformComponentBox);
    contact.contactNormal = -contact.contactNormal;
    return contact;
}

Contact CollisionUtilities::findContactBetweenBoxAndCapsule(
    const BoundingBoxComponent& box,
    const TransformComponent& transformComponentBox,
    const BoundingCapsuleComponent& capsule,
    const TransformComponent& transformComponentCapsule
) noexcept {
    Contact contact = CollisionUtilities::findContactBetweenCapsuleAndBox(capsule, transformComponentCapsule, box, transformComponentBox);
    contact.contactNormal = -contact.contactNormal;
    return contact;
}

Contact CollisionUtilities::findContactBetweenBoxAndBox(
    const BoundingBoxComponent& box1,
    const TransformComponent& transformComponent1,
    const BoundingBoxComponent& box2,
    const TransformComponent& transformComponent2
) noexcept {
    const Transform& transformBox1 = transformComponent1.getGlobalTransform();
    const Transform& transformBox2 = transformComponent2.getGlobalTransform();

    const vec3 center1 = box1.getCenter(transformBox1);
    const vec3 halfExtents1 = box1.getActualHalfExtents(transformBox1);
    vec3 axis1[3] = {
        transformBox1.getXUnitVector(),
        transformBox1.getYUnitVector(),
        transformBox1.getZUnitVector()
    };

    const vec3 center2 = box2.getCenter(transformBox2);
    const vec3 halfExtents2 = box2.getActualHalfExtents(transformBox2);
    vec3 axis2[3] = {
        transformBox2.getXUnitVector(),
        transformBox2.getYUnitVector(),
        transformBox2.getZUnitVector()
    };

    // Let's compute the contact point
    // Let's do point to face contact
    const vec3 xVector1 = halfExtents1.x * axis1[0];
    const vec3 yVector1 = halfExtents1.y * axis1[1];
    const vec3 zVector1 = halfExtents1.z * axis1[2];
    constexpr size_t NUM_CORNERS = 8;
    const vec3 corners1[NUM_CORNERS] = {
        center1 - xVector1 - yVector1 - zVector1,
        center1 - xVector1 - yVector1 + zVector1,
        center1 - xVector1 + yVector1 - zVector1,
        center1 - xVector1 + yVector1 + zVector1,
        center1 + xVector1 - yVector1 - zVector1,
        center1 + xVector1 - yVector1 + zVector1,
        center1 + xVector1 + yVector1 - zVector1,
        center1 + xVector1 + yVector1 + zVector1
    };

    const vec3 xVector2 = halfExtents2.x * axis2[0];
    const vec3 yVector2 = halfExtents2.y * axis2[1];
    const vec3 zVector2 = halfExtents2.z * axis2[2];
    const vec3 corners2[NUM_CORNERS] = {
        center2 - xVector2 - yVector2 - zVector2,
        center2 - xVector2 - yVector2 + zVector2,
        center2 - xVector2 + yVector2 - zVector2,
        center2 - xVector2 + yVector2 + zVector2,
        center2 + xVector2 - yVector2 - zVector2,
        center2 + xVector2 - yVector2 + zVector2,
        center2 + xVector2 + yVector2 - zVector2,
        center2 + xVector2 + yVector2 + zVector2
    };

    Contact contactVertex = {
        vec3(),
        vec3(),
        0.f,
        ContactValidity::INVALID
    };
    for (size_t i = 0; i < NUM_CORNERS; ++i) {
        const Contact newContactVertex1 = move(GeometryUtilities::computeContactBetweenVertexAndBox(
            corners1[i],
            center2,
            axis2[0],
            axis2[1],
            axis2[2],
            halfExtents2
        ));

        if (contactVertex.validity == ContactValidity::INVALID || contactVertex.penetration < newContactVertex1.penetration) {
            contactVertex = newContactVertex1;
        }

        const Contact newContactVertex2 = move(GeometryUtilities::computeContactBetweenVertexAndBox(
            corners2[i],
            center1,
            axis1[0],
            axis1[1],
            axis1[2],
            halfExtents1
        ));

        if (contactVertex.validity == ContactValidity::INVALID || contactVertex.penetration < newContactVertex2.penetration) {
            contactVertex = newContactVertex2;
            contactVertex.contactNormal = -contactVertex.contactNormal;
        }
    }

    // Let's do edge to edge contact
    constexpr size_t NUM_EDGES = 12;
    const Segment edges1[NUM_EDGES] = {
        Segment(corners1[0], corners1[1]),
        Segment(corners1[0], corners1[2]),
        Segment(corners1[0], corners1[4]),
        Segment(corners1[3], corners1[1]),
        Segment(corners1[3], corners1[2]),
        Segment(corners1[3], corners1[7]),
        Segment(corners1[5], corners1[7]),
        Segment(corners1[5], corners1[4]),
        Segment(corners1[5], corners1[1]),
        Segment(corners1[6], corners1[7]),
        Segment(corners1[6], corners1[4]),
        Segment(corners1[6], corners1[2])
    };

    const Segment edges2[NUM_EDGES] = {
        Segment(corners2[0], corners2[1]),
        Segment(corners2[0], corners2[2]),
        Segment(corners2[0], corners2[4]),
        Segment(corners2[3], corners2[1]),
        Segment(corners2[3], corners2[2]),
        Segment(corners2[3], corners2[7]),
        Segment(corners2[5], corners2[7]),
        Segment(corners2[5], corners2[4]),
        Segment(corners2[5], corners2[1]),
        Segment(corners2[6], corners2[7]),
        Segment(corners2[6], corners2[4]),
        Segment(corners2[6], corners2[2])
    };

    Contact contactEdge = {
        vec3(),
        vec3(),
        0.f,
        ContactValidity::INVALID
    };
    for (size_t i = 0; i < NUM_EDGES; ++i) {
        for (size_t j = 0; j < NUM_EDGES; ++j) {
            vec3 c1, c2;
            edges1[j].computeClosestPointsBetweenSegment(edges2[i], c1, c2);
            vec3 offset1 = c1 - center1;
            vec3 offset2 = c2 - center1;

            if (dot(offset1, offset1) > dot(offset2, offset2)) {
                Contact newContactEdge = move(GeometryUtilities::computeContactBetweenVertexAndBox(
                    c2,
                    center1,
                    axis1[0],
                    axis1[1],
                    axis1[2],
                    halfExtents1
                ));
                if (contactEdge.validity == ContactValidity::INVALID || contactEdge.penetration < newContactEdge.penetration) {
                    contactEdge = newContactEdge;
                }
            }
        }
    }

    // The winner of the 2 methods is the one with the highest penetration
    return contactEdge.validity == ContactValidity::INVALID || contactVertex.penetration >= contactEdge.penetration ? contactVertex : contactEdge;
}

bool CollisionUtilities::areMovingSphereAndSphereIntersecting(
    const BoundingSphereComponent& sphere1,
    const TransformComponent& transformComponent1,
    const PhysicsComponent& physicsComponent1,
    const BoundingSphereComponent& sphere2,
    const TransformComponent& transformComponent2,
    const PhysicsComponent& physicsComponent2,
    const float& startTimePoint,
    const float& finalTimePoint,
    float& intersectionTimePoint
) noexcept {
    const Transform& transform1 = transformComponent1.getGlobalTransform();

    const vec3 velocityRelativeToSphere2 = velocity1 - velocity2;
    const float speed = length(velocityRelativeToSphere2);
    const vec3 velocityUnitVector = velocityRelativeToSphere2 / speed;
    const float delTime = finalTimePoint - startTimePoint;
    float distanceSegment = delTime * speed;
    const float sphereRadius1 = sphere1.getActualRadius(transform1);

    vec3 testingSphereCenter = sphere1.getCenter(transform1) + velocityUnitVector * delTime * 0.5f;
    CollisionSphere testingSphere(distanceSegment * 0.5f + sphereRadius1);
    testingSphere.getTransformComponent().translate(testingSphereCenter);
    testingSphere.update(Transform());
    bool collisionDetected = CollisionUtilities::isSphereIntersectingSphere(testingSphere, testingTransformComponent, sphere2, transformComponent2);

    if (collisionDetected) {
        float maxErrorDistance = 0.1f;
        float timeSegment = delTime * 0.5f;
        distanceSegment = speed * timeSegment;
        float startTime = startTimePoint;
        float endTime = finalTimePoint;
        intersectionTimePoint = 0.f;
        while (distanceSegment > maxErrorDistance) {
            vec3 offset = -velocityUnitVector * distanceSegment * 0.5f;
            testingSphere.getSphereComponent().setRadius(distanceSegment * 0.5f + sphereRadius1);
            testingSphere.getTransformComponent().translate(offset);
            testingSphere.update(Transform());

            if (CollisionUtilities::isSphereIntersectingSphere(testingSphere, testingTransformComponent, sphere2, transformComponent2)) {
                endTime = startTime + timeSegment;
                intersectionTimePoint = startTime + timeSegment * 0.5f;
            }
            else {
                offset = velocityUnitVector * distanceSegment;
                testingSphere.getTransformComponent().translate(offset);
                testingSphere.update(Transform());

                endTime = startTime + timeSegment * 2;
                startTime = startTime + timeSegment;
                intersectionTimePoint = startTime + timeSegment * 0.5f;
            }

            timeSegment *= 0.5f;
            distanceSegment = speed * timeSegment;
        }
    }

    return collisionDetected;
}

bool CollisionUtilities::areMovingCapsuleAndSphereIntersecting(
    const CollisionCapsule& capsule,
    const vec3& velocityCapsule,
    const CollisionSphere& sphere,
    const vec3& velocitySphere,
    const float& startTimePoint,
    const float& finalTimePoint,
    float& intersectionTimePoint
) noexcept {
    const Transform& transformSphere = sphere.getTransformComponent().getGlobalTransform();
    const BoundingSphereComponent& sphereComponent = sphere.getSphereComponent();

    const vec3 velocityRelativeToCapsule = velocitySphere - velocityCapsule;
    const float speed = length(velocityRelativeToCapsule);
    const vec3 velocityUnitVector = velocityRelativeToCapsule / speed;
    const float delTime = finalTimePoint - startTimePoint;
    float distanceSegment = delTime * speed;
    const float sphereRadius = sphereComponent.getActualRadius(transformSphere);

    vec3 testingSphereCenter = sphereComponent.getCenter(transformSphere) + velocityUnitVector * delTime * 0.5f;
    CollisionSphere testingSphere(distanceSegment * 0.5f + sphereRadius);
    testingSphere.getTransformComponent().translate(testingSphereCenter);
    testingSphere.update(Transform());
    bool collisionDetected = CollisionUtilities::isCapsuleIntersectingSphere(capsule, testingSphere);

    if (collisionDetected) {
        float maxErrorDistance = 0.1f;
        float timeSegment = delTime * 0.5f;
        distanceSegment = speed * timeSegment;
        float startTime = startTimePoint;
        float endTime = finalTimePoint;
        intersectionTimePoint = 0.f;
        while (distanceSegment > maxErrorDistance) {
            vec3 offset = -velocityUnitVector * distanceSegment * 0.5f;
            testingSphere.getSphereComponent().setRadius(distanceSegment * 0.5f + sphereRadius);
            testingSphere.getTransformComponent().translate(offset);
            testingSphere.update(Transform());

            if (CollisionUtilities::isCapsuleIntersectingSphere(capsule, testingSphere)) {
                endTime = startTime + timeSegment;
                intersectionTimePoint = startTime + timeSegment * 0.5f;
            }
            else {
                offset = velocityUnitVector * distanceSegment;
                testingSphere.getTransformComponent().translate(offset);
                testingSphere.update(Transform());

                endTime = startTime + timeSegment * 2;
                startTime = startTime + timeSegment;
                intersectionTimePoint = startTime + timeSegment * 0.5f;
            }

            timeSegment *= 0.5f;
            distanceSegment = speed * timeSegment;
        }
    }

    return collisionDetected;
}

bool CollisionUtilities::areMovingCapsuleAndCapsuleIntersecting(
    const CollisionCapsule& capsule1,
    const vec3& velocity1,
    const CollisionCapsule& capsule2,
    const vec3& velocity2,
    const float& startTimePoint,
    const float& finalTimePoint,
    float& intersectionTimePoint
) noexcept {
    // Check if the volumes are already intersecting
    if (CollisionUtilities::isCapsuleIntersectingCapsule(capsule1, capsule2)) {
        intersectionTimePoint = 0.f;
        return true;
    }

    const Transform& transform1 = capsule1.getTransformComponent().getGlobalTransform();
    const BoundingCapsuleComponent& capsuleComponent1 = capsule1.getCapsuleComponent();
    const Transform& transform2 = capsule2.getTransformComponent().getGlobalTransform();
    const BoundingCapsuleComponent& capsuleComponent2 = capsule2.getCapsuleComponent();

    const vec3 velocityRelativeToCapsule2 = velocity1 - velocity2;
    const float speed = length(velocityRelativeToCapsule2);
    const vec3 velocityUnitVector = velocityRelativeToCapsule2 / speed;

    // the velocity unit vector will act as our x unit vector for the test obb
    // this will be the axis in which we will shrink the test obb
    // The half extents for the y and z axis will stay constant throughout the test
    const vec3 xAxis = transform1.getXUnitVector();
    const vec3 yAxis = transform1.getYUnitVector();
    const vec3 zAxis = transform1.getZUnitVector();
    bool isYAxisParallelToVelocity = 1. - dot(yAxis, velocityUnitVector) <= GeometryConstants::EPSILON;
    const vec3 testXAxis = isYAxisParallelToVelocity ? cross(zAxis, velocityUnitVector) : cross(yAxis, velocityUnitVector);
    const vec3 testZAxis = cross(testXAxis, velocityUnitVector);


    // calculate the y and z half extents
    const float capsuleRadius1 = capsuleComponent1.getActualRadius(transform1);
    const float capsuleCylinderLength1 = capsuleComponent1.getActualCapsuleCylinderLength(transform1);
    const vec3 halfExtents1 = vec3(capsuleRadius1, capsuleCylinderLength1 * 0.5f + capsuleRadius1, capsuleRadius1);
    const vec3 transformedX1 = xAxis * halfExtents1.x;
    const vec3 transformedY1 = yAxis * halfExtents1.y;
    const vec3 transformedZ1 = zAxis * halfExtents1.z;
    constexpr size_t NUM_CORNERS = 8;
    const vec3 corners[NUM_CORNERS] = {
        -transformedX1 - transformedY1 - transformedZ1,
        -transformedX1 - transformedY1 + transformedZ1,
        -transformedX1 + transformedY1 - transformedZ1,
        -transformedX1 + transformedY1 + transformedZ1,
        transformedX1 - transformedY1 - transformedZ1,
        transformedX1 - transformedY1 + transformedZ1,
        transformedX1 + transformedY1 - transformedZ1,
        transformedX1 + transformedY1 + transformedZ1
    };

    float xHalfExtent = glm::abs(dot(corners[0], testXAxis));
    float yHalfExtent = glm::abs(dot(corners[0], velocityUnitVector));
    float zHalfExtent = glm::abs(dot(corners[0], testZAxis));
    for (size_t i = 1; i < NUM_CORNERS; i++) {
        const float currentXHalfExtent = glm::abs(dot(corners[i], testXAxis));
        const float currentYHalfExtent = glm::abs(dot(corners[i], velocityUnitVector));
        const float currentZHalfExtent = glm::abs(dot(corners[i], testZAxis));

        if (currentXHalfExtent > xHalfExtent) {
            xHalfExtent = currentXHalfExtent;
        }
        if (currentYHalfExtent > currentZHalfExtent) {
            yHalfExtent = currentYHalfExtent;
        }
        if (currentZHalfExtent > zHalfExtent) {
            zHalfExtent = currentZHalfExtent;
        }
    }

    float radius = sqrt(xHalfExtent * xHalfExtent + zHalfExtent * zHalfExtent);
    float capsuleLength = yHalfExtent * 2.f;

    const float delTime = finalTimePoint - startTimePoint;
    float distanceSegment = delTime * speed;
    const vec3 testingCapsuleCenter = capsuleComponent1.getCenter(transform1) + velocityUnitVector * distanceSegment * 0.5f;
    CollisionCapsule testingCapsule(radius, capsuleLength + distanceSegment);
    testingCapsule.getTransformComponent().generalRotate(glm::degrees(glm::acos(dot(velocityUnitVector, yAxis))), testXAxis);
    testingCapsule.getTransformComponent().translate(testingCapsuleCenter);
    testingCapsule.update(Transform());


    bool collisionDetected = CollisionUtilities::isCapsuleIntersectingCapsule(capsule2, testingCapsule);

    if (collisionDetected) {
        float maxErrorDistance = 0.1f;
        float timeSegment = delTime * 0.5f;
        distanceSegment = speed * timeSegment;
        float startTime = startTimePoint;
        float endTime = finalTimePoint;
        intersectionTimePoint = 0.f;
        while (distanceSegment > maxErrorDistance) {
            vec3 offset = -velocityUnitVector * distanceSegment * 0.5f;
            testingCapsule.getCapsuleComponent().setCapsuleCylinderLength(distanceSegment * 0.5f + capsuleLength);
            testingCapsule.getTransformComponent().translate(offset);
            testingCapsule.update(Transform());

            if (CollisionUtilities::isCapsuleIntersectingCapsule(capsule2, testingCapsule)) {
                endTime = startTime + timeSegment;
                intersectionTimePoint = startTime + timeSegment * 0.5f;
            }
            else {
                offset = velocityUnitVector * distanceSegment;
                testingCapsule.getTransformComponent().translate(offset);
                testingCapsule.update(Transform());

                endTime = startTime + timeSegment * 2;
                startTime = startTime + timeSegment;
                intersectionTimePoint = startTime + timeSegment * 0.5f;
            }

            timeSegment *= 0.5f;
            distanceSegment = speed * timeSegment;
        }
    }

    return collisionDetected;
}

bool CollisionUtilities::areMovingBoxAndSphereIntersecting(
    const CollisionBox& box,
    const vec3& velocityBox,
    const CollisionSphere& sphere,
    const vec3& velocitySphere,
    const float& startTimePoint,
    const float& finalTimePoint,
    float& intersectionTimePoint
) noexcept {
    const Transform& transformSphere = sphere.getTransformComponent().getGlobalTransform();
    const BoundingSphereComponent& sphereComponent = sphere.getSphereComponent();

    const vec3 velocityRelativeToBox = velocitySphere - velocityBox;
    const float speed = length(velocityRelativeToBox);
    const vec3 velocityUnitVector = velocityRelativeToBox / speed;
    const float delTime = finalTimePoint - startTimePoint;
    float distanceSegment = delTime * speed;
    const float sphereRadius = sphereComponent.getActualRadius(transformSphere);

    vec3 testingSphereCenter = sphereComponent.getCenter(transformSphere) + velocityUnitVector * delTime * 0.5f;
    CollisionSphere testingSphere(distanceSegment * 0.5f + sphereRadius);
    testingSphere.getTransformComponent().translate(testingSphereCenter);
    testingSphere.update(Transform());
    bool collisionDetected = CollisionUtilities::isBoxIntersectingSphere(box, testingSphere);

    if (collisionDetected) {
        float maxErrorDistance = 0.1f;
        float timeSegment = delTime * 0.5f;
        distanceSegment = speed * timeSegment;
        float startTime = startTimePoint;
        float endTime = finalTimePoint;
        intersectionTimePoint = 0.f;
        while (distanceSegment > maxErrorDistance) {
            vec3 offset = -velocityUnitVector * distanceSegment * 0.5f;
            testingSphere.getSphereComponent().setRadius(distanceSegment * 0.5f + sphereRadius);
            testingSphere.getTransformComponent().translate(offset);
            testingSphere.update(Transform());

            if (CollisionUtilities::isBoxIntersectingSphere(box, testingSphere)) {
                endTime = startTime + timeSegment;
                intersectionTimePoint = startTime + timeSegment * 0.5f;
            }
            else {
                offset = velocityUnitVector * distanceSegment;
                testingSphere.getTransformComponent().translate(offset);
                testingSphere.update(Transform());

                endTime = startTime + timeSegment * 2;
                startTime = startTime + timeSegment;
                intersectionTimePoint = startTime + timeSegment * 0.5f;
            }

            timeSegment *= 0.5f;
            distanceSegment = speed * timeSegment;
        }
    }

    return collisionDetected;
}

bool CollisionUtilities::areMovingBoxAndCapsuleIntersecting(
    const CollisionBox& box,
    const vec3& velocityBox,
    const CollisionCapsule& capsule,
    const vec3& velocityCapsule,
    const float& startTimePoint,
    const float& finalTimePoint,
    float& intersectionTimePoint
) noexcept {
    // Check if the volumes are already intersecting
    if (CollisionUtilities::isBoxIntersectingCapsule(box, capsule)) {
        intersectionTimePoint = 0.f;
        return true;
    }

    const Transform& transformBox1 = box.getTransformComponent().getGlobalTransform();
    const BoundingBoxComponent& boxComponent = box.getBoxComponent();

    const vec3 velocityRelativeToCapsule = velocityBox - velocityCapsule;
    const float speed = length(velocityRelativeToCapsule);
    const vec3 velocityUnitVector = velocityRelativeToCapsule / speed;

    // the velocity unit vector will act as our x unit vector for the test obb
    // this will be the axis in which we will shrink the test obb
    // The half extents for the y and z axis will stay constant throughout the test
    const vec3 xAxis1 = transformBox1.getXUnitVector();
    const vec3 yAxis1 = transformBox1.getYUnitVector();
    const vec3 zAxis1 = transformBox1.getZUnitVector();
    bool isXAxisParallelToVelocity = 1. - dot(xAxis1, velocityUnitVector) <= GeometryConstants::EPSILON;
    const vec3 testYAxis = isXAxisParallelToVelocity ? cross(zAxis1, velocityUnitVector) : cross(xAxis1, velocityUnitVector);
    const vec3 testZAxis = cross(testYAxis, velocityUnitVector);


    // calculate the y and z half extents
    const vec3 halfExtents = boxComponent.getActualHalfExtents(transformBox1);
    const vec3 transformedX = xAxis1 * halfExtents.x;
    const vec3 transformedY = yAxis1 * halfExtents.y;
    const vec3 transformedZ = zAxis1 * halfExtents.z;
    constexpr size_t NUM_CORNERS = 8;
    const vec3 corners[NUM_CORNERS] = {
        -transformedX - transformedY - transformedZ,
        -transformedX - transformedY + transformedZ,
        -transformedX + transformedY - transformedZ,
        -transformedX + transformedY + transformedZ,
        transformedX - transformedY - transformedZ,
        transformedX - transformedY + transformedZ,
        transformedX + transformedY - transformedZ,
        transformedX + transformedY + transformedZ
    };

    float xHalfExtent = glm::abs(dot(corners[0], velocityUnitVector));
    float yHalfExtent = glm::abs(dot(corners[0], testYAxis));
    float zHalfExtent = glm::abs(dot(corners[0], testZAxis));
    for (size_t i = 1; i < NUM_CORNERS; i++) {
        const float currentXHalfExtent = glm::abs(dot(corners[i], velocityUnitVector));
        const float currentYHalfExtent = glm::abs(dot(corners[i], testYAxis));
        const float currentZHalfExtent = glm::abs(dot(corners[i], testZAxis));

        if (currentXHalfExtent > xHalfExtent) {
            xHalfExtent = currentXHalfExtent;
        }
        if (currentYHalfExtent > yHalfExtent) {
            yHalfExtent = currentYHalfExtent;
        }
        if (currentZHalfExtent > zHalfExtent) {
            zHalfExtent = currentZHalfExtent;
        }
    }

    const float delTime = finalTimePoint - startTimePoint;
    float distanceSegment = delTime * speed;
    const vec3 testingBoxCenter = boxComponent.getCenter(transformBox1) + velocityUnitVector * distanceSegment * 0.5f;
    CollisionBox testingBox(vec3(distanceSegment * 0.5f + xHalfExtent, yHalfExtent, zHalfExtent));
    testingBox.getTransformComponent().generalRotate(glm::degrees(glm::acos(dot(velocityUnitVector, xAxis1))), testYAxis);
    testingBox.getTransformComponent().translate(testingBoxCenter);
    testingBox.update(Transform());


    bool collisionDetected = CollisionUtilities::isBoxIntersectingCapsule(testingBox, capsule);

    if (collisionDetected) {
        float maxErrorDistance = 0.1f;
        float timeSegment = delTime * 0.5f;
        distanceSegment = speed * timeSegment;
        float startTime = startTimePoint;
        float endTime = finalTimePoint;
        intersectionTimePoint = 0.f;
        while (distanceSegment > maxErrorDistance) {
            vec3 offset = -velocityUnitVector * distanceSegment * 0.5f;
            testingBox.getBoxComponent().setHalfExtents(vec3(distanceSegment * 0.5f + xHalfExtent, yHalfExtent, zHalfExtent));
            testingBox.getTransformComponent().translate(offset);
            testingBox.update(Transform());

            if (CollisionUtilities::isBoxIntersectingCapsule(testingBox, capsule)) {
                endTime = startTime + timeSegment;
                intersectionTimePoint = startTime + timeSegment * 0.5f;
            }
            else {
                offset = velocityUnitVector * distanceSegment;
                testingBox.getTransformComponent().translate(offset);
                testingBox.update(Transform());

                endTime = startTime + timeSegment * 2;
                startTime = startTime + timeSegment;
                intersectionTimePoint = startTime + timeSegment * 0.5f;
            }

            timeSegment *= 0.5f;
            distanceSegment = speed * timeSegment;
        }
    }

    return collisionDetected;
}

bool CollisionUtilities::areMovingBoxAndBoxIntersecting(
    const CollisionBox& box1,
    const vec3& velocity1,
    const CollisionBox& box2,
    const vec3& velocity2,
    const float& startTimePoint,
    const float& finalTimePoint,
    float& intersectionTimePoint
) noexcept {
    // Check if the volumes are already intersecting
    if (CollisionUtilities::isBoxIntersectingBox(box1, box2)) {
        intersectionTimePoint = 0.f;
        return true;
    }

    const Transform& transformBox1 = box1.getTransformComponent().getGlobalTransform();
    const BoundingBoxComponent& boxComponent1 = box1.getBoxComponent();

    const vec3 velocityRelativeToOBB2 = velocity1 - velocity2;
    const float speed = length(velocityRelativeToOBB2);
    const vec3 velocityUnitVector = velocityRelativeToOBB2 / speed;

    // the velocity unit vector will act as our x unit vector for the test obb
    // this will be the axis in which we will shrink the test obb
    // The half extents for the y and z axis will stay constant throughout the test
    const vec3 xAxis1 = transformBox1.getXUnitVector();
    const vec3 yAxis1 = transformBox1.getYUnitVector();
    const vec3 zAxis1 = transformBox1.getZUnitVector();
    bool isXAxisParallelToVelocity = 1. - dot(xAxis1, velocityUnitVector) <= GeometryConstants::EPSILON;
    const vec3 testYAxis = isXAxisParallelToVelocity ? cross(zAxis1, velocityUnitVector) : cross(xAxis1, velocityUnitVector);
    const vec3 testZAxis = cross(testYAxis, velocityUnitVector);


    // calculate the y and z half extents
    const vec3 halfExtents1 = boxComponent1.getActualHalfExtents(transformBox1);
    const vec3 transformedX1 = xAxis1 * halfExtents1.x;
    const vec3 transformedY1 = yAxis1 * halfExtents1.y;
    const vec3 transformedZ1 = zAxis1 * halfExtents1.z;
    constexpr size_t NUM_CORNERS = 8;
    const vec3 corners[NUM_CORNERS] = {
        -transformedX1 - transformedY1 - transformedZ1,
        -transformedX1 - transformedY1 + transformedZ1,
        -transformedX1 + transformedY1 - transformedZ1,
        -transformedX1 + transformedY1 + transformedZ1,
        transformedX1 - transformedY1 - transformedZ1,
        transformedX1 - transformedY1 + transformedZ1,
        transformedX1 + transformedY1 - transformedZ1,
        transformedX1 + transformedY1 + transformedZ1
    };

    float xHalfExtent = glm::abs(dot(corners[0], velocityUnitVector));
    float yHalfExtent = glm::abs(dot(corners[0], testYAxis));
    float zHalfExtent = glm::abs(dot(corners[0], testZAxis));
    for (size_t i = 1; i < NUM_CORNERS; i++) {
        const float currentXHalfExtent = glm::abs(dot(corners[i], velocityUnitVector));
        const float currentYHalfExtent = glm::abs(dot(corners[i], testYAxis));
        const float currentZHalfExtent = glm::abs(dot(corners[i], testZAxis));

        if (currentXHalfExtent > xHalfExtent) {
            xHalfExtent = currentXHalfExtent;
        }
        if (currentYHalfExtent > yHalfExtent) {
            yHalfExtent = currentYHalfExtent;
        }
        if (currentZHalfExtent > zHalfExtent) {
            zHalfExtent = currentZHalfExtent;
        }
    }

    const float delTime = finalTimePoint - startTimePoint;
    float distanceSegment = delTime * speed;
    const vec3 testingBoxCenter = boxComponent1.getCenter(transformBox1) + velocityUnitVector * distanceSegment * 0.5f;
    CollisionBox testingBox(vec3(distanceSegment * 0.5f + xHalfExtent, yHalfExtent, zHalfExtent));
    testingBox.getTransformComponent().generalRotate(glm::degrees(glm::acos(dot(velocityUnitVector, xAxis1))), testYAxis);
    testingBox.getTransformComponent().translate(testingBoxCenter);
    testingBox.update(Transform());


    bool collisionDetected = CollisionUtilities::isBoxIntersectingBox(box2, testingBox);

    if (collisionDetected) {
        float maxErrorDistance = 0.1f;
        float timeSegment = delTime * 0.5f;
        distanceSegment = speed * timeSegment;
        float startTime = startTimePoint;
        float endTime = finalTimePoint;
        intersectionTimePoint = 0.f;
        while (distanceSegment > maxErrorDistance) {
            vec3 offset = -velocityUnitVector * distanceSegment * 0.5f;
            testingBox.getBoxComponent().setHalfExtents(vec3(distanceSegment * 0.5f + xHalfExtent, yHalfExtent, zHalfExtent));
            testingBox.getTransformComponent().translate(offset);
            testingBox.update(Transform());

            if (CollisionUtilities::isBoxIntersectingBox(box2, testingBox)) {
                endTime = startTime + timeSegment;
                intersectionTimePoint = startTime + timeSegment * 0.5f;
            }
            else {
                offset = velocityUnitVector * distanceSegment;
                testingBox.getTransformComponent().translate(offset);
                testingBox.update(Transform());

                endTime = startTime + timeSegment * 2;
                startTime = startTime + timeSegment;
                intersectionTimePoint = startTime + timeSegment * 0.5f;
            }

            timeSegment *= 0.5f;
            distanceSegment = speed * timeSegment;
        }
    }

    return collisionDetected;
}*/