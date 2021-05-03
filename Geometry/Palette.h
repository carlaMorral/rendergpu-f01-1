#ifndef PALETTE_H
#define PALETTE_H

#include <vector>
#include <library/Common.h>
using namespace Common;
#include <QFile>
#include <QString>
#include <QStringList>
#include <QRegularExpression>
#include <QDebug>
class Palette
{
public:
    Palette(QString fileName);

    vec3 getColor(float value); //value between 0,1

private:
    QString fileName;
    int size;
    std::vector<vec3> colors;
};

#endif // PALETTE_H
