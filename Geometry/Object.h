#ifndef Object_H
#define Object_H

#include <QObject>
#include <vector>

#include <library/Common.h>
#include <memory>

#include <QGLShaderProgram>
#include <QOpenGLTexture>

#include <QFile>
#include <QRegularExpression>
#include <QDebug>
#include <QString>
#include <QStringList>

#include <Geometry/TG.h>
#include <Geometry/TranslateTG.h>
#include <Geometry/ScaleTG.h>
#include <Geometry/Animation.h>
#include <Geometry/Cara.h>
#include <Geometry/Material.h>

using namespace Common;

typedef vec4  point4;

// Classe que conte la representacio d'un Objecte: geometria, topologia, material i textures
class Object : public QObject, public Animable {

    Q_OBJECT
protected:
    QString nom;
    vector<Cara> cares;
    vector<point4> vertexs;
    vector<point4> normalsVertexs;
    vector<vec2>   textVertexs;

    // Estructures per passar a la GPU
    GLuint buffer;
    GLuint vao;

    int     numPoints;
    point4 *points;
    point4 *normals;

    shared_ptr<Material> material;

    int Index; // index de control del numero de vertexs a passar a la GPU

    shared_ptr<QGLShaderProgram> program;

    shared_ptr<QOpenGLTexture> texture;

public:
    Object(const int npoints, QObject *parent = 0);
    Object(const int npoints, QString n);
    Object(const int npoints, QString n, vec3 position, float scale);
    Object(const int npoints, QString n, vec3 position, float scale, shared_ptr<Material> material);
    ~Object();

    void parseObjFile(const QString &fileName);

    void setTexture(shared_ptr<QOpenGLTexture> t);

    virtual void make();
    virtual void toGPU(shared_ptr<QGLShaderProgram> p);
    virtual void toGPUTexture(shared_ptr<QGLShaderProgram> pr);

    virtual void draw();
    virtual void drawTexture();

    Capsa3D calculCapsa3D();

    virtual void aplicaTG(shared_ptr<TG> tg);

    void setPosition(vec3 position);

    void setScale(float scale);

    void setMaterial(shared_ptr<Material> material);
private:
    void initTexture();
};



#endif // Object_H
