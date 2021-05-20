#include "Cub.h"

Cub::Cub() : Cub(1.0)
{
    qDebug() <<"Estic en el constructor del Cub\n";

}

// Constructora amb tots els parametres
Cub::Cub(float a) : Object(8)
{
    qDebug() <<"Estic en el constructor parametritzat del Cub\n";
    vertexs.push_back(point4( -a/2, -a/2,  a/2, 1.0 ));
    vertexs.push_back(point4( -a/2,  a/2,  a/2, 1.0 ));
    vertexs.push_back(point4(  a/2,  a/2,  a/2, 1.0 ));
    vertexs.push_back(point4(  a/2, -a/2,  a/2, 1.0 ));
    vertexs.push_back(point4( -a/2, -a/2, -a/2, 1.0 ));
    vertexs.push_back(point4( -a/2,  a/2, -a/2, 1.0 ));
    vertexs.push_back(point4(  a/2,  a/2, -a/2, 1.0 ));
    vertexs.push_back(point4(  a/2, -a/2, -a/2, 1.0 ));

    textVertexs.push_back(vec2(1./4,0.0));
    textVertexs.push_back(vec2(2./4,0.0));
    textVertexs.push_back(vec2(2./4,1./3));
    textVertexs.push_back(vec2(3./4,1./3));
    textVertexs.push_back(vec2(1.0,1./3));
    textVertexs.push_back(vec2(1.0,2./3));
    textVertexs.push_back(vec2(3./4,2./3));
    textVertexs.push_back(vec2(2./4,2./3));
    textVertexs.push_back(vec2(2./4,1.0));
    textVertexs.push_back(vec2(1./4,1.0));
    textVertexs.push_back(vec2(1./4,2./3));
    textVertexs.push_back(vec2(0.0,2./3));
    textVertexs.push_back(vec2(0.0,1./3));
    textVertexs.push_back(vec2(1./4,1./3));

    // Bottom
    Cara *bottomTriangle1 = new Cara();
    bottomTriangle1->idxVertices.push_back(4);
    bottomTriangle1->idxVertices.push_back(0);
    bottomTriangle1->idxVertices.push_back(7);
    bottomTriangle1->idxTextures.push_back(0);
    bottomTriangle1->idxTextures.push_back(13);
    bottomTriangle1->idxTextures.push_back(1);
    cares.push_back(*bottomTriangle1);

    Cara *bottomTriangle2 = new Cara();
    bottomTriangle2->idxVertices.push_back(7);
    bottomTriangle2->idxVertices.push_back(0);
    bottomTriangle2->idxVertices.push_back(3);
    bottomTriangle2->idxTextures.push_back(1);
    bottomTriangle2->idxTextures.push_back(13);
    bottomTriangle2->idxTextures.push_back(2);
    cares.push_back(*bottomTriangle2);

    // Front
    Cara *frontTriangle1 = new Cara();
    frontTriangle1->idxVertices.push_back(0);
    frontTriangle1->idxVertices.push_back(1);
    frontTriangle1->idxVertices.push_back(3);
    frontTriangle1->idxTextures.push_back(13);
    frontTriangle1->idxTextures.push_back(10);
    frontTriangle1->idxTextures.push_back(2);
    cares.push_back(*frontTriangle1);

    Cara *frontTriangle2 = new Cara();
    frontTriangle2->idxVertices.push_back(3);
    frontTriangle2->idxVertices.push_back(1);
    frontTriangle2->idxVertices.push_back(2);
    frontTriangle2->idxTextures.push_back(2);
    frontTriangle2->idxTextures.push_back(10);
    frontTriangle2->idxTextures.push_back(7);
    cares.push_back(*frontTriangle2);

    // Top
    Cara *topTriangle1 = new Cara();
    topTriangle1->idxVertices.push_back(1);
    topTriangle1->idxVertices.push_back(5);
    topTriangle1->idxVertices.push_back(2);
    topTriangle1->idxTextures.push_back(10);
    topTriangle1->idxTextures.push_back(9);
    topTriangle1->idxTextures.push_back(7);
    cares.push_back(*topTriangle1);

    Cara *topTriangle2 = new Cara();
    topTriangle2->idxVertices.push_back(2);
    topTriangle2->idxVertices.push_back(5);
    topTriangle2->idxVertices.push_back(6);
    topTriangle2->idxTextures.push_back(7);
    topTriangle2->idxTextures.push_back(9);
    topTriangle2->idxTextures.push_back(8);
    cares.push_back(*topTriangle2);

    // Right
    Cara *rightTriangle1 = new Cara();
    rightTriangle1->idxVertices.push_back(3);
    rightTriangle1->idxVertices.push_back(2);
    rightTriangle1->idxVertices.push_back(7);
    rightTriangle1->idxTextures.push_back(2);
    rightTriangle1->idxTextures.push_back(7);
    rightTriangle1->idxTextures.push_back(3);
    cares.push_back(*rightTriangle1);

    Cara *rightTriangle2 = new Cara();
    rightTriangle2->idxVertices.push_back(7);
    rightTriangle2->idxVertices.push_back(2);
    rightTriangle2->idxVertices.push_back(6);
    rightTriangle2->idxTextures.push_back(3);
    rightTriangle2->idxTextures.push_back(7);
    rightTriangle2->idxTextures.push_back(6);
    cares.push_back(*rightTriangle2);

    // Left
    Cara *leftTriangle1 = new Cara();
    leftTriangle1->idxVertices.push_back(4);
    leftTriangle1->idxVertices.push_back(5);
    leftTriangle1->idxVertices.push_back(0);
    leftTriangle1->idxTextures.push_back(12);
    leftTriangle1->idxTextures.push_back(11);
    leftTriangle1->idxTextures.push_back(13);
    cares.push_back(*leftTriangle1);

    Cara *leftTriangle2 = new Cara();
    leftTriangle2->idxVertices.push_back(0);
    leftTriangle2->idxVertices.push_back(5);
    leftTriangle2->idxVertices.push_back(1);
    leftTriangle2->idxTextures.push_back(13);
    leftTriangle2->idxTextures.push_back(11);
    leftTriangle2->idxTextures.push_back(10);
    cares.push_back(*leftTriangle2);

    // Back
    Cara *backTriangle1 = new Cara();
    backTriangle1->idxVertices.push_back(7);
    backTriangle1->idxVertices.push_back(6);
    backTriangle1->idxVertices.push_back(4);
    backTriangle1->idxTextures.push_back(3);
    backTriangle1->idxTextures.push_back(6);
    backTriangle1->idxTextures.push_back(4);
    cares.push_back(*backTriangle1);

    Cara *backTriangle2 = new Cara();
    backTriangle2->idxVertices.push_back(4);
    backTriangle2->idxVertices.push_back(6);
    backTriangle2->idxVertices.push_back(5);
    backTriangle2->idxTextures.push_back(4);
    backTriangle2->idxTextures.push_back(6);
    backTriangle2->idxTextures.push_back(5);
    cares.push_back(*backTriangle2);

    faces.push_back(QImage("://resources/textures/skybox/right.jpg"));
    faces.push_back(QImage("://resources/textures/skybox/left.jpg"));
    faces.push_back(QImage("://resources/textures/skybox/bottom.jpg"));
    faces.push_back(QImage("://resources/textures/skybox/top.jpg"));
    faces.push_back(QImage("://resources/textures/skybox/back.jpg"));
    faces.push_back(QImage("://resources/textures/skybox/front.jpg"));

    canHaveTexture = true;

}

// Destructora
Cub::~Cub()
{
}

void Cub::setTexture() {
    QImage image[6];
    for (GLuint i = 0; i < faces.size(); i++) {
        image[i] = faces[i].convertToFormat(QImage::Format_RGBA8888);
    }

    glActiveTexture(GL_TEXTURE0);

    texture = make_shared<QOpenGLTexture>(QOpenGLTexture::TargetCubeMap);

    if (!texture->isCreated())
        texture->create();

    glBindTexture(GL_TEXTURE_CUBE_MAP, texture->textureId());

    texture->setFormat(QOpenGLTexture::RGBAFormat);
    texture->setSize(image[0].width(), image[0].height(), image[0].depth());
    texture->generateMipMaps();
    texture->allocateStorage();

    texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveX, QOpenGLTexture::RGBA,
                     QOpenGLTexture::UInt8, (const void*)image[0].constBits(), 0);
    texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveY, QOpenGLTexture::RGBA,
                     QOpenGLTexture::UInt8, (const void*)image[3].constBits(), 0);
    texture->setData(0, 0, QOpenGLTexture::CubeMapPositiveZ, QOpenGLTexture::RGBA,
                     QOpenGLTexture::UInt8, (const void*)image[5].constBits(), 0);
    texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeX, QOpenGLTexture::RGBA,
                     QOpenGLTexture::UInt8, (const void*)image[1].constBits(), 0);
    texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeY, QOpenGLTexture::RGBA,
                     QOpenGLTexture::UInt8, (const void*)image[2].constBits(), 0);
    texture->setData(0, 0, QOpenGLTexture::CubeMapNegativeZ, QOpenGLTexture::RGBA,
                     QOpenGLTexture::UInt8, (const void*)image[4].constBits(), 0);

    texture->setWrapMode(QOpenGLTexture::ClampToEdge);
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    make();

}

void Cub::draw() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, Index);
    glDepthFunc(GL_LESS);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glDisable(GL_TEXTURE_CUBE_MAP);
}


void Cub::make(){

    qDebug() << "MAKE";

    Index = 0;
    for(unsigned int i=0; i<cares.size(); i++){
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++){
            points[Index] = vertexs[cares[i].idxVertices[j]];
            textVertexsGPU[Index] = textVertexs[cares[i].idxTextures[j]];
            Index++;
        }
    }
}

void Cub::toGPU(shared_ptr<QGLShaderProgram> pr) {

    program = pr;

    qDebug() << "Cube to GPU.....";

    texture->bind(texture->textureId());
    program->setUniformValue("textEnvironment", texture->textureId());

    // Creació d'un vertex array object
    glGenVertexArrays( 1, &vao );

    // Creacio i inicialitzacio d'un vertex buffer object (VBO)
    glGenBuffers( 1, &buffer );

    // Activació a GL del Vertex Buffer Object
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    glBufferData( GL_ARRAY_BUFFER, sizeof(point4)*Index + sizeof(vec2)*Index, NULL, GL_STATIC_DRAW );
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*Index, points );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index, sizeof(vec2)*Index, textVertexsGPU);

    qDebug() << "Buffer creat.....";
    // set up vertex arrays
    glBindVertexArray( vao );
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0,  0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,  (void*)(sizeof(point4)*Index));
    glEnableVertexAttribArray(1);

    glEnable(GL_TEXTURE_CUBE_MAP);

    qDebug() << "Tot ja a GPU.....";
}








