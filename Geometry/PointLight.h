#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <library/vec.h>

#include "Light.h"

using namespace Common;


class PointLight : Light
{
public:
    PointLight(vec3 ambient, vec3 diffuse, vec3 specular, vec4 position, vec3 coeficients);

    vec3 getCoeficients() const;
    void setCoeficients(const vec3 &value);

    vec4 getLightPosition();
    void setLightPosition(vec4 v);

protected:

    vec3 coeficients;
};

#endif // POINTLIGHT_H
