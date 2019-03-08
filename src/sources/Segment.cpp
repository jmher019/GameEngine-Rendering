#include <Segment.hpp>

using namespace puggo;

Segment::Segment(const vec3& start, const vec3& end) noexcept:
    start(start),
    end(end) {
}

Segment::Segment(const Segment& segment) noexcept:
    start(segment.start),
    end(segment.end) {
}

Segment::Segment(Segment&& segment) noexcept:
    start(move(segment.start)),
    end(move(segment.end)) {
}

Segment& Segment::operator=(const Segment& segment) noexcept {
    start = segment.start;
    end = segment.end;

    return *this;
}

Segment& Segment::operator=(Segment&& segment) noexcept {
    start = move(segment.start);
    end = move(segment.end);

    return *this;
}

const vec3& Segment::getStart(void) const noexcept {
    return start;
}

void Segment::setStart(const vec3& start) noexcept {
    this->start = start;
}

const vec3& Segment::getEnd(void) const noexcept {
    return end;
}

void Segment::setEnd(const vec3& end) noexcept {
    this->end = end;
}

vec3 Segment::computeClosestPointOnSegment(const vec3& target) const noexcept {
    const vec3 ab = end - start;
    // Project p onto ab, but deferring divide by Dot(ab, ab)
    const float t = dot(target - start, ab);
    if (t <= 0.0f) {
        // p projects outside the [start, end] interval, on the start side; clamp to start
        return vec3(start);
    }

    const float denom = dot(ab, ab); // Always nonnegative since denom = ||ab||^2
    if (t >= denom) {
        // p projects outside the [start, end] interval, on the end side; clamp to end
        return vec3(end);
    }

    return start + ab * t / denom;
}

void Segment::computeClosestPointsBetweenSegment(
    const Segment& targetSegment,
    vec3& pointOnSegment,
    vec3& pointOnTargetSegment
) const noexcept {
    const vec3 d1 = end - start;
    const vec3 d2 = targetSegment.end - targetSegment.start;
    const vec3 r = start - targetSegment.start;
    const float b = dot(d1, d1);
    const float e = dot(d2, d2);
    const float f = dot(d2, r);
    float s = 0.f, t = 0.f;

    // Check if either or both segments degenerate into points
    if (b <= GeometryConstants::EPSILON && e <= GeometryConstants::EPSILON) {
        // Both segments degenerate into points
        pointOnSegment = start;
        pointOnTargetSegment = targetSegment.start;
        return;
    }

    if (b <= GeometryConstants::EPSILON) {
        // First segment degenerates into a point
        t = clamp(f / e, 0.f, 1.f);
    }
    else {
        const float c = dot(d1, r);
        if (e <= GeometryConstants::EPSILON) {
            // second segment degenerates to a point
            s = clamp(-c / b, 0.f, 1.f);
        }
        else {
            // The general nondegenerate case starts here
            const float d = dot(d1, d2);
            const float denom = b * e - d * d;

            // If segments not parallel, compute closest point on L1 to L2 and
            // clamp to segment s1. Else pick arbitrary s (here 0)
            if (denom != 0.f) {
                s = clamp((d * f - c * e) / denom, 0.f, 1.f);
            }
            else {
                s = 0.f;
            }

            t = (d * s + f) / e;

            // If t in [0, 1] done. Else clamp t, recompute s for the new value of t
            if (t < 0.f) {
                t = 0.f;
                s = clamp(-c / b, 0.f, 1.f);
            }
            else if (t > 1.f) {
                t = 1.f;
                s = clamp((d - c) / b, 0.f, 1.f);
            }
        }
    }

    pointOnSegment = start + d1 * s;
    pointOnTargetSegment = targetSegment.start + d2 * t;
}