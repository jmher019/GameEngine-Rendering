#include <GPUShaderInterface.hpp>

using namespace puggo;

void GPUShaderInterface::useShader(const GLuint& shader) {
    glUseProgram(shader);
}

void GPUShaderInterface::setUIntUniform(const GLuint& shader, const char* name, const GLuint& value) {
    glUniform1ui(glGetUniformLocation(shader, name), value);
}

void GPUShaderInterface::setFloat(const GLuint& shader, const char* name, const GLfloat& value) {
    glUniform1f(glGetUniformLocation(shader, name), value);
}

void GPUShaderInterface::setVec3(const GLuint& shader, const char* name, const GLfloat* vec) {
    glUniform3fv(glGetUniformLocation(shader, name), 1, vec);
}

void GPUShaderInterface::setVec4(const GLuint& shader, const char* name, const GLfloat* vec) {
    glUniform4fv(glGetUniformLocation(shader, name), 1, vec);
}

void GPUShaderInterface::setMat4(const GLuint& shader, const char* name, const GLfloat* mat) {
    glUniformMatrix4fv(glGetUniformLocation(shader, name), 1, false, mat);
}