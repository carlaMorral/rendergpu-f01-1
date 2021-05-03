#include "TG.h"

using namespace Common;

TG::TG()
{
 matTG = mat4(1.0f);
}

TG::TG(mat4 matTG)
{
 this->matTG = matTG;
}

mat4 TG::getTG() {
    return matTG;
}
