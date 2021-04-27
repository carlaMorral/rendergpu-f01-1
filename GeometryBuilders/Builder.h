#ifndef BUILDER_H
#define BUILDER_H

#include <QtWidgets>
#include <Renders/GLWidget.h>

#include "Mapping.h"
#include "DataService/VirtualWorldReader.h"
#include "DataService/ConfigMappingReader.h"

class Builder : public QObject {
        Q_OBJECT

    shared_ptr<Scene> scene;
    GLWidget *glWidget;
    shared_ptr<Mapping> map;
    shared_ptr<VirtualWorldReader> vwr;
    shared_ptr<ConfigMappingReader> mapping;

public:
    Builder(GLWidget *glWid);

public slots:
    void newObjFromFile();
    void newVirtualScene();
    void newDataScene();

signals:
    void newObj(shared_ptr<Object> o);
    void newScene(shared_ptr<Scene> sc);
};

#endif // BUILDER_H
