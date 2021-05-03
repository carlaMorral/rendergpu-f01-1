#ifndef REALDATAREADER_H
#define REALDATAREADER_H
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <sstream>
#include <QObject>
#include <QString>
#include <QStringList>
#include <vector>
#include "Geometry/TG.h"
#include "Geometry/ScaleTG.h"
#include "Geometry/Scene.h"
#include "GeometryBuilders/Mapping.h"
class RealDataReader {
public:
    explicit RealDataReader();

    RealDataReader(shared_ptr<Scene> s);

    void readFile (QString fileName, shared_ptr<Mapping> map);

private:

    virtual void fileLineRead (QString lineReaded);

    shared_ptr<Scene> scene;
    shared_ptr<Mapping> mapping;

    void dataFound(QStringList list);

};
#endif // REALDATAREADER_H
