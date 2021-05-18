#include "Geometry/Material.h"


Material::Material(): diffuse(1.0f) {

}

Material::~Material() {

}

Material::Material(QString fileName){
    // http://paulbourke.net/dataformats/mtl/
    //Default values:
    this->ambient = vec3(0.2f, 0.2f, 0.2f);
    this->diffuse = vec3(0.8f, 0.5f, 0.5f);
    this->specular = vec3(1.0f, 1.0f, 1.0f);
    this->transparency = vec3(0.0f, 0.0f, 0.0f);
    this->shininess = 20.0;
    QFile file(fileName);
    if(!file.exists()){
        std::cout << "Material file " << fileName.toStdString() << " not found. Loading default values." << std::endl;
        return;
    }
    if(file.open(QFile::ReadOnly | QFile::Text)) {
        bool llegirMaterial = false;
        while(!file.atEnd()){
            QString line = file.readLine().trimmed();
            QStringList lineParts = line.split(QRegularExpression("\\s+"));
            if(!llegirMaterial){//Llegim fins a trobar el newmtl
                if(lineParts.at(0).compare("newmtl", Qt::CaseInsensitive) == 0){
                    llegirMaterial = true;
                }
            }else{//Parsegem components:
                //NOMES LLEGIM: ambient (Ka), diffuse (Kd), specular (Ks), transparency (Kt?), shininess (Ns?)
                QString first = lineParts.at(0);
                if(first.compare("Ka", Qt::CaseInsensitive) == 0){
                    float r = lineParts.at(1).toFloat();
                    float g = lineParts.at(2).toFloat();
                    float b = lineParts.at(3).toFloat();
                    this->ambient = vec3(r,g,b);
                }
                else if(first.compare("Kd", Qt::CaseInsensitive) == 0){
                    float r = lineParts.at(1).toFloat();
                    float g = lineParts.at(2).toFloat();
                    float b = lineParts.at(3).toFloat();
                    this->diffuse = vec3(r,g,b);
                }
                else if(first.compare("Ks", Qt::CaseInsensitive) == 0){
                    float r = lineParts.at(1).toFloat();
                    float g = lineParts.at(2).toFloat();
                    float b = lineParts.at(3).toFloat();
                    this->specular = vec3(r,g,b);
                }
                else if(first.compare("Kt", Qt::CaseInsensitive) == 0){
                    float r = lineParts.at(1).toFloat();
                    float g = lineParts.at(2).toFloat();
                    float b = lineParts.at(3).toFloat();
                    this->transparency = vec3(r,g,b);
                }
                else if(first.compare("Ns", Qt::CaseInsensitive) == 0){
                    float s = lineParts.at(1).toFloat();
                    this->shininess = s;
                }
            }
        }
    }
}


Material::Material(vec3 a, vec3 d, vec3 s, vec3 k, float beta) {
    this->ambient = a;
    this->diffuse = d;
    this->specular = s;
    this->shininess = beta;
    this->transparency = k;
}

vec3 Material::getAmbient() const {
    return this->ambient;
}

vec3 Material::getDiffuse() const {
    return this->diffuse;
}

vec3 Material::getSpecular() const {
    return this->specular;
}

float Material::getShininess() const {
    return this->shininess;
}

vec3 Material::getTransparency() const {
    return this->transparency;
}

/**
 * Passa el material de CPU a GPU
 * @brief Material::toGPU
 * @param program
 */
void Material::toGPU(shared_ptr<QGLShaderProgram> program){
    // Primer passarem el material
    // 1. Declerem un struct amb la informacio del material

    struct {
        GLuint ambient;
        GLuint diffuse;
        GLuint specular;
        GLuint transparency;
        GLuint shininess;
    } gl_IdMaterial;

    // 2. Obtenim identificadors GPU
    gl_IdMaterial.ambient = program->uniformLocation("material.ambient");
    gl_IdMaterial.diffuse = program->uniformLocation("material.diffuse");
    gl_IdMaterial.specular = program->uniformLocation("material.specular");
    gl_IdMaterial.transparency = program->uniformLocation("material.transparency");
    gl_IdMaterial.shininess = program->uniformLocation("material.shininess");

    // 3. Bind de les zones de memòria de GPU a CPU
    glUniform3fv(gl_IdMaterial.ambient, 1, getAmbient());
    glUniform3fv(gl_IdMaterial.diffuse, 1, getDiffuse());
    glUniform3fv(gl_IdMaterial.specular, 1, getSpecular());
    glUniform3fv(gl_IdMaterial.transparency, 1, getTransparency());
    glUniform1f(gl_IdMaterial.shininess, getShininess());
}

