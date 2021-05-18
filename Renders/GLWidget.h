#pragma once

#define GLWIDGET_H

#include <math.h>
#include <Renders/Camera.h>
#include <QtWidgets>
#include <QGLWidget>
#include <QtOpenGL>
#include <QTime>
#include <QtDebug>
#include <QString>
#include <QFloat16>

#include <Geometry/Scene.h>
#include "Geometry/Animation.h"

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_COLOR_ATTRIBUTE 1

class QGLShaderProgram;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    GLWidget(const QGLFormat &glf, QWidget *parent=0);
    ~GLWidget();

    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    void setScene (shared_ptr<Scene> sc);
    shared_ptr<Scene> getScene() {return scene;}


public slots:

    void updateObject(shared_ptr<Object> obj);
    void updateScene(shared_ptr<Scene> sc);

    void saveImage();
    void saveAnimation();

    void activaToonShader();
    void activaPhongShader();
    void activaGouraudShader();

    void activaPhongTex();
    void activaBackground();
    void activaBumpMapping();
    void activaEnvMapping();
    void activaTransparency();

    void setRotation(float angle, float x, float y, float z);
    void setTranslation(float x, float y, float z);
    void setScale(float s);
    void setPerspective(float verticalAngle, float nearPlane, float farPlane);
    void setLookAt(const QVector3D &eye, const QVector3D &center, const QVector3D& up);
    void setPointLight(const QVector3D &lightPos, const QVector3D &Ia, const QVector3D &Id,
                               const QVector3D &Is, const QVector3D &coefs);
    void setDirLight(const QVector3D &lightDir, const QVector3D &Ia, const QVector3D &Id,
                     const QVector3D &Is);
    void setSpotLight(const QVector3D &lightDir, const QVector3D &Ia, const QVector3D &Id,
                      const QVector3D &Is, const qfloat16 angle, const qfloat16 sharpness);
    void setTextureFile(const QString &file);

    // Acció per activar a cada update del timer
    void setCurrentFrame();


signals:
    void ObsCameraChanged(shared_ptr<Camera> cam);
    void FrustumCameraChanged(shared_ptr<Camera> cam);


protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void setXRotation(int angle);
    void setYRotation(int angle);

    void qNormalizeAngle(double &angle);

    void Zoom (int positiu);
    void saveFrame();
private:
    shared_ptr<Scene>  scene; // Escena que es pinta al GLWidget

    QTimer *timer;
    unsigned int currentFrame;
    unsigned int currentImage;

    QPoint lastPos;   // per interactuar amb la camera

    //Lista de shaders
    std::map<QString, shared_ptr<QGLShaderProgram>> shaderPrograms;
    //Shader actual
    shared_ptr<QGLShaderProgram> program;
    //Nom del shader actual (key del map de shaders)
    QString currentShader;
    bool loadShader(QString shader);
    bool loadShaderAndRefresh(QString shader);
    void initShadersGPU();
    bool createShadersGPU(QString vShaderFile,QString fShaderFile);
    void updateShaderTexture();
};

