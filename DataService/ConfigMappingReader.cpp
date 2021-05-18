#include "ConfigMappingReader.h"

ConfigMappingReader::ConfigMappingReader(QString filename, Scene::DATA_TYPES dataType)
{
  numProp = 0;
  this->dataType = dataType;
  usedPalettes = {};
  readFile(filename);
}

void ConfigMappingReader::readFile(QString fileName) {
    QFile file(fileName);

    if(!file.open(QIODevice::ReadOnly)) {
        std::cerr << "Error opening the file " << fileName.toStdString() << std::endl;
        return;
    }

    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        fileLineRead(line);
    }
    file.close();
}

void ConfigMappingReader::fileLineRead (QString lineReaded) {

    QStringList fields = lineReaded.split(",");
    if (QString::compare("limitsMonVirtual", fields[0], Qt::CaseInsensitive) == 0)
        limitsVirtualFound(fields);
    else  if (QString::compare("limitsMonReal", fields[0], Qt::CaseInsensitive) == 0)
        limitsRealFound(fields);
    else if (QString::compare("plaBase", fields[0], Qt::CaseInsensitive) == 0)
        baseFound(fields);
    else if (QString::compare("prop", fields[0], Qt::CaseInsensitive) == 0)
        propFound(fields);
    else
        std::cerr << "Element unknown" << std::endl;
}

void ConfigMappingReader::limitsVirtualFound(QStringList fields) {
    // limitsMonVirtual xmin xmax zmin zmax
    if (fields.size() != 7 ) {
        std::cerr << "Wrong limits format c1" << std::endl;
        return;
    }
    Vxmin = fields[1].toDouble();
    Vxmax = fields[2].toDouble();
    Vymin = fields[3].toDouble();
    Vymax = fields[4].toDouble();
    Vzmin = fields[5].toDouble();
    Vzmax = fields[6].toDouble();
    Vmin = vec3(Vxmin, Vymin, Vzmin);
    Vmax = vec3(Vxmax, Vymax, Vzmax);
    Vdiff = vec3(Vxmax - Vxmin, Vymax - Vymin, Vzmax - Vzmin);
    VminDiff = min({Vdiff.x, Vdiff.y, Vdiff.z});
}

void ConfigMappingReader::limitsRealFound(QStringList fields) {
    // limitsMonVirtual xmin xmax zmin zmax
    if (this->dataType==Scene::DATA_TYPES::REALDATA || this->dataType==Scene::REALDATA) {
        if (fields.size() != 5 ) {
            std::cerr << "Wrong limits format a1" << std::endl;
            return;
        }
        Rxmin = fields[1].toDouble();
        Rxmax = fields[2].toDouble();
        Rzmin = fields[3].toDouble();
        Rzmax = fields[4].toDouble();

    } else {
        // limitsMonVirtual xmin xmax ymin ymax zmin zmax
        if (fields.size() != 7 ) {
            std::cerr << "Wrong limits format b1" << std::endl;
            return;
        }
        Rxmin = fields[1].toDouble();
        Rxmax = fields[2].toDouble();
        Rymin = fields[3].toDouble();
        Rymax = fields[4].toDouble();
        Rzmin = fields[5].toDouble();
        Rzmax = fields[6].toDouble();
    }
    Rmin = vec3(Rxmin, Rymin, Rzmin);
    Rmax = vec3(Rxmax, Rymax, Rzmax);
    Rdiff = vec3(Rxmax- Rxmin, Rymax- Rymin, Rzmax - Rzmin);
    RminDiff = min({Rdiff.x, Rdiff.y, Rdiff.z});
}

void ConfigMappingReader::baseFound(QStringList fields) {
    //base plane nx ny nz d textura
    if (fields.size() != 6) {
        std::cerr << "Wrong base format" << std::endl;
        return;
    }

    normalPlaBase = vec3(fields[1].toDouble(), fields[2].toDouble(), fields[3].toDouble());
    dPlaBase = fields[4].toDouble();
    texturePlaBase = make_shared<QOpenGLTexture>(QImage(fields[5]));
}

void ConfigMappingReader::propFound(QStringList fields) {
    //prop numProp vmin vmax .obj palette(.gpl)

    std::cerr<<"Prop found"<<std::endl;
    if (fields.size() != 6) {
        std::cerr << "Wrong propietat format config mapping" << std::endl;
        return;
    }
    numProp++;
    propLimits.push_back(std::make_pair(fields[2].toDouble(), fields[3].toDouble()));
    QString objFileName = fields[4];
    QString palFileName = fields[5];
    if(usedPalettes.find(palFileName) == usedPalettes.end()){
        usedPalettes[palFileName] = make_shared<Palette>(palFileName);
    }

    props.push_back(std::make_pair(objFileName, usedPalettes[palFileName]));

}
