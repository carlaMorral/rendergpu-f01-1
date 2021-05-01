#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>

#include <vector>
#include <iostream>
#include <sstream>

#include "Geometry/Scene.h"
#include "GeometryBuilders/Mapping.h"

class VirtualWorldReader {
public:
    explicit VirtualWorldReader();

    VirtualWorldReader(shared_ptr<Scene> s);

    void readScene (QString fileName, shared_ptr<Mapping> map);

    shared_ptr<Object> readBrObject (QString fileName);

private:
    //virtual void fileLineRead (QString lineReaded);

    shared_ptr<Scene> scene;
    shared_ptr<Mapping> mapping;

};

