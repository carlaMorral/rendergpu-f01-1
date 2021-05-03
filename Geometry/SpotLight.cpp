#include "SpotLight.h"

SpotLight::SpotLight(vec3 ambient, vec3 diffuse, vec3 specular, vec3 direction, float angle) : Light(LightType::Spot, ambient, diffuse, specular)
{
    this->direction = direction;
    this->angleObertura = angle;
}

vec3 SpotLight::getLightDirection(){
    return direction;
}

void SpotLight::setLightDirection(vec3 d){
    this->direction = d;
}

float SpotLight::getAngle(){
    return this->angleObertura;
}

void SpotLight::setAngle(float a){
    this->angleObertura = a;
}

