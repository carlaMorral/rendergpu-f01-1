#include "Geometry/Material.h"


Material::Material(): diffuse(1.0f) {

}

Material::~Material() {

}

Material::Material(vec3 a, vec3 d, vec3 s, vec3 k, float beta) {
    this->ambient = a;
    this->diffuse = d;
    this->specular = s;
    this->shineness = beta;
    this->k = k;
    // k es transparencia
}

/**
 * Passa el material de CPU a GPU
 * @brief Material::toGPU
 * @param program
 */
void Material::toGPU(shared_ptr<QGLShaderProgram> program){
}

