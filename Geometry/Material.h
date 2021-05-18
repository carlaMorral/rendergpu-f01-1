#pragma once

#include <vector>

#include <library/Common.h>
#include <memory>

#include <QGLShaderProgram>
#include <QOpenGLTexture>
#include <QFile>
#include <QRegularExpression>
#include <library/vec.h>

using namespace std;
using namespace Common;
// TO DO: A canviar a la fase 1 de la practica 2
// Classe que representa els materials d'un objecte
class Material {


public:
    Material();
    Material(vec3 a, vec3 d, vec3 s, vec3 k, float beta);
    Material(QString fileName);
    ~Material();

    void toGPU(shared_ptr<QGLShaderProgram> program);

    vec3 getAmbient() const;
    vec3 getDiffuse() const;
    vec3 getSpecular() const;
    float getShininess() const;
    vec3 getTransparency() const;

protected:
    vec3 diffuse, ambient, specular, transparency;
    float shininess;
};

