#ifndef PUGGO_STRING_UTILS_HPP
#define PUGGO_STRING_UTILS_HPP

#include <vector>
#include <string>

using namespace std;

namespace puggo {
    namespace StringUtils {
        vector<string> split(const string& str, const char& delim) noexcept;
    }
}

#endif // !PUGGO_STRING_UTILS_HPP
