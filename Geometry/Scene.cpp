#include "Geometry/Scene.h"

/**
 * @brief Scene::Scene
 */
Scene::Scene() {
    // Inicialització de la capsa minima
    capsaMinima.pmin = vec3(-1.0, -1.0,-1.0);
    capsaMinima.a = 2;
    capsaMinima.h = 2;
    capsaMinima.p = 2;
    lightAmbientGlobal = vec3(0.2, 0.2, 0.2);

}

/**
 * @brief Scene::~Scene
 */
Scene::~Scene() {
    objects.clear();
    lights.clear();
}

/**
 * @brief Scene::addObject
 * @param obj
 */
void Scene::addObject(shared_ptr<Object> obj) {
    objects.push_back(obj);
    calculCapsaMinCont3DEscena();
}

/**
 * @brief Scene::toGPU
 */
void Scene::toGPU(shared_ptr<QGLShaderProgram> p) {
    for(unsigned int i=0; i < objects.size(); i++){
        objects.at(i)->toGPU(p);
    }
}

/**
 * @brief Scene::draw
 */
void Scene::draw() {
    for(unsigned int i=0; i < objects.size(); i++){
        objects.at(i)->draw();
    }
}

/**
 * @brief Scene::drawTexture
 */
void Scene::drawTexture() {
    for(unsigned int i=0; i < objects.size(); i++){
        objects.at(i)->drawTexture();
    }
}

/**
 * @brief Scene::getLightActual
 * @return
 */
shared_ptr<Light> Scene::getLightActual() {
    // TO DO OPCIONAL: A modificar si es vol canviar el comportament de la GUI
    // Ara per ara dona com a Light actual la darrera que s'ha inserit
    return (lights[lights.size()-1]);
}

/**
 * @brief Scene::setLightActual
 * @param l
 */
void Scene::setLightActual(shared_ptr<Light> l){
    lights[lights.size()-1]=l;
}



/**
 * @brief Scene::lightsToGPU
 * @param program
 */
void Scene::lightsToGPU(shared_ptr<QGLShaderProgram> program){

    // 1. Es declara un struct d'identificadors
    struct gl_IdLight
    {
     GLuint id_type;
     GLuint id_ambient;
     GLuint id_diffuse;
     GLuint id_specular;
     GLuint id_position;
     GLuint id_direction;
     GLuint id_coefficients;
     GLuint id_angle;
    };

    // vector de structs gl_IdLights
    gl_IdLight gl_IdVectLights [MAX_LIGHTS];

    for(uint i=0; i<MAX_LIGHTS && i<lights.size(); i++){

        // 2. Creem les variables per cada identificador

        // Variables per totes les llums
        int type = lights.at(i)->getTipusLight();
        vec3 ambient = lights.at(i)->getIa();
        vec3 diffuse = lights.at(i)->getId();
        vec3 specular = lights.at(i)->getIs();

        // Variables nomes per alguns tipus de llums (inicialitzem a 0)
        vec4 position = vec4(0);
        vec3 coefficients = vec3(0);
        vec3 direction = vec3(0);
        float angle = 0;

        // Nomes per llums puntuals
        if (lights.at(i)->getTipusLight()==LightType::Puntual){
            std::shared_ptr<PointLight> pointlight = std::dynamic_pointer_cast<PointLight> (lights.at(i));
            position = vec4(pointlight->getLightPosition());
            coefficients = vec3(pointlight->getCoeficients());
        }

        // Nomes per llums direccionals
        if (lights.at(i)->getTipusLight()==LightType::Direccional){
            std::shared_ptr<DirectionalLight> dirlight = std::dynamic_pointer_cast<DirectionalLight> (lights.at(i));
            direction = vec3(dirlight->getLightDirection());
        }

        // Nomes per llums spot
        if (lights.at(i)->getTipusLight()==LightType::Spot){
            std::shared_ptr<SpotLight> spotlight = std::dynamic_pointer_cast<SpotLight> (lights.at(i));
            direction = vec3(spotlight->getLightDirection());
            angle = spotlight->getAngle();
        }

        // 3. obtencio dels identificadors de la GPU: Suposem i l'index de l'i-èssim element del vector
        gl_IdVectLights[i].id_type = program->uniformLocation(QString("lights[%1].type").arg(i));
        gl_IdVectLights[i].id_ambient = program->uniformLocation(QString("lights[%1].ambient").arg(i));
        gl_IdVectLights[i].id_diffuse = program->uniformLocation(QString("lights[%1].diffuse").arg(i));
        gl_IdVectLights[i].id_specular = program->uniformLocation(QString("lights[%1].specular").arg(i));
        gl_IdVectLights[i].id_position = program->uniformLocation(QString("lights[%1].position").arg(i));
        gl_IdVectLights[i].id_direction = program->uniformLocation(QString("lights[%1].direction").arg(i));
        gl_IdVectLights[i].id_coefficients = program->uniformLocation(QString("lights[%1].coefficients").arg(i));
        gl_IdVectLights[i].id_angle = program->uniformLocation(QString("lights[%1].angle").arg(i));


        // 4. Bind de les zones de memòria que corresponen a la GPU als valors de la CPU
        glUniform1i(gl_IdVectLights[i].id_type, type);
        glUniform3fv(gl_IdVectLights[i].id_ambient, 1, ambient);
        glUniform3fv(gl_IdVectLights[i].id_diffuse, 1, diffuse);
        glUniform3fv(gl_IdVectLights[i].id_specular, 1, specular);
        glUniform3fv(gl_IdVectLights[i].id_coefficients, 1, coefficients);
        glUniform4fv(gl_IdVectLights[i].id_position, 1, position);
        glUniform3fv(gl_IdVectLights[i].id_direction, 1, direction);
        glUniform1f(gl_IdVectLights[i].id_angle, angle);
    }
}

void Scene::addLight(shared_ptr<Light> l) {
    lights.push_back(l);
}

/**
 * @brief Scene::setAmbientToGPU
 * @param program
 */
void Scene::setAmbientToGPU(shared_ptr<QGLShaderProgram> program){

       // 1. Es declara un struct d'identificadors
       struct gl_IdGlobal{
           GLuint id_global;
       };

       gl_IdGlobal gl_IdGlobalAmbientLight;

       // 2. Creem la variable local globalLight
       vec3 globalLight = vec3(lightAmbientGlobal);

       // 3. obtencio de l'identificador de la GPU
       gl_IdGlobalAmbientLight.id_global = program->uniformLocation("globalAmbientLight.globalLight");

       // 4. Bind de la zona de memòria que corresponen a la GPU al valor de la CPU
       glUniform3fv(gl_IdGlobalAmbientLight.id_global, 1, globalLight);
}

/**
 * @brief Scene::setCamera
 * @param Camera *
 */
void Scene::setCamera(shared_ptr<Camera> c) {
    camera = c;
}
/**
 * @brief Scene::calculCapsaMinCont3DEscena
 */

void Scene::calculCapsaMinCont3DEscena()
{
    Capsa3D c;
    vec3 pmax;

    if (objects.size()==1) {
        capsaMinima = objects[0]->calculCapsa3D();
        pmax[0] = capsaMinima.pmin[0]+capsaMinima.a;
        pmax[1] = capsaMinima.pmin[1]+capsaMinima.h;
        pmax[2] = capsaMinima.pmin[2]+capsaMinima.p;
    } else {
        capsaMinima.pmin[0]=200;
        capsaMinima.pmin[1]=200;
        capsaMinima.pmin[2]=200;
        pmax[0] = -200;
        pmax[1] = -200;
        pmax[2] = -200;
    }

    for (unsigned int i=0; i<objects.size(); i++) {
       c = objects[i]->calculCapsa3D();

       if (capsaMinima.pmin[0]>c.pmin[0]) capsaMinima.pmin[0] = c.pmin[0];
       if (capsaMinima.pmin[1]>c.pmin[1]) capsaMinima.pmin[1] = c.pmin[1];
       if (capsaMinima.pmin[2]>c.pmin[2]) capsaMinima.pmin[2] = c.pmin[2];
       if (pmax[0]<c.pmin[0]+c.a) pmax[0] = c.pmin[0]+c.a;
       if (pmax[1]<c.pmin[1]+c.h) pmax[1] = c.pmin[1]+c.h;
       if (pmax[2]<c.pmin[2]+c.p) pmax[2] = c.pmin[2]+c.p;
    }
    capsaMinima.a = pmax[0]-capsaMinima.pmin[0];
    capsaMinima.h = pmax[1]-capsaMinima.pmin[1];
    capsaMinima.p = pmax[2]-capsaMinima.pmin[2];
}

void Scene::update(int nframe) {
    for (unsigned int i = 0; i< objects.size(); i++) {
        if (dynamic_pointer_cast<Animable>(objects[i]) ) objects[i]->update(nframe);
    }
}
