#ifndef SCALETG_H
#define SCALETG_H

#include "TG.h"

class ScaleTG : public TG
{
public:
    Common::vec3 scale;
    ScaleTG(Common::vec3 scale);
};

#endif // SCALETG_H
