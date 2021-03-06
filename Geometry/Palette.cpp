#include "Palette.h"


Palette::Palette(QString fileName){
    QFile file(fileName);
    if(!file.exists()){
        std::cout << "Problem reading palette file with name " << fileName.toStdString() << std::endl;
    }
    if(file.open(QFile::ReadOnly | QFile::Text)) {
        bool llegirColors = false;
        size = 0;
        while(!file.atEnd()){
            QString line = file.readLine().trimmed();
            QStringList lineParts = line.split(QRegularExpression("\\s+"));
            if(!llegirColors){//Llegim fins a trobar el #
                if(lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0){
                    llegirColors = true;
                }
                //qDebug() << line.remove(0, 1).trimmed();
            }else{//Parsegem colors:
                float r = lineParts.at(0).toFloat();
                float g = lineParts.at(1).toFloat();
                float b = lineParts.at(2).toFloat();
                colors.push_back(vec3(r,g,b));
                size++;
            }

        }
    }
}

vec3 Palette::getColor(float value){
    int index = std::max(0, std::min(size-1, (int)floor(value * size)));
    return colors[index] / float(255);
}
