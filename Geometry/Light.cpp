#include "Geometry/Light.h"

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
