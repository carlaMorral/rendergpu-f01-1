#include "Palette.h"


Palette::Palette(QString fileName){
    QFile file(fileName);
    if(!file.exists()){
        std::cout << "Problem reading palette file with name " << fileName.toStdString() << std::endl;
    }
    if(file.open(QFile::ReadOnly | QFile::Text)) {
        bool llegirColors = false;
        while(!file.atEnd()){
            QString line = file.readLine().trimmed();
            QStringList lineParts = line.split(QRegularExpression("\\s+"));
            if(!llegirColors){//Llegim fins a trobar el #
                if(lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0){
                    llegirColors = true;
                }
                qDebug() << line.remove(0, 1).trimmed();
            }else{//Parsegem colors:

            }

        }
    }
}

