#include "PointLight.h"

PointLight::PointLight(vec3 ambient, vec3 diffuse, vec3 specular, vec4 position, vec3 coeficients) : Light(LightType::Puntual, ambient, diffuse, specular)
{
    this->position = position;
}

/**
 * @brief Light::getLightPosition
 */
vec4 PointLight::getLightPosition() {
    // TO DO: A canviar a la fase 1 de la practica 2
    return position;
}

/**
 * @brief Light::setLightPosition
 * @param v
 */
void PointLight::setLightPosition(vec4 v) {
    this->position = v;
}

/**
 * @brief Light::getCoeficients
 * @return
 */
vec3 PointLight::getCoeficients() const
{
    return coeficients;
}

/**
 * @brief Light::setCoeficients
 * @param value
 */
void PointLight::setCoeficients(const vec3 &value)
{
    // TODO els coeficients son directament el que passarem?
    coeficients = value;
}
