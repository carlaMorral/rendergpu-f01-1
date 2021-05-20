#ifndef CUB_H
#define CUB_H
#include "../library/Common.h"
#include "Object.h"
#include <QGLShaderProgram>
#include <QOpenGLTexture>

#include <stdio.h>


const int NumVertices = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

typedef vec4  color4;
typedef vec4  point4;

class Cub: public Object
{
  public:
      Cub();
      Cub(float a);
      ~Cub();
};

#endif // CUB_H
