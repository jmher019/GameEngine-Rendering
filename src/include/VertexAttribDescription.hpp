#ifndef PUGGO_VERTEX_ATTRIB_DESCRIPTION_HPP
#define PUGGO_VERTEX_ATTRIB_DESCRIPTION_HPP

#include <glad/glad.h>

namespace puggo {
    struct VertexAttribDescription {
        GLuint index;
        GLint size;
        GLenum type;
        GLboolean normalized;
        GLsizei stride;
        void* offset;
    };
}

#endif // !PUGGO_VERTEX_ATTRIB_DESCRIPTION_HPP
