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
    // Primer passarem el material
    // 1. Declerem un struct amb la informacio del material

    struct {
        GLuint ambient;
        GLuint diffuse;
        GLuint specular;
        GLuint transparency;
        GLuint shininess;
    } gl_IdMaterial;

    // 2. Obtenim identificadors GPU
    gl_IdMaterial.ambient = program->uniformLocation("material.ambient");
    gl_IdMaterial.diffuse = program->uniformLocation("material.diffuse");
    gl_IdMaterial.specular = program->uniformLocation("material.specular");
    gl_IdMaterial.transparency = program->uniformLocation("material.transparency");
    gl_IdMaterial.shininess = program->uniformLocation("material.shininess");

    // 3. Bind de les zones de memòria de GPU a CPU
    glUniform3fv(gl_IdMaterial.ambient, 1, getAmbient());
    glUniform3fv(gl_IdMaterial.diffuse, 1, getDiffuse());
    glUniform3fv(gl_IdMaterial.specular, 1, getSpecular());
    glUniform3fv(gl_IdMaterial.transparency, 1, getTransparency());
    glUniform1f(gl_IdMaterial.shininess, getShininess());
}

