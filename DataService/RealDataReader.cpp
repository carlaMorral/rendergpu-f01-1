#include "RealDataReader.h"


RealDataReader::RealDataReader(shared_ptr<Scene> s)
{
    scene = s;
}

void RealDataReader::readFile(QString fileName, shared_ptr<Mapping> map) {
    QFile file(fileName);

    mapping = map;

    if(!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Error opening the file " <<  fileName.toStdString() << std::endl;
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        fileLineRead(line);
    }

    file.close();
}

void RealDataReader::fileLineRead (QString lineReaded) {

    QStringList fields = lineReaded.split(",");
    if (QString::compare("data", fields[0], Qt::CaseInsensitive) == 0)
        dataFound(fields);
    else
        std::cerr << "Element unknown" << std::endl;
}

void RealDataReader::dataFound(QStringList fields) {
    //data x z valor1 valor2...
    int n = mapping->getNumProps();

    if (fields.size() != (3 + n)) {
        std::cerr << "Wrong data format in RealDataReader: required " << n + 3 << " fields, but found instead " << fields.size() << std::endl;
        return;
    }

    shared_ptr<TG> mapeigRealAVirtual = mapping->getMapeigRealAVirtual();
    vec4 puntBasev4 = mapeigRealAVirtual->getTG() * vec4(fields[1].toDouble(), 0.0, fields[2].toDouble(), 1.0);
    vec3 puntBase = vec3(puntBasev4.x, puntBasev4.y, puntBasev4.z);
    for (int i=0; i<n; i++) {

        shared_ptr<Object> o;

        //Valor de la propietat
        float valor = fields[i+3].toFloat();

        //Escalat segons la propietat:
        float escalat = mapping->getEscalat(i, valor);

        // Construccio de l'objecte al Mon Virtual:
        o = make_shared<Object>(100000, mapping->getPropObjectFileName(i), puntBase, escalat);

        //Asignació material:
        vec3 color = mapping->getPaletteProp(i)->getColor(mapping->mapeigValorAUnit(i, valor));

        // Afegir objecte a l'escena
        scene->objects.push_back(o);
    }
}
