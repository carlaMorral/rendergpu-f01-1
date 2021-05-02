#pragma once

#include "../library/Common.h"
#include "Object.h"
#include <QGLShaderProgram>

#include <stdio.h>

typedef vec4  point4;

class FittedPlane: public Object
{
  public:
      FittedPlane(int xmin, int zmin, int xmax, int zmax, int d);
      ~FittedPlane();
};

