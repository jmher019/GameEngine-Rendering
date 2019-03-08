#ifndef PUGGO_SEGMENT_HPP
#define PUGGO_SEGMENT_HPP

#include <glm/glm.hpp>

#include <GeometryConstants.hpp>

using namespace glm;
using namespace std;

namespace puggo {
    class Segment {
    public:
        Segment(const vec3& start, const vec3& end) noexcept;
        Segment(const Segment& segment) noexcept;
        Segment(Segment&& segment) noexcept;

        Segment& operator=(const Segment& segment) noexcept;
        Segment& operator=(Segment&& segment) noexcept;

        const vec3& getStart(void) const noexcept;
        void setStart(const vec3& start) noexcept;
        const vec3& getEnd(void) const noexcept;
        void setEnd(const vec3& end) noexcept;
        vec3 computeClosestPointOnSegment(const vec3& target) const noexcept;
        void computeClosestPointsBetweenSegment(
            const Segment& targetSegment,
            vec3& pointOnSegment,
            vec3& pointOnTargetSegment
        ) const noexcept;

    private:
        vec3 start;
        vec3 end;
    };
}

#endif // !PUGGO_SEGMENT_HPP
