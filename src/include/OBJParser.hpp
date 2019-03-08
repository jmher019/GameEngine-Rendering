#ifndef PUGGO_OBJ_PARSING_HPP
#define PUGGO_OBJ_PARSING_HPP

#include <fstream>

#include <StringUtils.hpp>
#include <Vertex.hpp>

using namespace std;

namespace puggo {
    namespace OBJ {
        vector<Vertex> parse(const char* fileName);
    }
}

#endif // !PUGGO_OBJ_PARSING_HPP
