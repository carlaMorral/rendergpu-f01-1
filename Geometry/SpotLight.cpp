#include "SpotLight.h"

SpotLight::SpotLight(vec3 ambient, vec3 diffuse, vec3 specular, vec3 direction, float angle, float sharpness) : Light(LightType::Spot, ambient, diffuse, specular)
{
    this->direction = direction;
    this->angleObertura = angle;
    this->sharpness = sharpness;
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

float SpotLight::getSharpness(){
    return this->sharpness;
}

