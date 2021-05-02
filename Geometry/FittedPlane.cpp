#include "FittedPlane.h"

// Constructora amb tots els parametres
FittedPlane::FittedPlane(int xmin, int zmin, int xmax, int zmax, int d) : Object(4)
{
    qDebug() << "Estic en el constructor del FittedPlane\n";

    vertexs[0] = point4( xmin, d,  zmin, 1.0 );
    vertexs[1] = point4( xmax,  d,  zmin, 1.0 );
    vertexs[2] = point4(  xmax,  d,  zmax, 1.0 );
    vertexs[3] = point4(  xmin, d,  zmax, 1.0 );

    Cara *cara_1 = new Cara();
    cara_1->idxVertices.push_back(0);
    cara_1->idxVertices.push_back(1);
    cara_1->idxVertices.push_back(2);
    cares.push_back(*cara_1);

    Cara *cara_2 = new Cara();
    cara_2->idxVertices.push_back(0);
    cara_2->idxVertices.push_back(2);
    cara_2->idxVertices.push_back(3);
    cares.push_back(*cara_2);

    make();
}

// Destructora
FittedPlane::~FittedPlane()
{
}
