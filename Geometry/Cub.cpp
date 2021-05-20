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

    Cara *bottom = new Cara();
    bottom->idxVertices.push_back(4);
    bottom->idxVertices.push_back(0);
    bottom->idxVertices.push_back(3);
    bottom->idxTextures.push_back(0);
    bottom->idxTextures.push_back(13);
    bottom->idxTextures.push_back(2);
    cares.push_back(*bottom);

    Cara *right = new Cara();
    right->idxVertices.push_back(4);
    right->idxVertices.push_back(0);
    right->idxVertices.push_back(3);
    right->idxTextures.push_back(0);
    right->idxTextures.push_back(13);
    right->idxTextures.push_back(2);
    cares.push_back(*bottom);


}

// Destructora
Cub::~Cub()
{
}


