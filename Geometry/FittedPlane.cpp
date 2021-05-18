#include "FittedPlane.h"

// Constructora amb tots els parametres
FittedPlane::FittedPlane(int xmin, int xmax, int zmin, int zmax, int d) : Object(4)
{
    qDebug() << "Estic en el constructor del FittedPlane\n";
    vertexs.push_back(point4( xmin, d,  zmin, 1.0 ));
    vertexs.push_back(point4( xmax,  d,  zmin, 1.0 ));
    vertexs.push_back(point4(  xmax,  d,  zmax, 1.0 ));
    vertexs.push_back(point4(  xmin, d,  zmax, 1.0 ));

    normalsVertexs.push_back(point4(0, -1, 0, 0));
    normalsVertexs.push_back(point4(0, -1, 0, 0));
    normalsVertexs.push_back(point4(0, -1, 0, 0));
    normalsVertexs.push_back(point4(0, -1, 0, 0));

    textVertexs.push_back(vec2(0,0));
    textVertexs.push_back(vec2(1,0));
    textVertexs.push_back(vec2(1,1));
    textVertexs.push_back(vec2(0,1));

    Cara *cara_1 = new Cara();
    cara_1->idxVertices.push_back(0);
    cara_1->idxVertices.push_back(1);
    cara_1->idxVertices.push_back(2);
    cara_1->idxTextures.push_back(0);
    cara_1->idxTextures.push_back(1);
    cara_1->idxTextures.push_back(2);
    cara_1->idxNormals.push_back(0);
    cara_1->idxNormals.push_back(1);
    cara_1->idxNormals.push_back(2);
    cares.push_back(*cara_1);

    Cara *cara_2 = new Cara();
    cara_2->idxVertices.push_back(0);
    cara_2->idxVertices.push_back(2);
    cara_2->idxVertices.push_back(3);
    cara_2->idxTextures.push_back(0);
    cara_2->idxTextures.push_back(2);
    cara_2->idxTextures.push_back(3);
    cara_2->idxNormals.push_back(0);
    cara_2->idxNormals.push_back(2);
    cara_2->idxNormals.push_back(3);
    cares.push_back(*cara_2);

    normalsVertexs.push_back(point4(0, 1, 0, 0));
    normalsVertexs.push_back(point4(0, 1, 0, 0));
    normalsVertexs.push_back(point4(0, 1, 0, 0));
    normalsVertexs.push_back(point4(0, 1, 0, 0));

    Cara *cara_3 = new Cara();
    cara_3->idxVertices.push_back(2);
    cara_3->idxVertices.push_back(1);
    cara_3->idxVertices.push_back(0);
    cara_3->idxTextures.push_back(2);
    cara_3->idxTextures.push_back(1);
    cara_3->idxTextures.push_back(0);
    cara_3->idxNormals.push_back(6);
    cara_3->idxNormals.push_back(5);
    cara_3->idxNormals.push_back(4);
    cares.push_back(*cara_3);

    Cara *cara_4 = new Cara();
    cara_4->idxVertices.push_back(3);
    cara_4->idxVertices.push_back(2);
    cara_4->idxVertices.push_back(0);
    cara_4->idxTextures.push_back(3);
    cara_4->idxTextures.push_back(2);
    cara_4->idxTextures.push_back(0);
    cara_4->idxNormals.push_back(7);
    cara_4->idxNormals.push_back(6);
    cara_4->idxNormals.push_back(4);
    cares.push_back(*cara_4);

    make();
}

// Destructora
FittedPlane::~FittedPlane()
{
}
