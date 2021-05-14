#include "PointLight.h"

PointLight::PointLight(vec3 ambient, vec3 diffuse, vec3 specular, vec4 position, vec3 coeficients) : Light(LightType::Puntual, ambient, diffuse, specular)
{
    this->position = position;
    this->coefficients = coeficients;
}

/**
 * @brief Light::getLightPosition
 */
vec4 PointLight::getLightPosition() {
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
vec3 PointLight::getCoefficients() const
{
    return coefficients;
}

/**
 * @brief Light::setCoeficients
 * @param value
 */
void PointLight::setCoefficients(const vec3 &value)
{
    // TODO els coeficients son directament el que passarem?
    coefficients = value;
}
