#include "VirtualWorldReader.h"


VirtualWorldReader::VirtualWorldReader(shared_ptr<Scene> s)
{
    scene = s;
}

void VirtualWorldReader::readScene(QString fileName, shared_ptr<Mapping> map) {

    mapping = map;
    std::cout << fileName.toStdString()<<std::endl;

    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Error opening the file" << std::endl;
        return;
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(",");
        readBrObject(fields[0]);
    }
    file.close();
}

shared_ptr<Object> VirtualWorldReader::readBrObject (QString fileName) {
    auto obj = make_shared<Object>(100000, fileName);
    scene->addObject(obj);
    scene->camera->actualitzaCamera(scene->capsaMinima);
    return obj;
}



