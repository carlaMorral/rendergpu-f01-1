#ifndef MAPPING_H
#define MAPPING_H

#pragma once

#include <string.h>

#include "DataService/ConfigMappingReader.h"
#include "Geometry/ColorMap.h"
#include "Geometry/ColorMapStatic.h"
#include "Geometry/Material.h"
//#include "GeometryBuilders/ObjectFactory.h"
#include "Geometry/TranslateTG.h"
#include "Geometry/ScaleTG.h"

#include <QString>

using namespace std;

class Mapping
{
public:

    Mapping();
    Mapping(const shared_ptr<ConfigMappingReader> configMapping);

    Scene::DATA_TYPES    getDataType(){
        return setup->dataType;
    }
    vec3  mapeigPunt(vec3 puntMonReal);
    float mapeigValor(float valorMonReal);
    float mapeigValor(int i ,float valorMonReal);

    int getNumProps() { return setup->numProp; };

    vec3 getNormalBasePlane(){ return setup->normalPlaBase; };
    float getdBasePlane(){ return setup->dPlaBase; };
    //shared_ptr<Texture> getTextureBasePlane(){return setup->texturePlaBase; }; //TODO: quan afegim textures (pas 5)
    vec3 getVirtualMaxCoord(){ return setup->Vmax; };
    vec3 getVirtualMinCoord(){ return setup->Vmin; };

    shared_ptr<TG> getMapeigRealAVirtual();
    shared_ptr<ScaleTG> getEscalat(int iProp, float valorMonReal);

    //ColorMapStatic::COLOR_MAP_TYPES getColorMapProp(int i) {
    //    return setup->props[i].second;
    //}

    QString getPropObjectFileName(int index){
        return setup->props[index].first;
    };

    //shared_ptr<ColorMap> getColorMap(ColorMapStatic::COLOR_MAP_TYPES tCM);

private:
    shared_ptr<ConfigMappingReader> setup;
};


#endif // MAPPING_H
