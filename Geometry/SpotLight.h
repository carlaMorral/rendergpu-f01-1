#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H


#include <library/vec.h>

#include "Light.h"

using namespace Common;


class SpotLight : public Light
{
public:
    SpotLight(vec3 ambient, vec3 diffuse, vec3 specular, vec3 direction, float angle, float sharpness);

    vec3 getLightDirection();
    void setLightDirection(vec3 d);

    float getAngle();
    void setAngle(float a);
    float getSharpness();

protected:
    vec3 direction;
    float sharpness;
    float angleObertura;
};

#endif // SPOTLIGHT_H
