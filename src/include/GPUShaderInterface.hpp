#ifndef PUGGO_GPU_SHADER_INTERFACE_HPP
#define PUGGO_GPU_SHADER_INTERFACE_HPP

#include <glad/glad.h>

namespace puggo {
    class GPUShaderInterface {
    public:
        static void useShader(const GLuint& shader);
        static void setUIntUniform(const GLuint& shader, const char* name, const GLuint& value);
        static void setFloat(const GLuint& shader, const char* name, const GLfloat& value);
        static void setVec3(const GLuint& shader, const char* name, const GLfloat* vec);
        static void setVec4(const GLuint& shader, const char* name, const GLfloat* vec);
        static void setMat4(const GLuint& shader, const char* name, const GLfloat* mat);
    };
}

#endif // !PUGGO_GPU_SHADER_INTERFACE_HPP
