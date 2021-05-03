#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include <library/vec.h>

#include "Light.h"

using namespace Common;


class DirectionalLight : public Light
{
public:
    DirectionalLight(vec3 ambient, vec3 diffuse, vec3 specular, vec3 direction);

    vec3 getLightDirection();
    void setLightDirection(vec3 d);

protected:
    vec3 direction;
};


#endif // DIRECTIONALLIGHT_H
