#include "Renders/GLWidget.h"


GLWidget::GLWidget(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {

    setFocusPolicy( Qt::StrongFocus );

}

GLWidget::GLWidget(const QGLFormat &glf, QWidget *parent) : QGLWidget(glf, parent) {

    setFocusPolicy( Qt::StrongFocus );
    scene = make_shared<Scene>();
    scene->setCamera(make_shared<Camera>(this->size().width(), this->size().height()));
    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);
}

GLWidget::~GLWidget() {
    //makeCurrent();
}


void GLWidget::setScene(shared_ptr<Scene> sc) {
    scene = sc;
    scene->setCamera(make_shared<Camera>(this->size().width(), this->size().height()));
    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);
}

/* Interacció amb GL i inicialització de shaders */

/**
 * @brief GLWidget::initializeGL()
 */
void GLWidget::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_RGBA);
    glEnable(GL_DOUBLE);

    initShadersGPU();
    qDebug() << "Shaders initialized";

    // Default point light:
    vec3 ambient(0.3,0.3,0.3);
    vec3 diffuse(1,1,1);
    vec3 specular(0.5,0.5,0.5);
    vec4 position(-25,25,25,1);
    vec3 coefficients(0,0,1);
    shared_ptr<Light> l = dynamic_pointer_cast<Light>(make_shared<PointLight>(ambient, diffuse, specular, position, coefficients));
    scene->addLight(l);

    scene->camera->init(this->size().width(), this->size().height(), scene->capsaMinima);
    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);

    glViewport(scene->camera->vp.pmin[0], scene->camera->vp.pmin[1], scene->camera->vp.a, scene->camera->vp.h);
    // TODO: aquestes crides nomes per check que es fa be, treure un cop es faci merge amb pas 1!!!
    if (!scene->CUBEMAP_ACTIVATED)
        sendLightsToGPU();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * @brief GLWidget::paintGL()
 */
void GLWidget::paintGL() {
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    qDebug() << "paintGL";

    if (scene->CUBEMAP_ACTIVATED) {
        loadShader("CubeMap");
        scene->cub->setTexture();
        scene->camera->toGPU(program);
        scene->cub->toGPU(program);
        scene->cub->draw();
        loadShader("Gouraud");
        // Nomes enviem les llums una vegada
        if(!lightsSent) {
            sendLightsToGPU();
            lightsSent = true;
        }
    }

    scene->camera->toGPU(program);
    scene->draw();
}

/**
 * @brief GLWidget::resizeGL()
 */
void GLWidget::resizeGL(int width, int height) {

    glViewport(scene->camera->vp.pmin[0], scene->camera->vp.pmin[1], scene->camera->vp.a, scene->camera->vp.h);

    scene->camera->vp.a = width;
    scene->camera->vp.h = height;

    scene->camera->CalculaWindow(scene->capsaMinima);

    updateGL();
}

/**
 * @brief GLWidget::initShadersGPU
 */
void GLWidget::initShadersGPU(){
    //Creem els programes amb els shaders
    createShadersGPU("://resources/vshaderGouraud.glsl", "://resources/fshaderGouraud.glsl");
    createShadersGPU("://resources/vshaderPhong.glsl", "://resources/fshaderPhong.glsl");
    createShadersGPU("://resources/vshaderToon.glsl", "://resources/fshaderToon.glsl");
    createShadersGPU("://resources/vshaderCubeMap.glsl", "://resources/fshaderCubeMap.glsl");
    //Queden guardats al map shaderPrograms amb els noms Gouraud | Phong | Toon | CubeMap
    if (!scene->CUBEMAP_ACTIVATED)
        loadShader("Gouraud");
}

bool GLWidget::createShadersGPU(QString vShaderFile, QString fShaderFile){
    QString name = vShaderFile.section("/", 3, 3).replace(".glsl", "").replace("vshader", "");
    cout << "Loading shader program. Assigned name: " << name.toStdString() << endl;
    //Només l'afegim si no existeix
    if (shaderPrograms.find(name) == shaderPrograms.end()){
        QGLShader *vshader = new QGLShader(QGLShader::Vertex, this);
        QGLShader *fshader = new QGLShader(QGLShader::Fragment, this);
        vshader->compileSourceFile(vShaderFile);
        fshader->compileSourceFile(fShaderFile);
        auto program = make_shared<QGLShaderProgram>(this);
        program-> addShader(vshader);
        program-> addShader(fshader);
        shaderPrograms[name] = program;
        cout << name.toStdString() << " loaded successfully." << endl;
        return true;
    }else{
        //Si el shader ja existeix, no el tornem a afegir
        cout << name.toStdString() << " already exists." << endl;
        return false;
    }
}

bool GLWidget::loadShader(QString shader){
    //Si ja l'estem utilitzant, no el carreguem
    if (currentShader == shader){
        return false;
    }

    //Si no existeix, no el carreguem
    auto shaderEntry = shaderPrograms.find(shader);
    if(shaderEntry == shaderPrograms.end()){
        cout << "Error! Shader " << shader.toStdString() << " does not exist!" << endl;
        return false;
    }

    program = shaderEntry->second;
    program->link();
    program->bind();
    currentShader = shader;
    return true;
}

bool GLWidget::loadShaderAndRefresh(QString shader){ //updateShader
    if(!loadShader(shader)){
        return false; //Si no s'ha carregat, no fem res
    }

    // Enviem nou shader a GPU
    scene->toGPU(program);

    updateGL();

    return true;
}

void GLWidget::sendLightsToGPU() {
    scene->setAmbientToGPU(this->program);
    scene->lightsToGPU(this->program);
}

QSize GLWidget::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize GLWidget::sizeHint() const {
    return QSize(400, 400);
}


/** Gestio de les animacions i la gravació d'imatges ***/

void GLWidget::setCurrentFrame(){

    scene->update(currentFrame);
    updateGL();
    this->saveFrame();
    currentFrame++;

    if (currentFrame == MAXFRAMES)
        timer->stop();

}

void GLWidget::saveFrame(){
    this->grabFrameBuffer().save("screen_output_"+QVariant(currentFrame).toString()+".jpg");
}

void GLWidget::saveImage(){

    this->grabFrameBuffer().save("screen_output_"+QVariant(currentImage).toString()+".jpg");
    currentImage++;
}



/** Metodes SLOTS que serveixen al builder per a actualitzar l'escena i els objectes */

void GLWidget::updateObject(shared_ptr<Object> obj) {
    obj->toGPU(program);

    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);

    updateGL();
}

void GLWidget::updateScene(shared_ptr<Scene> sc) {
    // Control de la nova escena a la GPU

    qDebug() << "updateScene";

    scene = sc;
    scene->toGPU(program);

    // Podeu Utilitzar l'altre constructor de Camera
    // per inicialitzar els parametres de la camara.
    scene->setCamera(make_shared<Camera>(this->size().width(), this->size().height()));
    scene->camera->actualitzaCamera(scene->capsaMinima);

    emit ObsCameraChanged(scene->camera);
    emit FrustumCameraChanged(scene->camera);

    updateGL();

}

void GLWidget::updateShaderTexture(){
    //TODO
}

/** Metodes que es criden des dels menús */

void GLWidget::saveAnimation() {
    // Comença el timer de l'animació
    timer = new QTimer(this);
    currentFrame=0;
    currentImage=0;
    connect(timer, SIGNAL(timeout()), this, SLOT(setCurrentFrame()));
    timer->start(1000);

}

void GLWidget::activaToonShader() {
    //A implementar a la fase 1 de la practica 2
    loadShaderAndRefresh("Toon");
    qDebug()<<"Estic a Toon";
}

void GLWidget::activaPhongShader() {
    //Opcional: A implementar a la fase 1 de la practica 2
    loadShaderAndRefresh("Phong");
    qDebug()<<"Estic a Phong";

}

void GLWidget::activaGouraudShader() {
    //A implementar a la fase 1 de la practica 2
    loadShaderAndRefresh("Gouraud");
    qDebug()<<"Estic a Gouraud";

}

void GLWidget::activaPhongTex() {
    //A implementar a la fase 1 de la practica 2
    qDebug()<<"Estic a Phong Tex";
}

void GLWidget::activaBackground() {
    //A implementar a la fase 2 de la practica 2
    qDebug()<<"Estic a Background";

}
void GLWidget::activaBumpMapping() {
    //TO DO: a implementar a la fase 2 de la practica 2
     qDebug()<<"Estic a Bump Mapping";
}

void GLWidget::activaEnvMapping() {
    //TO DO: a implementar a la fase 2 de la practica 2
    qDebug()<<"Estic a Environmental Mapping";
}

void GLWidget::activaTransparency() {
    //TO DO: a implementar a la fase 2 de la practica 2
    qDebug()<<"Estic a Transparencia";
}


/** Mètodes que es criden des de les finestres de dialeg */

void GLWidget::setRotation(float angle, float x, float y, float z)
{
    // Rotació en coordenades de mon que es farà sobre l'escena carregada

}
void GLWidget::setTranslation(float x, float y, float z)
{
    // Translació en coordenades de mon que es farà sobre l'escena carregada

}

void GLWidget::setScale(float s)
{
    // Escala en coordenades de mon que es  farà sobre l'escena carregada
}


void GLWidget::setPerspective(float verticalAngle, float nearPlane, float farPlane)
{
    scene->camera->setFrustum(verticalAngle, nearPlane, farPlane);

    updateGL();
}

void GLWidget::setLookAt(const QVector3D &eye, const QVector3D &center, const QVector3D& up)
{
    vec4 lookfrom(eye[0], eye[1], eye[2], 1.0);
    vec4 lookat(center[0], center[1], center[2], 1.0);
    vec4 vup(up[0], up[1], up[2], 1.0);
    scene->camera->setObservador(lookfrom, lookat, vup);

    updateGL();
}

void GLWidget::setPointLight(const QVector3D &lightPos, const QVector3D &Ia, const QVector3D &Id,
                           const QVector3D &Is, const QVector3D &coefs)
{
    vec4 position(lightPos[0],lightPos[1], lightPos[2], 1.0) ;
    vec3 ambient( Ia[0], Ia[1], Ia[2]);
    vec3 diffuse( Id[0], Id[1], Id[2]);
    vec3 specular( Is[0], Is[1], Is[2]);
    vec3 coefficients( coefs[0], coefs[1], coefs[2]);

    //Creem una llum i la posem a lights[0].
    //ja que lights[0] serà la llum puntual/direccional/spotlight que escollim des de la interfície

    shared_ptr<Light> l = dynamic_pointer_cast<Light>(make_shared<PointLight>(ambient, diffuse, specular, position, coefficients));

    scene->lights[0] = l;

    scene->lightsToGPU(program);

    updateGL();
}

void GLWidget::setDirLight(const QVector3D &lightDir, const QVector3D &Ia, const QVector3D &Id,
                 const QVector3D &Is)
{
    vec3 direction(lightDir[0],lightDir[1], lightDir[2]) ;
    vec3 ambient( Ia[0], Ia[1], Ia[2]);
    vec3 diffuse( Id[0], Id[1], Id[2]);
    vec3 specular( Is[0], Is[1], Is[2]);
    //Creem una llum i la posem a lights[0].
    //ja que lights[0] serà la llum puntual/direccional/spotlight que escollim des de la interfície

    shared_ptr<Light> l = dynamic_pointer_cast<Light>(make_shared<DirectionalLight>(ambient, diffuse, specular, direction));

    scene->lights[0] = l;

    scene->lightsToGPU(program);

    updateGL();
}

//(vec3 ambient, vec3 diffuse, vec3 specular, vec3 direction) : Light(LightType::Direccional, ambient, diffuse, specular)
void GLWidget::setSpotLight(const QVector3D &lightDir, const QVector3D &Ia, const QVector3D &Id,
                 const QVector3D &Is, const qfloat16 angle, const qfloat16 sharpness)
{
    vec3 direction(lightDir[0],lightDir[1], lightDir[2]) ;
    vec3 ambient( Ia[0], Ia[1], Ia[2]);
    vec3 diffuse( Id[0], Id[1], Id[2]);
    vec3 specular( Is[0], Is[1], Is[2]);
    float ang = angle;
    float sharp = sharpness;
    //Creem una llum i la posem a lights[0].
    //ja que lights[0] serà la llum puntual/direccional/spotlight que escollim des de la interfície

    shared_ptr<Light> l = dynamic_pointer_cast<Light>(make_shared<SpotLight>(ambient, diffuse, specular, direction, angle, sharp));

    scene->lights[0] = l;

    scene->lightsToGPU(program);

    updateGL();
}

void GLWidget::setTextureFile(const QString &file)
{
    shared_ptr<QOpenGLTexture> texture;

    texture = make_shared<QOpenGLTexture>(QImage(file).mirrored());

    // TO DO: A modificar en la fase 1 de la practica 2
    // Per ara es posa la textura al primer objecte de l'escena
    for (int i = 0; i < scene->objects.size(); i++) {
        if (scene->objects[i]->canHaveTexture || scene->objects[i]->OPT_IND_TEXT_ACT) {
            scene->objects[i]->setTexture(texture);
        }
    }
}

/**  Mètodes d'interacció amb el ratolí */

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        if(lastPos.y()!= event->y() && lastPos.x()!= event->x()) {
           setXRotation(dy);
           setYRotation(dx);
        } else if(lastPos.y()!= event->y()) {// rotar la camera
            setXRotation(dy);
        } else if (lastPos.x()!= event->x()) {
            setYRotation(dx);
        }

    } else if (event->buttons() & Qt::RightButton) {
       // Zoom: canviar la mida de la window
        if(lastPos.y()> event->y())
             Zoom(-1);
        else
             Zoom(1);
    }

    lastPos = event->pos();
}


void GLWidget::setXRotation(int angle)
{
    if (angle >0) {
        scene->camera->angX += 5;
    } else if (angle<0)
        scene->camera->angX -= 5;
    qNormalizeAngle(scene->camera->angX);

    scene->camera->rotaCamera();

    emit ObsCameraChanged(scene->camera);

    updateGL();
}

void GLWidget::setYRotation(int angle)
{
    if (angle >0) {
        scene->camera->angY += 5;
    } else if (angle<0)
        scene->camera->angY-= 5;
    qNormalizeAngle(scene->camera->angY);

    scene->camera->rotaCamera();

    emit ObsCameraChanged(scene->camera);

    updateGL();
}

void GLWidget::qNormalizeAngle(double &angle)
{
    while (angle < 0)
        angle += 360*16;
    while (angle > 360)
        angle -= 360*16;
}

void GLWidget::Zoom (int positiu) {
    scene->camera->AmpliaWindow(positiu*(0.005));

    emit FrustumCameraChanged(scene->camera);

    updateGL();
}

