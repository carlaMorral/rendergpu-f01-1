#ifndef CONFIGMAPPINGREADER_H
#define CONFIGMAPPINGREADER_H
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <sstream>
#include <QObject>
#include <QString>
#include <QStringList>
#include <vector>
#include "Geometry/Scene.h"
#include "Geometry/Material.h"
#include "Geometry/Palette.h"


class ConfigMappingReader {
public:
    ConfigMappingReader();

    ConfigMappingReader(QString filename, Scene::DATA_TYPES dataType);

    void readFile (QString fileName);

protected:
    virtual void fileLineRead (QString lineReaded);

    void limitsRealFound(QStringList list);

    void limitsVirtualFound(QStringList list);

    void baseFound(QStringList list);

    void propFound(QStringList list);

public:
    Scene::DATA_TYPES   dataType;
    float               Rxmin, Rxmax, Rymin, Rymax, Rzmin, Rzmax;
    float               Vxmin, Vxmax, Vymin, Vymax, Vzmin, Vzmax;
    int                 numProp;
    vec3                normalPlaBase;
    double              dPlaBase;
    shared_ptr<QOpenGLTexture> texturePlaBase;
    //Per comoditat, oferim també els limits com a vectors i altres mesures:
    vec3                Rmin, Rmax, Vmin, Vmax, Rdiff, Vdiff;
    float               VminDiff, RminDiff;
    vector<pair<double, double>> propLimits;
    vector<pair<QString, shared_ptr<Palette>>> props;
    bool hasPlaBase;
private:
    std::map<QString, shared_ptr<Palette>> usedPalettes;
};


#endif // CONFIGMAPPINGREADER_H
