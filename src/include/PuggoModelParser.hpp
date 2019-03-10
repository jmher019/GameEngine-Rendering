#ifndef PUGGO_PUGGO_MODEL_PARSER_HPP
#define PUGGO_PUGGO_MODEL_PARSER_HPP

#include <vector>
#include <fstream>

#include <Vertex.hpp>

using namespace std;

namespace puggo {
    namespace PUGGOModel {
        vector<Vertex> parse(const char* fileName);
    }
}

#endif // !PUGGO_PUGGO_MODEL_PARSER_HPP
