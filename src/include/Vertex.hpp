#ifndef PUGGO_VERTEX_HPP
#define PUGGO_VERTEX_HPP

#include <vector>

#include <glm\glm.hpp>

#include <VertexAttribDescription.hpp>

using namespace glm;
using namespace std;

namespace puggo {
    struct Vertex {
        vec3 position;
        vec3 normal;
        vec3 color;
        vec2 texCoord;

        static const vector<VertexAttribDescription> attribDescriptions;
    };
}

#endif // !PUGGO_VERTEX_HPP
