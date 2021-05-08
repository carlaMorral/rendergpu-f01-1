#include "Geometry/Light.h"

Light::Light(LightType t) {
    this->type = t;
}

/**
 * @brief Light::Light
 * @param t
 */
Light::Light(LightType t, vec3 Ia, vec3 Id, vec3 Is) {
    this->type = t;
    this->ambient = Ia;
    this->diffuse = Id;
    this->specular = Is;
}

/**
 * @brief Light::getDiffuseIntensity
 * @return
 */
vec3 Light::getId() {
    // TO DO: A canviar a la fase 1 de la practica 2
   return this->diffuse;
}

/**
 * @brief Light::setId
 * @param i
 */
void Light::setId(vec3 i) {
    this->diffuse = i;

}


/**
 * @brief Light::getIa
 * @return
 */
vec3 Light::getIa() const
{
    return this->ambient;
}

/**
 * @brief Light::setIa
 * @param value
 */
void Light::setIa(const vec3 &value)
{
    this->ambient = value;

}

/**
 * @brief Light::getIs
 * @return
 */
vec3 Light::getIs() const
{
    return this->specular;
}

/**
 * @brief Light::setIs
 * @param value
 */
void Light::setIs(const vec3 &value)
{
    this->specular = value;
}


/**
 * @brief Light::getTipusLight
 *
 */
LightType Light::getTipusLight() const
{
    return this->type;
}

/**
 * @brief Light::setTipusLight
 * @param value
 */
void Light::setTipusLight(const LightType &value)
{
    this->type = value;
}

/**
 * @brief Light::getLightPosition
 */
vec4 Light::getLightPosition() {
    // TO DO: A canviar a la fase 1 de la practica 2
    return position;
}

/**
 * @brief Light::setLightPosition
 * @param v
 */
void Light::setLightPosition(vec4 v) {
    this->position = v;
}

/**
 * @brief Light::getCoefficients
 */
vec3 Light::getCoefficients() {
    return this->coefficients;
}

/**
 * @brief Light::setCoefficients
 * @param v
 */
void Light::setCoefficients(vec3 v) {
    this->coefficients = v;
}
