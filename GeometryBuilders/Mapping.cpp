#include "Mapping.h"

Mapping::Mapping(shared_ptr<ConfigMappingReader> mr)
{
   setup = mr;
}

//Aquesta es crida des de VirtualWorldReader
vec3 Mapping::mapeigPunt(vec3 puntMonReal) {
      vec3 Rmin = this->setup->Rmin;
      vec3 Rmax = this->setup->Rmax;
      vec3 Vmin = this->setup->Vmin;
      vec3 Vmax = this->setup->Vmax;

      return (puntMonReal - Rmin) / (Rmax - Rmin) * (Vmax - Vmin) + Vmin;
}


//Aquesta es crida des de VirtualWorldReader
float Mapping::mapeigValor(float valorMonReal) {
    // Es fa un mapejat (minR, maxR) -> (minV, maxV), però agafant l'eix amb menor diferèncie en cada cas!
    return valorMonReal / this->setup->RminDiff * this->setup->VminDiff;
}

shared_ptr<TG> Mapping::getMapeigRealAVirtual(){
    vec3 Rmin = this->setup->Rmin;
    vec3 Rmax = this->setup->Rmax;
    vec3 Vmin = this->setup->Vmin;
    vec3 Vmax = this->setup->Vmax;
    vec3 vDiv = vec3(1,1,1)/(Rmax - Rmin);
    vDiv.y = 0;
    mat4 restamR = Translate(-Rmin);
    mat4 divisioRDiff = Scale(vDiv);
    mat4 vDiff = Scale(Vmax - Vmin);
    mat4 sumaVmin = Translate(Vmin);
    //Provisional Fase 2E:  inverteix eix de les Z, com s'explica a l'enunciat del FASE2 E.1
    mat4 invertZ = Scale(vec3(1,1,-1));
    //Ordre invers (matrius no són commutatives i es multiplicarà el punt per la dreta)
    auto tg = make_shared<TG>(invertZ*sumaVmin*vDiff*divisioRDiff*restamR);
    return tg;
}


shared_ptr<ScaleTG> Mapping::getEscalat(int iProp, float valorMonReal){
    float minProp = setup->propLimits[iProp].first;
    float maxProp = setup->propLimits[iProp].second;
    //Mapegem el rang (valorMinProp, valorMaxProp) al rang (0.01 * minDiffV, minDiffV)
    float minVirtual = 0.01*setup->VminDiff;
    float maxVirtual = 0.5*setup->VminDiff;
    float factor = minVirtual + (valorMonReal - minProp) / (maxProp - minProp) * (maxVirtual - minVirtual);
    auto tg = make_shared<ScaleTG>(vec3(factor, factor, factor));
    return tg;
}
