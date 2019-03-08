#include <Vertex.hpp>

using namespace puggo;

const vector<VertexAttribDescription> Vertex::attribDescriptions = {
    { 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0 },
    { 1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal) },
    { 2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color) },
    { 3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord) }
};