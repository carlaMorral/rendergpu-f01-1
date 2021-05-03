#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H


#include <library/vec.h>

#include "Light.h"

using namespace Common;


class SpotLight : public Light
{
public:
    SpotLight(vec3 ambient, vec3 diffuse, vec3 specular, vec3 direction, float a);

    vec3 getLightDirection();
    void setLightDirection(vec3 d);

    float getAngle();
    void setAngle(float a);

protected:
    vec3 direction;
    float angleObertura;
};

#endif // SPOTLIGHT_H
