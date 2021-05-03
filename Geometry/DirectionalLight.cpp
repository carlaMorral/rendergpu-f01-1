#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(vec3 ambient, vec3 diffuse, vec3 specular, vec3 direction) : Light(LightType::Direccional, ambient, diffuse, specular)
{
    this->direction = direction;
}

vec3 DirectionalLight::getLightDirection(){
    return direction;
}

void DirectionalLight::setLightDirection(vec3 d){
    this->direction = d;
}
