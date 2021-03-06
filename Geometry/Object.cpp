#include "Geometry/Object.h"

/**
 * @brief Object::Object
 * @param npoints
 * @param parent
 */
Object::Object(int npoints, QObject *parent) : QObject(parent){
    numPoints = npoints;
    points = new point4[numPoints];
    normals= new point4[numPoints];
    textVertexsGPU = new vec2[numPoints];
    canHaveTexture = true;
    hasTexture = false;

    vec3 ambient(0.1f, 0.02f, 0.02f);
    vec3 diffuse(1.0f, 0.2f, 0.2f);
    vec3 specular(1.0f, 1.0f, 1.0f);
    vec3 transparency(0.0f, 0.0f, 0.0f);
    float shininess = 20.0;
    material = make_shared<Material>(ambient, diffuse, specular, transparency, shininess);
 }


/**
 * @brief Object::Object
 * @param npoints
 * @param n
 */
Object::Object(int npoints, QString n) : numPoints(npoints){
    points = new point4[numPoints];
    normals= new point4[numPoints];
    textVertexsGPU = new vec2[numPoints];
    canHaveTexture = false;
    hasTexture = false;

    /*
    vec3 ambient(0.2f, 0.2f, 0.2f);
    vec3 diffuse(0.8f, 0.5f, 0.5f);
    vec3 specular(1.0f, 1.0f, 1.0f);
    vec3 transparency(0.0f, 0.0f, 0.0f);
    float shininess = 20.0;
    material = make_shared<Material>(ambient, diffuse, specular, transparency, shininess);
    */

    parseObjFile(n);

    //Llegeix material del fitxer que es digui igual pero .mtl
    QString matFile = n.replace(QString(".obj"), QString(".mtl"));
    material = make_shared<Material>(matFile);

    if (canHaveTexture) {
        qDebug() << "Object can support direct textures";
    } else {
        qDebug() << "Object cannot support direct textures";
    }
    make();
}

Object::Object(int npoints, QString n, vec3 position, float scale) : Object(npoints, n){
    setPosition(position);
    setScale(scale);
}

Object::Object(int npoints, QString n, vec3 position, float scale,shared_ptr<Material> material) : Object(npoints, n, position, scale){
    setMaterial(material);
}

void Object::setMaterial(shared_ptr<Material> material){
    this->material = material;
}

/**
 * @brief Object::~Object
 */
Object::~Object(){
    delete points;
    delete normals;
}

/**
 * @brief Object::toGPU
 * @param pr
 */
void Object::toGPU(shared_ptr<QGLShaderProgram> pr) {

    program = pr;

    qDebug() << "Obj to GPU.....";

    // Creaci?? d'un vertex array object
    glGenVertexArrays( 1, &vao );

    // Creacio i inicialitzacio d'un vertex buffer object (VBO)
    glGenBuffers( 1, &buffer );

    // Aqui s'ha de fer el pas de dades a la GPU per si hi ha m??s d'un objecte
    // Activaci?? a GL del Vertex Buffer Object
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    // DONE: fase 1 pas 4
    // Passem les normals a la GPU

    glBufferData( GL_ARRAY_BUFFER, 2*sizeof(point4)*Index + sizeof(vec2)*Index, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*Index, points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index, sizeof(point4)*Index, normals);
    glBufferSubData( GL_ARRAY_BUFFER, 2*sizeof(point4)*Index, sizeof(vec2)*Index, textVertexsGPU);
    qDebug() << "Buffer creat.....";
    // set up vertex arrays
    glBindVertexArray( vao );
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(point4)*Index));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0,  (void*)(2*sizeof(point4)*Index));
    glEnableVertexAttribArray(2);

    glEnable( GL_DEPTH_TEST );
    glEnable(GL_TEXTURE_2D);

    qDebug() << "Tot ja a GPU.....";
}


/**
 * Pintat en la GPU.
 * @brief Object::draw
 */
void Object::draw(){


    qDebug() << "DRAW Object";

    // Aqui s'ha de fer el pas de dades a la GPU per si hi ha m??s d'un objecte
    // Activaci?? a GL del Vertex Buffer Object
    material->toGPU(program);

    this->toGPUTexture(program);

    glBindVertexArray( vao );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays( GL_TRIANGLES, 0, Index );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}

/**
 * @brief Object::make
 */
void Object::make(){

    // DONE: fase 1 pas 4
    // Cal calcular la normal a cada vertex a la CPU


    qDebug() << "MAKE";

    static vec3  base_colors[] = {
        vec3( 1.0, 0.0, 0.0 ),
        vec3( 0.0, 1.0, 0.0 ),
        vec3( 0.0, 0.0, 1.0 )
    };

    Index = 0;
    for(unsigned int i=0; i<cares.size(); i++){
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++){
            points[Index] = vertexs[cares[i].idxVertices[j]];
            normals[Index] = normalsVertexs[cares[i].idxNormals[j]];
            if (this->canHaveTexture || OPT_IND_TEXT_ACT) {
                textVertexsGPU[Index] = textVertexs[cares[i].idxTextures[j]];
            }
            Index++;
        }
    }
}


/**
 * @brief Object::toGPUTexture
 * @param pr
 */
void Object::toGPUTexture(shared_ptr<QGLShaderProgram> pr) {
    program = pr;

    // TO DO: Cal implementar en la fase 1 de la practica 2
    // S'ha d'activar la textura i es passa a la GPU
    if (hasTexture) { //canHaveTexture en comptes de hasTexture per tal que funcioni tambe amb MandelBrot Shader
        texture->bind(0);
        program->setUniformValue("texMap", 0);
    }

    GLuint glHasTexture = program->uniformLocation("hasTexture");
    glUniform1i(glHasTexture, int(this->hasTexture));

}


/**
 * Pintat en la GPU.
 * @brief Object::drawTexture
 */
void Object::drawTexture(){

    // TO DO: Cal implementar en la fase 1 de la practica 2
    // S'ha d'activar la textura i es passa a la GPU

}

void Object::setTexture(shared_ptr<QOpenGLTexture> t){
   texture = t;
   hasTexture = true;
   initTexture();
}

/**
 * @brief Object::initTexture
 */
void Object::initTexture()
 {
    // TO DO: A implementar a la fase 1 de la practica 2
    // Cal inicialitzar la textura de l'objecte: veure l'exemple del CubGPUTextura
    qDebug() << "Initializing textures...";

    // Carregar la textura
    glActiveTexture(GL_TEXTURE0);
    texture->setWrapMode(QOpenGLTexture::Repeat);
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    texture->bind(0);

    printf("Textura carregada");
 }


void Object::parseObjFile(const QString &fileName)
{
    QFile file(fileName);
    if(file.exists()) {
        if(file.open(QFile::ReadOnly | QFile::Text)) {
            QVector<QVector3D> v, vn;
            QVector<QVector2D> vt;

            while(!file.atEnd()) {
                QString line = file.readLine().trimmed();
                QStringList lineParts = line.split(QRegularExpression("\\s+"));
                if(lineParts.count() > 0) {
                    // if it???s a comment
                    if(lineParts.at(0).compare("#", Qt::CaseInsensitive) == 0)
                    {
                        qDebug() << line.remove(0, 1).trimmed();
                    }

                    // if it???s a vertex position (v)
                    else if(lineParts.at(0).compare("v", Qt::CaseInsensitive) == 0)
                    {
                        vertexs.push_back(point4(lineParts.at(1).toFloat(),
                                           lineParts.at(2).toFloat(),
                                           lineParts.at(3).toFloat(), 1.0f));
                    }

                    // if it???s a normal (vn)
                    else if(lineParts.at(0).compare("vn", Qt::CaseInsensitive) == 0)
                    {
                        normalsVertexs.push_back (point4(lineParts.at(1).toFloat(),
                                            lineParts.at(2).toFloat(),
                                            lineParts.at(3).toFloat(), 0.0f));
                    }

                    // if it???s a texture (vt)
                    else if(lineParts.at(0).compare("vt", Qt::CaseInsensitive) == 0)
                    {
                        textVertexs.push_back(vec2(lineParts.at(1).toFloat(),
                                            lineParts.at(2).toFloat()));
                        canHaveTexture = true;
                    }

                    // if it???s face data (f)
                    // there???s an assumption here that faces are all triangles
                    else if(lineParts.at(0).compare("f", Qt::CaseInsensitive) == 0)
                    {
                        Cara *cara = new Cara();

                        // get points from v array
                        cara->idxVertices.push_back(lineParts.at(1).split("/").at(0).toInt() - 1);
                        cara->idxVertices.push_back(lineParts.at(2).split("/").at(0).toInt() - 1);
                        cara->idxVertices.push_back(lineParts.at(3).split("/").at(0).toInt() - 1);

                        if(textVertexs.size() > 0) // check if really there are any UV coords
                        {
                            cara->idxTextures.push_back( lineParts.at(1).split("/").at(1).toInt() - 1);
                            cara->idxTextures.push_back( lineParts.at(2).split("/").at(1).toInt() - 1);
                            cara->idxTextures.push_back( lineParts.at(3).split("/").at(1).toInt() - 1);
                        }

                        // get normals from vn array
                        cara->idxNormals.push_back( lineParts.at(1).split("/").at(2).toInt() - 1);
                        cara->idxNormals.push_back( lineParts.at(2).split("/").at(2).toInt() - 1);
                        cara->idxNormals.push_back( lineParts.at(3).split("/").at(2).toInt() - 1);


                        // cara->calculaNormal();
                        cares.push_back(*cara);
                    }

                }
            }

            file.close();
        }
    }
    if (OPT_IND_TEXT_ACT) {
        fillIndirectTextureCoord();
    }
}

void Object::fillIndirectTextureCoord() {
    Capsa3D capsaMinima = calculCapsa3D();
    vec3 centreCapsa(capsaMinima.pmin.x + capsaMinima.a/float(2), capsaMinima.pmin.y + capsaMinima.h/float(2), capsaMinima.pmin.z + capsaMinima.p/float(2));
    textVertexs.clear();
    int index = 0;
    for(unsigned int i=0; i<cares.size(); i++){
        cares[i].idxTextures.clear();
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++){
            cares[i].idxTextures.push_back(index);
            vec3 posCentrada = vec3(vertexs[cares[i].idxVertices[j]].x, vertexs[cares[i].idxVertices[j]].y, vertexs[cares[i].idxVertices[j]].z) - centreCapsa;
            posCentrada = normalize(posCentrada);
            vec2 coordText(0.5 - atan2(posCentrada.z, posCentrada.x)/(2*M_PI), 0.5 + asin(posCentrada.y)/M_PI);
            qDebug() << "XYZ" << posCentrada.x << posCentrada.y << posCentrada.z << posCentrada.x*posCentrada.x + posCentrada.y*posCentrada.y + posCentrada.z*posCentrada.z;
            qDebug() << "UV" << coordText.x << coordText.y;
            textVertexs.push_back(coordText);
            index++;
        }
        vec2 s3 = textVertexs[index-3];
        vec2 s2 = textVertexs[index-2];
        vec2 s1 = textVertexs[index-1];
        if (s1.x > 0.75 && s2.x > 0.75 && s3.x < 0.25) {
            textVertexs[index-3] += vec2(1.0, 0.0);
        } else if (s1.x > 0.75 && s2.x < 0.25 && s3.x > 0.75) {
            textVertexs[index-2] += vec2(1.0, 0.0);
        } else if (s1.x < 0.25 && s2.x > 0.75 && s3.x > 0.75) {
            textVertexs[index-1] += vec2(1.0, 0.0);
        } else if (s1.x > 0.75 && s2.x < 0.25 && s3.x < 0.25) {
            textVertexs[index-2] += vec2(1.0, 0.0);
            textVertexs[index-3] += vec2(1.0, 0.0);
        } else if (s1.x < 0.25 && s2.x > 0.75 && s3.x < 0.25) {
            textVertexs[index-1] += vec2(1.0, 0.0);
            textVertexs[index-3] += vec2(1.0, 0.0);
        } else if (s1.x < 0.25 && s2.x < 0.25 && s3.x > 0.75) {
            textVertexs[index-1] += vec2(1.0, 0.0);
            textVertexs[index-2] += vec2(1.0, 0.0);
        }
        if (s1.y > 0.75 && s2.y > 0.75 && s3.y < 0.25) {
            textVertexs[index-3] += vec2(0.0, 1.0);
        } else if (s1.y > 0.75 && s2.y < 0.25 && s3.y > 0.75) {
            textVertexs[index-2] += vec2(0.0, 1.0);
        } else if (s1.y < 0.25 && s2.y > 0.75 && s3.y > 0.75) {
            textVertexs[index-1] += vec2(0.0, 1.0);
        } else if (s1.y > 0.75 && s2.y < 0.25 && s3.y < 0.25) {
            textVertexs[index-2] += vec2(0.0, 1.0);
            textVertexs[index-3] += vec2(0.0, 1.0);
        } else if (s1.y < 0.25 && s2.y > 0.75 && s3.y < 0.25) {
            textVertexs[index-1] += vec2(0.0, 1.0);
            textVertexs[index-3] += vec2(0.0, 1.0);
        } else if (s1.y < 0.25 && s2.y < 0.25 && s3.y > 0.75) {
            textVertexs[index-1] += vec2(0.0, 1.0);
            textVertexs[index-2] += vec2(0.0, 1.0);
        }
    }
}

Capsa3D Object::calculCapsa3D()
{
    vec3    pmin, pmax;
    int     i;
    Capsa3D capsa;

    pmin.x = points[0].x;
    pmin.y = points[0].y;
    pmin.z = points[0].z;
    pmax = pmin;
    for(i=1; i<Index; i++) {
        if(points[i].x <pmin[0])
            pmin[0] = points[i].x;
        if(points[i].y <pmin[1])
            pmin[1] = points[i].y;
        if(points[i].z <pmin[2])
            pmin[2] = points[i].z;

        if(points[i].x >pmax[0])
            pmax[0] = points[i].x;
        if(points[i].y >pmax[1])
            pmax[1] = points[i].y;
        if(points[i].z >pmax[2])
            pmax[2] = points[i].z;
    }
    capsa.pmin = pmin;
    capsa.a = pmax[0]-pmin[0];
    capsa.h = pmax[1]-pmin[1];
    capsa.p = pmax[2]-pmin[2];
    return capsa;
}

void Object::setPosition(vec3 position){
    Capsa3D capsaMinima = calculCapsa3D();
    vec3 centreCapsa(capsaMinima.pmin.x + capsaMinima.a/float(2), capsaMinima.pmin.y + capsaMinima.h/float(2), capsaMinima.pmin.z + capsaMinima.p/float(2));
    for(int i =0; i <vertexs.size(); i++){
                this->vertexs[i] = this->vertexs[i] -centreCapsa + position;
    }
    make();
}

void Object::setScale(float scale){
    shared_ptr<ScaleTG> scaleTG = make_shared<ScaleTG>(vec3(scale));
    this->aplicaTG(scaleTG);
}

void Object::aplicaTG(shared_ptr<TG> tg){
    if(dynamic_pointer_cast<TranslateTG>(tg)){
        for(int i =0; i <vertexs.size(); i++){
                    this->vertexs[i] = tg->getTG() * this->vertexs[i];
        }
    }else if(dynamic_pointer_cast<ScaleTG>(tg)){
        Capsa3D capsaMinima = calculCapsa3D();
        vec3 centreCapsa(capsaMinima.pmin.x + capsaMinima.a/float(2), capsaMinima.pmin.y + capsaMinima.h/float(2), capsaMinima.pmin.z + capsaMinima.p/float(2));
        //Cal fer un cub unitari:
        //primer fem que sigui un cub (posem totes les arestes amb longitud igual que la m??s gran)
        //s'ha de dividir per aquesta mida per fer-lo unitari:
        float passarAUnitari(float(1) / max({capsaMinima.a, capsaMinima.h, capsaMinima.p}));
        for(int i = 0; i < vertexs.size(); i++){
            this->vertexs[i] -= centreCapsa;
            this->vertexs[i] *= passarAUnitari;
            this->vertexs[i] = tg->getTG() * this->vertexs[i];
            this->vertexs[i] += centreCapsa;
        }
    }
    make();
}
