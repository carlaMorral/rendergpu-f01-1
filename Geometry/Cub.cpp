#include "Cub.h"

Cub::Cub() : Cub(10.0)
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

    canHaveTexture = true;

}

// Destructora
Cub::~Cub()
{
}


