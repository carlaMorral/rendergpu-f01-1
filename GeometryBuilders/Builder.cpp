#include "GeometryBuilders/Builder.h"

Builder::Builder(GLWidget *glWid)
{
    glWidget = glWid;
    scene = glWidget->getScene();
    vwr = make_shared<VirtualWorldReader>(scene);
    rdr = make_shared<RealDataReader>(scene);
}

void Builder::newObjFromFile()
{
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
            shared_ptr<Object> obj = vwr->readBrObject(fileName);
            emit newObj(obj);
    }
}

void Builder::newVirtualScene() {
    // TO DO Fase 1: creació de la nova escena Virtual a partir d'un fitxer
    // de  a partir de les dades
    // del configMapping  i un fitxer .txt de tipus VIRTUALWORLD.
    // Nomes hi hauran fitxers de tipus BoundaryObject.
    // Usa el ConfigMappingReader i la teva SceneFactoryVirtual
    // per a construir l'escena tal i com feies a la practica 1
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
        QString configMapping = QString(fileName).replace(QString(".txt"), QString("_mapping.txt"));
        shared_ptr<ConfigMappingReader> mr = make_shared<ConfigMappingReader>(configMapping, Scene::VIRTUALWORLD);
        map = make_shared<Mapping>(mr);
        vwr->readScene(fileName, map);
    }
    emit newScene(scene);
}


void Builder::newDataScene()
{
    // TO DO Fase 1: Crear la nova escena a partir de les dades
    // del configMapping i el fitxer .txt que conté les dades
    // Utilitza el ConfigMappingReader i la teva SceneFactoryData per a llegir els fitxers
    // i crear l'escena corresponent.
    QString fileName = QFileDialog::getOpenFileName();
    if (!fileName.isNull()) {
        QString configMapping = QString(fileName).replace(QString(".txt"), QString("_mapping.txt"));
        shared_ptr<ConfigMappingReader> mr = make_shared<ConfigMappingReader>(configMapping, Scene::REALDATA);
        map = make_shared<Mapping>(mr);
        rdr->readFile(fileName, map);
    }
    emit newScene(scene);
    // Opcionalment pots crear un dialeg per posar els valors del mapping
    //TODO: If fitxer mapping not found, diàleg?
}

