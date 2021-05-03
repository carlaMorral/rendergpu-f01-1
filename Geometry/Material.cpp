#include "Geometry/Material.h"


Material::Material(): diffuse(1.0f) {

}

Material::~Material() {

}

Material::Material(vec3 a, vec3 d, vec3 s, vec3 k, float beta) {
    this->ambient = a;
    this->diffuse = d;
    this->specular = s;
    this->shininess = beta;
    this->transparency = k;
}

vec3 Material::getAmbient() const {
    return this->ambient;
}

vec3 Material::getDiffuse() const {
    return this->diffuse;
}

vec3 Material::getSpecular() const {
    return this->specular;
}

float Material::getShininess() const {
    return this->shininess;
}

vec3 Material::getTransparency() const {
    return this->transparency;
}

/**
 * Passa el material de CPU a GPU
 * @brief Material::toGPU
 * @param program
 */
void Material::toGPU(shared_ptr<QGLShaderProgram> program){
}

